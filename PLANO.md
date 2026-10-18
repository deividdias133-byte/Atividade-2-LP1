# Plano de implementação

Baseado em `DESCRICAO.md` e `AGENTS.md`. C++11, só biblioteca padrão,
sem `new`/`delete`, sem lambda e sem `unordered_map`. As classes não usam
`cin` nem `cout`: quem lê e escreve na tela é a interface.

## Arquivos que serão criados

```text
include/Time.hpp        src/Time.cpp        classe Time
include/Partida.hpp     src/Partida.cpp     classe Partida
include/Campeonato.hpp  src/Campeonato.cpp  classe Campeonato
include/Interface.hpp   src/Interface.cpp   leitura e escrita na tela
                        src/main.cpp        só chama a interface
exemplos/               arquivos de entrada para teste
```

O comando de compilação do `README.md` (`g++ ... src/*.cpp -Iinclude -o sistema`)
já pega todos esses arquivos, então ele não precisa mudar.

## Classes

### Time (`include/Time.hpp`, `src/Time.cpp`)

Guarda: `nome` (string), `vitorias` (int) e `kills` (int, somatório de todas
as partidas que o time jogou, ganhas ou perdidas).

Métodos:

- `Time(string nome)`
- `string nome() const`
- `int vitorias() const` e `int kills() const`
- `void registraJogo(bool venceu, int killsDaPartida)` — soma 1 vitória se
  venceu e sempre soma as kills
- `bool operator<(const Time& outro) const` — primeiro por vitórias, depois
  por kills; é ele que o `sort` da tabela usa
- `bool operator==(const Time& outro) const` — mesmas vitórias e mesmas
  kills; serve para detectar times na mesma posição

Por que: a tabela é ordenada por vitórias e desempatada por kills, então os
dois operadores ficam dentro da classe que tem esses dados.

### Partida (`include/Partida.hpp`, `src/Partida.cpp`)

Guarda: `timeA` e `timeB` (string), `vencedor` (string), `killsA` e `killsB`
(int).

Métodos:

- `Partida(string a, string b, string vencedor, int killsA, int killsB)`
- acessadores `timeA()`, `timeB()`, `vencedor()`, `killsA()`, `killsB()`
- `bool ehConfronto(string a, string b) const` — verdadeiro se a partida for
  entre esses dois times, qualquer que seja a ordem

Por que: cada partida é um registro imutável (não existe alterar estatística),
então só leitura depois de criada.

### Campeonato (`include/Campeonato.hpp`, `src/Campeonato.cpp`)

Guarda:

- `map<string, Time> times` — o objeto `Time` guardado dentro do map; a chave
  é o nome, o que já resolve nome repetido e a busca por nome
- `vector<Partida> partidas` — histórico na ordem em que aconteceram
- `set<string> confrontos` — uma chave por par, por exemplo
  `"meu_time|meu_time2"` (sempre em ordem alfabética); impede confronto
  repetido
- `bool comecou`, `bool acabou`, `bool semVencedor`, `string campeao`,
  `int totalPartidas`

Métodos (todos retornando `bool` ou dados; a interface é quem imprime):

- `bool cadastrarTime(string nome)` — falso se o campeonato já começou ou o
  nome já existe
- `bool apagarTime(string nome)` — falso se já começou ou o time não existe
- `bool comecar()` — falso se não há times, se são menos de 4, mais de 10 ou
  ímpares; calcula `totalPartidas = n * (n-1) / 2`
- `bool registrarResultado(string a, string b, string vencedor, int killsA,
  int killsB)` — falso se: não começou, já acabou, algum time não existe,
  `a == b`, confronto repetido, kills negativas, kills iguais (empate não
  existe na partida) ou vencedor não é `a` nem `b`; ao aceitar, atualiza os
  dois times e os três containers; se `partidas.size() == totalPartidas`,
  marca `acabou`
