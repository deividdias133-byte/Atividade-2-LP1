#include "Partida.hpp"

Partida::Partida(std::string timeA, std::string timeB, std::string vencedor, int killsA, int killsB)
    : timeA_(timeA), timeB_(timeB), vencedor_(vencedor), killsA_(killsA), killsB_(killsB) {
}

std::string Partida::timeA() const {
    return timeA_;
}

std::string Partida::timeB() const {
    return timeB_;
}

std::string Partida::vencedor() const {
    return vencedor_;
}

int Partida::killsA() const {
    return killsA_;
}

int Partida::killsB() const {
    return killsB_;
}

bool Partida::ehConfronto(std::string a, std::string b) const {
    return (a == timeA_ && b == timeB_) || (a == timeB_ && b == timeA_);
}
