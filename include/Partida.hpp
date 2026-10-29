#ifndef PARTIDA_HPP
#define PARTIDA_HPP

#include <string>

class Partida {
public:
    Partida(std::string timeA, std::string timeB, std::string vencedor, int killsA, int killsB);

    std::string timeA() const;
    std::string timeB() const;
    std::string vencedor() const;
    int killsA() const;
    int killsB() const;

    bool ehConfronto(std::string a, std::string b) const;

private:
    std::string timeA_;
    std::string timeB_;
    std::string vencedor_;
    int killsA_;
    int killsB_;
};

#endif
