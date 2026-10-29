#include "Campeonato.hpp"

#include <algorithm>
#include <utility>

Campeonato::Campeonato() : comecou_(false), acabou_(false), totalPartidas_(0) {
}

bool Campeonato::cadastrarTime(std::string nome) {
    if (comecou_) {
        return false;
    }
    if (times_.count(nome) > 0) {
        return false;
    }
    times_.insert(std::make_pair(nome, Time(nome)));
    return true;
}

bool Campeonato::apagarTime(std::string nome) {
    if (comecou_) {
        return false;
    }
    std::map<std::string, Time>::iterator it = times_.find(nome);
    if (it == times_.end()) {
        return false;
    }
    times_.erase(it);
    return true;
}

bool Campeonato::comecar() {
    int quantidade = static_cast<int>(times_.size());
    if (quantidade < 4 || quantidade > 10 || quantidade % 2 != 0) {
        return false;
    }
    comecou_ = true;
    totalPartidas_ = quantidade * (quantidade - 1) / 2;
    return true;
}

bool Campeonato::timeExiste(std::string nome) const {
    return times_.count(nome) > 0;
}

bool Campeonato::registrarResultado(std::string a, std::string b, std::string vencedor, int killsA, int killsB) {
    if (!comecou_ || acabou_) {
        return false;
    }
    if (a == b) {
        return false;
    }
    if (!timeExiste(a) || !timeExiste(b)) {
        return false;
    }
    if (vencedor != a && vencedor != b) {
        return false;
    }
    if (killsA < 0 || killsB < 0) {
        return false;
    }
    if (killsA == killsB) {
        return false;
    }

    std::string chave;
    if (a < b) {
        chave = a + "|" + b;
    } else {
        chave = b + "|" + a;
    }
    if (confrontos_.count(chave) > 0) {
        return false;
    }

    std::map<std::string, Time>::iterator itA = times_.find(a);
    std::map<std::string, Time>::iterator itB = times_.find(b);
    itA->second.registraJogo(vencedor == a, killsA);
    itB->second.registraJogo(vencedor == b, killsB);

    partidas_.push_back(Partida(a, b, vencedor, killsA, killsB));
    confrontos_.insert(chave);

    if (static_cast<int>(partidas_.size()) == totalPartidas_) {
        acabou_ = true;
    }
    return true;
}

bool Campeonato::comecou() const {
    return comecou_;
}

bool Campeonato::acabou() const {
    return acabou_;
}

std::vector<Time> Campeonato::classificacao() const {
    std::vector<Time> tabela;
    std::map<std::string, Time>::const_iterator it;
    for (it = times_.begin(); it != times_.end(); ++it) {
        tabela.push_back(it->second);
    }
    std::sort(tabela.begin(), tabela.end());
    return tabela;
}

std::vector<Partida> Campeonato::resultados() const {
    return partidas_;
}

int Campeonato::quantidadeNoPrimeiroLugar() const {
    std::vector<Time> tabela = classificacao();
    if (tabela.empty()) {
        return 0;
    }
    int quantidade = 0;
    for (std::size_t i = 0; i < tabela.size(); ++i) {
        if (tabela[i] == tabela[0]) {
            ++quantidade;
        }
    }
    return quantidade;
}

bool Campeonato::precisaDesempate() const {
    if (!acabou_ || !campeao_.empty()) {
        return false;
    }
    return quantidadeNoPrimeiroLugar() == 2;
}

bool Campeonato::registrarDesempate(std::string vencedor) {
    if (!precisaDesempate()) {
        return false;
    }
    std::vector<Time> tabela = classificacao();
    if (tabela[0].nome() != vencedor && tabela[1].nome() != vencedor) {
        return false;
    }
    campeao_ = vencedor;
    return true;
}

bool Campeonato::encerradoSemVencedor() const {
    if (!acabou_ || !campeao_.empty()) {
        return false;
    }
    return quantidadeNoPrimeiroLugar() >= 3;
}

std::string Campeonato::campeao() const {
    if (!acabou_) {
        return "";
    }
    if (!campeao_.empty()) {
        return campeao_;
    }
    if (quantidadeNoPrimeiroLugar() != 1) {
        return "";
    }
    std::vector<Time> tabela = classificacao();
    return tabela[0].nome();
}

bool Campeonato::encerrar() {
    times_.clear();
    partidas_.clear();
    confrontos_.clear();
    comecou_ = false;
    acabou_ = false;
    totalPartidas_ = 0;
    campeao_.clear();
    return true;
}
