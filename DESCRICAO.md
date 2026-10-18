# Descrição do sistema

Este sistema organiza e simula um campeonato de um jogo estilo FPS.

## Nome e ideia

O sistema é campeonatos e serve para organizar campeonatos.

## O que o sistema guarda

O sistema guarda resultados de partidas e os times.

## O que dá para fazer

cadastrar-time: registra um novo time antes do campeonato começar.
começar-campeonato: começa um novo campeonato.
mostrar-tabela: mostra a tabela do campeonato.
resultado: Você decide quem ganha e a quantidade de kills de cada time.
mostrar-resultado: mostra os resultados das partidas.
mostrar-vencedor: Mostra o quem é o vencedor do campeonato.
encerrar-campeonato: encerra o campeonato sem vencedores e os times são excluidos junto com os dados do campeonato.
apagar-time: apaga time existente antes do campeonato começar.

## Regras

Não dá para ter empate nas partidas, apenas na tabela.
Não dá para registrar um confronto que já aconteceu.
O empate que importa é apenas o do primeiro lugar.
Se três times empatarem o é executado o comando encerrar-campeonato.
O comando resultado decide o resultado das partidas com quem venceu e a quantidade de kills de cada time, as kills servirão de critério de desempate,
o que contará como critério inicial será o número de vitórias, caso o campeonato acabe com o número de vitórias iguais entre dois times, considerará quem tiver o maior número de kills,
caso tenha o mesmo número de kills ocorrerá uma partida de desempate.
A partida de desempate não mudará a tabela, só decidirá o vencedor.
A partida de desempate você decide o vencedor.
O comando mostrar-vencedor não pode ser execultado antes do campeonato acabar, caso contrário dará erro.
Cada time disputará uma partida com todos do campeonato, quando todas as partidas acontecerem, o campeonato se encerra.
Não pode dois times com o mesmo nome, não pode ter dois vencedores, não pode alterar as estatísticas da tabela.
Também não poderá haver numero de times ímpares, apensa um número de times par.
Poderá haver uma quantia de no máximo 10 times, o número mínimo de times é quatro.
A ordem da tabela é por vitórias, o critério de desempate é as kills feitas nas partidas.

## Quando algo dá errado

Quando tentar registrar um time depois de começar o campeonato.
Quando tentar apagar um time depois de começar o campeonato.
Quando tentar registrar mias de 10 ou menos de 4 times.
Caso tente imprimir o resultado antes de começar.
Quanto o time não existir ao tentar executar os comandos.
Nome de time repetido.
lista vazia.
Texto onde eram números, como kills "abc" ou kills negativas.


## Classes que eu imagino

Campeonato: é quem junta tudo.
time: guarda os dados de um time.
partida: representa uma partida já realizada.


## Exemplo de uso

===== campeonato =====
cadastrar-time
começar-campeonato

===== cadastrar-time =====
time 1:
nome:meu_time

time 2:
nome: meu_time2...
