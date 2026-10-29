#include "Interface.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

bool lerInteiro(const std::string& texto, int& valor) {
    std::istringstream fluxo(texto);
    if (!(fluxo >> valor)) {
        return false;
    }
    fluxo >> std::ws;
    return fluxo.eof();
}

}

void Interface::executar(Campeonato& campeonato) {
    std::string linha;
    while (std::getline(std::cin, linha)) {
        if (linha.empty()) {
            continue;
        }

        std::istringstream entrada(linha);
        std::string comando;
        entrada >> comando;

        if (comando == "cadastrar-time") {
            std::string nome;
            if (!(entrada >> nome)) {
                std::cout << "erro: nome do time não informado" << std::endl;
            } else if (campeonato.comecou()) {
                std::cout << "erro: o campeonato já começou" << std::endl;
            } else if (!campeonato.cadastrarTime(nome)) {
                std::cout << "erro: já existe um time com esse nome" << std::endl;
            } else {
                std::cout << "time cadastrado" << std::endl;
            }
        } else if (comando == "apagar-time") {
            std::string nome;
            if (!(entrada >> nome)) {
                std::cout << "erro: nome do time não informado" << std::endl;
            } else if (campeonato.comecou()) {
                std::cout << "erro: o campeonato já começou" << std::endl;
            } else if (!campeonato.apagarTime(nome)) {
                std::cout << "erro: time não existe" << std::endl;
            } else {
                std::cout << "time apagado" << std::endl;
            }
        } else if (comando == "começar-campeonato") {
            if (!campeonato.comecar()) {
                std::cout << "erro: o campeonato precisa de 4 a 10 times, em número par" << std::endl;
            } else {
                std::cout << "campeonato começou" << std::endl;
            }
        } else if (comando == "mostrar-tabela") {
            if (!campeonato.comecou()) {
                std::cout << "erro: o campeonato ainda não começou" << std::endl;
            } else {
                std::vector<Time> tabela = campeonato.classificacao();
                std::cout << "posição\ttime\tvitórias\tkills" << std::endl;
                int posicao = 0;
                for (std::size_t i = 0; i < tabela.size(); ++i) {
                    if (i == 0 || !(tabela[i] == tabela[i - 1])) {
                        posicao = static_cast<int>(i) + 1;
                    }
                    std::cout << posicao << "\t" << tabela[i].nome() << "\t"
                              << tabela[i].vitorias() << "\t" << tabela[i].kills() << std::endl;
                }
            }
        } else if (comando == "resultado") {
            if (!campeonato.comecou()) {
                std::cout << "erro: o campeonato ainda não começou" << std::endl;
            } else if (campeonato.acabou()) {
                std::cout << "erro: o campeonato já acabou" << std::endl;
            } else {
                std::string a;
                std::string b;
                std::string vencedor;
                std::string killsATexto;
                std::string killsBTexto;

                if (!(entrada >> a >> b >> vencedor >> killsATexto >> killsBTexto)) {
                    std::cout << "erro: dados da partida incompletos" << std::endl;
                } else {
                    int killsA = 0;
                    int killsB = 0;

                    if (!lerInteiro(killsATexto, killsA) || !lerInteiro(killsBTexto, killsB)) {
                        std::cout << "erro: kills inválidas" << std::endl;
                    } else if (killsA < 0 || killsB < 0) {
                        std::cout << "erro: as kills não podem ser negativas" << std::endl;
                    } else if (a == b) {
                        std::cout << "erro: um time não pode jogar contra si mesmo" << std::endl;
                    } else if (vencedor != a && vencedor != b) {
                        std::cout << "erro: o vencedor deve ser um dos dois times" << std::endl;
                    } else if (killsA == killsB) {
                        std::cout << "erro: a partida não pode terminar empatada" << std::endl;
                    } else if (!campeonato.timeExiste(a) || !campeonato.timeExiste(b)) {
                        std::cout << "erro: time não existe" << std::endl;
                    } else if (!campeonato.registrarResultado(a, b, vencedor, killsA, killsB)) {
                        std::cout << "erro: esse confronto já aconteceu" << std::endl;
                    } else {
                        std::cout << "resultado registrado" << std::endl;
                    }
                }
            }
        } else if (comando == "mostrar-resultado") {
            if (!campeonato.comecou()) {
                std::cout << "erro: o campeonato ainda não começou" << std::endl;
            } else {
                std::vector<Partida> partidas = campeonato.resultados();
                std::cout << "time A\ttime B\tvencedor\tkills A\tkills B" << std::endl;
                for (std::size_t i = 0; i < partidas.size(); ++i) {
                    std::cout << partidas[i].timeA() << "\t"
                              << partidas[i].timeB() << "\t"
                              << partidas[i].vencedor() << "\t"
                              << partidas[i].killsA() << "\t"
                              << partidas[i].killsB() << std::endl;
                }
            }
        } else if (comando == "mostrar-vencedor") {
            if (!campeonato.acabou()) {
                std::cout << "erro: o campeonato ainda não acabou" << std::endl;
            } else if (campeonato.encerradoSemVencedor()) {
                std::cout << "campeonato encerrado sem vencedor" << std::endl;
            } else if (campeonato.precisaDesempate()) {
                std::vector<Time> tabela = campeonato.classificacao();
                std::cout << "empate no primeiro lugar: registre o desempate entre "
                          << tabela[0].nome() << " e " << tabela[1].nome() << std::endl;
            } else {
                std::cout << "campeão: " << campeonato.campeao() << std::endl;
            }
        } else if (comando == "desempate") {
            std::string vencedor;
            if (!(entrada >> vencedor)) {
                std::cout << "erro: nome do time não informado" << std::endl;
            } else if (!campeonato.acabou()) {
                std::cout << "erro: o campeonato ainda não acabou" << std::endl;
            } else if (campeonato.encerradoSemVencedor()) {
                std::cout << "erro: campeonato encerrado sem vencedor" << std::endl;
            } else if (!campeonato.precisaDesempate()) {
                std::cout << "erro: não há desempate pendente" << std::endl;
            } else if (!campeonato.registrarDesempate(vencedor)) {
                std::cout << "erro: o vencedor deve ser um dos times empatados" << std::endl;
            } else {
                std::cout << "desempate registrado" << std::endl;
            }
        } else if (comando == "encerrar-campeonato") {
            campeonato.encerrar();
            std::cout << "campeonato encerrado" << std::endl;
        } else if (comando == "ajuda") {
            std::cout << "cadastrar-time <nome>" << std::endl;
            std::cout << "apagar-time <nome>" << std::endl;
            std::cout << "começar-campeonato" << std::endl;
            std::cout << "resultado <timeA> <timeB> <vencedor> <killsA> <killsB>" << std::endl;
            std::cout << "desempate <nome>" << std::endl;
            std::cout << "mostrar-tabela" << std::endl;
            std::cout << "mostrar-resultado" << std::endl;
            std::cout << "mostrar-vencedor" << std::endl;
            std::cout << "encerrar-campeonato" << std::endl;
            std::cout << "ajuda" << std::endl;
        } else {
            std::cout << "comando ainda não implementado" << std::endl;
        }
    }
}
