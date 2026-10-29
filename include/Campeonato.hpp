#ifndef CAMPEONATO_HPP
#define CAMPEONATO_HPP

#include <map>
#include <set>
#include <string>
#include <vector>

#include "Partida.hpp"
#include "Time.hpp"

class Campeonato {
public:
    Campeonato();

    bool cadastrarTime(std::string nome);
    bool apagarTime(std::string nome);
    bool comecar();

    bool timeExiste(std::string nome) const;
    bool registrarResultado(std::string a, std::string b, std::string vencedor, int killsA, int killsB);

    bool comecou() const;
    bool acabou() const;
    std::vector<Time> classificacao() const;
    std::vector<Partida> resultados() const;

    bool precisaDesempate() const;
    bool registrarDesempate(std::string vencedor);
    bool encerradoSemVencedor() const;
    std::string campeao() const;
    bool encerrar();

private:
    int quantidadeNoPrimeiroLugar() const;

    std::map<std::string, Time> times_;
    std::vector<Partida> partidas_;
    std::set<std::string> confrontos_;
    bool comecou_;
    bool acabou_;
    int totalPartidas_;
    std::string campeao_;
};

#endif
