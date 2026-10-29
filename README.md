# Simulador de campeonatos

Atividade da Unidade 2 de Linguagem de Programação I. Leia `ENUNCIADO.md`
antes de começar.

Uma frase dizendo o que o sistema faz. A descrição completa está em
`DESCRICAO.md`.

## Arquivos

```text
.
├── AGENTS.md       regras que a IA lê antes de cada pedido
├── DESCRICAO.md    a descrição do sistema, escrita por você
├── ENUNCIADO.md    a atividade
├── PLANO.md        o plano feito com a IA (criado na etapa 3)
├── README.md       este arquivo
├── exemplos/       arquivos de entrada para testar
├── include/        um .hpp por classe
└── src/            um .cpp por classe, mais a interface
```

## Compilar e executar

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema
```

Se o comando mudar, atualize esta seção. Na correção eu vou usar o que
estiver escrito aqui.

## Onde uso a STL

| Onde | O quê | Por quê |
| --- | --- | --- |
| `Campeonato` (`Campeonato.hpp:37`) | `map<string, Time>` | Guarda os times usando o nome como chave. A busca por nome fica direta e o `map` não deixa duas chaves iguais. |
| `Campeonato` (`Campeonato.hpp:38`) | `vector<Partida>` | Guarda as partidas na ordem em que foram registradas, que é a ordem que `mostrar-resultado` precisa. |
| `Campeonato` (`Campeonato.hpp:39`) | `set<string>` | Guarda uma chave por confronto, como `"A\|B"`. Como `set` não aceita repetição, fica fácil detectar confronto repetido. |
| `Campeonato::apagarTime` (`Campeonato.cpp:24`) | `map::find` | Encontra o time pelo nome sem percorrer todos os times. |
| `Campeonato::cadastrarTime` / `timeExiste` (`Campeonato.cpp:13,43`) | `map::count` | Verifica se o nome já existe antes de cadastrar. |
| `Campeonato::registrarResultado` (`Campeonato.cpp:72`) | `set::count` | Verifica se o confronto já foi registrado. |
| `Campeonato::classificacao` (`Campeonato.cpp:98`) | `vector<Time>` + `sort` | Copia os times para um vetor e ordena pela tabela. O `map` é ordenado por nome, não por vitórias/kills; o `vector` pode ser reordenado. O `sort` usa o `Time::operator<`, definido em `Time.cpp:26`. |
| `Campeonato::resultados` (`Campeonato.cpp:108`) | `vector<Partida>` | Devolve as partidas na ordem original para a interface mostrar. |
| `Interface` (`Interface.cpp:64,116,132`) | `vector<Time>` / `vector<Partida>` | Recebe os dados prontos das classes e só percorre para imprimir; a interface não guarda o estado do campeonato. |

## Como usei a IA

Escreva com as suas palavras:

- Modelo usado: Big Pickle
- Um pedido que deu certo, e por que você acha que deu certo: O pedido das etapas aos poucos. Deu certo por que usei o prompt do pdf e também por que a descrição estava bem montada, logo veio um plano bem estruturado.
- Um pedido que deu errado, o que veio errado e como você mudou o pedido: um pedido de interface, toda vez que eu peço uma interface para o programa acho erros, logo deixei o programa apenas com comandos e com um comando <ajuda> para poder mostrar os comandos.
- Uma coisa que a IA sugeriu e você recusou, e por quê: Ela sugeriu um menu depois do código feito, recusei por quê  não vale a pena fazer isso depois de ter feito por comandos.