- `vector<Partida> resultados() const` — para `mostrar-resultado`
- `vector<Time> classificacao() const` — copia os times e aplica `sort` com
  `operator<`; times empatados em vitórias e kills saem na mesma posição
- `bool acabou() const` e `bool comecou() const`
- `bool precisaDesempate() const` — acabou e os dois primeiros empataram em
  vitórias e kills
- `bool registrarDesempate(string vencedor)` — define o campeão sem mudar a
  tabela
- `bool encerradoSemVencedor() const` — acabou e três times empatados no
  primeiro lugar
- `string campeao() const`
- `bool encerrar()` — apaga times, partidas e confrontos; o sistema volta ao
  estado inicial e pode receber um novo campeonato

Por que cada container:

| Onde | Container | Por quê |
| --- | --- | --- |
| Campeonato | `map<string, Time>` | busca por nome direta e já garante nome único |
| Campeonato | `set<string>` | `set` não aceita repetição: confronto repetido vira erro simples |
| Campeonato | `vector<Partida>` | guarda a ordem cronológica para `mostrar-resultado` |
| classificacao() | `sort` + `operator<` | é o jeito de ordenar a tabela pelos critérios da descrição |

### Interface (`include/Interface.hpp`, `src/Interface.cpp`, `src/main.cpp`)

- `void executar(Campeonato& campeonato)` — lê a linha, separa o comando dos
  argumentos e chama o método certo
- lê as kills com `istringstream`: se o texto não for número ou for negativo,
  imprime o erro (é a interface que converte, não a classe)
- imprime as mensagens de erro da seção "Quando algo dá errado" do
  `DESCRICAO.md`, e o resultado de `mostrar-tabela`, `mostrar-resultado` e
  `mostrar-vencedor`
- `mostrar-vencedor` com campeonato encerrado sem vencedor mostra a mensagem
  "campeonato encerrado sem vencedor", não é erro

## Etapas

Cada etapa termina com o projeto compilando pelo comando do `README.md` e com
algo que dá para testar na tela.

1. **Time + esqueleto da interface.** Cria `Time` (com `operator<` e
   `operator==`), `Interface` e `main.cpp`. A interface lê qualquer comando;
   os que ainda não existem respondem "comando ainda não implementado".
   Teste: compilar e digitar comandos.

2. **Cadastrar e apagar times.** Cria `Campeonato` com `cadastrarTime` e
   `apagarTime` e liga esses dois comandos na interface.
   Teste: cadastrar 4 times; cadastrar nome repetido dá erro; apagar um time;
   apagar time que não existe dá erro.

3. **Começar o campeonato e mostrar a tabela.** Cria `comecar` (validações
   de 4, 10 e par) e `classificacao` com o `sort`; liga `começar-campeonato`
   e `mostrar-tabela`.
   Teste: começar com 3 times dá erro; com 5 dá erro; com 4 funciona; a
   tabela mostra os times com 0 vitórias e 0 kills; `mostrar-tabela` antes de
   começar dá erro.

4. **Registrar resultados.** Cria `Partida`, `registrarResultado`,
   `resultados`, o `set` de confrontos e o encerramento automático quando
   todas as partidas foram registradas; liga `resultado` e
   `mostrar-resultado`.
   Teste: em um campeonato de 4 times são 6 partidas; registrar as 6 fecha o
   campeonato sozinho; confronto repetido dá erro; kills iguais, negativas ou
   com texto dão erro.

5. **Mostrar o vencedor.** Cria `precisaDesempate`, `registrarDesempate`,
   `encerradoSemVencedor` e `campeao`; liga `mostrar-vencedor`.
   Teste: campeão direto aparece; dois empatados exigem a partida de
   desempate (que não muda a tabela); três empatados mostram "campeonato
   encerrado sem vencedor"; antes de acabar dá erro.

6. **Encerrar e testar tudo.** Cria `encerrar`; cria os arquivos de
   `exemplos/` (um caminho feliz completo e um para cada erro da descrição);
   roda todos os exemplos e confere item por item da seção "Quando algo dá
   errado".
