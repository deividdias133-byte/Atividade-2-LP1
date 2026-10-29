#ifndef TIME_HPP
#define TIME_HPP

#include <string>

class Time {
public:
    Time(std::string nome);

    std::string nome() const;
    int vitorias() const;
    int kills() const;

    void registraJogo(bool venceu, int killsDaPartida);

    bool operator<(const Time& outro) const;
    bool operator==(const Time& outro) const;

private:
    std::string nome_;
    int vitorias_;
    int kills_;
};

#endif
