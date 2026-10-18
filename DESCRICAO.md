# Descrição do sistema

Este sistema organiza e simula um campeonato de um jogo estilo FPS.

## Nome e ideia

O sistema é campeonatos e serve para organizar campeonatos.

## O que o sistema guarda

O sistema guarda resultados de partidas e os times.

## O que dá para fazer

cadastrar-time: registra um novo time antes do campeonato começar.
começar-campeonato: começa um novo campeonato, quando já houver de 4 a 10 times, em número par.
mostrar-tabela: mostra a tabela do campeonato, com a posição de cada time, as vitórias e o total de kills.
resultado: você decide quem ganha a partida e a quantidade de kills de cada um dos dois times.
mostrar-resultado: mostra os resultados das partidas já registradas.
mostrar-vencedor: mostra quem é o vencedor do campeonato.
encerrar-campeonato: encerra o campeonato sem vencedores e os times são excluídos junto com os dados do campeonato.
apagar-time: apaga um time existente antes do campeonato começar.

## Regras

Cada partida tem um vencedor; empate não existe na partida. Empate quer dizer
dois times com o mesmo número de vitórias na tabela.
Não dá para registrar um confronto que já aconteceu.
O empate que importa é apenas o do primeiro lugar.
O critério para ordenar a tabela é, primeiro, o número de vitórias; o
desempate é o total de kills que o time fez em todas as partidas, ganhas ou
perdidas.
Se dois times terminarem com o mesmo número de vitórias e o mesmo número de
kills em primeiro lugar, acontece uma partida de desempate. Você decide o
vencedor dessa partida. Ela não muda a tabela, só decide quem é o campeão.
Se três times empatarem em primeiro lugar, o campeonato encerra sem vencedor,
mas os times e a tabela continuam guardados.
Fora do primeiro lugar, times com vitórias empatadas são ordenados pelas
kills; se as kills também empatarem, os dois ficam na mesma posição na tabela.
Cada time disputará uma partida com todos os times do campeonato; quando
todas as partidas acontecerem, o campeonato se encerra sozinho.
O comando mostrar-vencedor não pode ser executado antes de o campeonato
acabar, caso contrário dará erro.
Não pode haver dois times com o mesmo nome, não pode haver dois vencedores e
não existe comando para alterar estatísticas já registradas na tabela.
Não pode haver número de times ímpares: apenas número par, no mínimo 4 e no
máximo 10. Essa conferência acontece no começar-campeonato.

## Quando algo dá errado

Quando tentar registrar um time depois de começar o campeonato.
Quando tentar apagar um time depois de começar o campeonato.
Quando tentar começar o campeonato com menos de 4 times, mais de 10 times ou
com número ímpar de times.
Quando tentar mostrar a tabela ou o resultado antes de começar o campeonato.
Quando tentar mostrar o vencedor antes de o campeonato acabar.
Quando o time não existir ao tentar executar os comandos.
Quando nome de time repetido.
Quando tentar registrar um confronto que já aconteceu.
Quando tentar começar o campeonato sem times cadastrados (lista vazia).
Quando o que era número não for número, como kills "abc", ou kills negativas.

## Classes que eu imagino

Campeonato: é quem junta tudo.
time: guarda os dados de um time.
partida: representa uma partida já realizada.

## Exemplo de uso

===== campeonato =====
cadastrar-time
começar-campeonato
resultado
mostrar-tabela
mostrar-resultado
mostrar-vencedor
encerrar-campeonato
apagar-time

===== cadastrar-time =====
time 1:
nome: meu_time

time 2:
nome: meu_time2
