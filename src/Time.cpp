#include "Time.hpp"

Time::Time(std::string nome) : nome_(nome), vitorias_(0), kills_(0) {
}

std::string Time::nome() const {
    return nome_;
}

int Time::vitorias() const {
    return vitorias_;
}

int Time::kills() const {
    return kills_;
}

void Time::registraJogo(bool venceu, int killsDaPartida) {
    if (venceu) {
        ++vitorias_;
    }
    kills_ += killsDaPartida;
}

bool Time::operator<(const Time& outro) const {
    if (vitorias_ != outro.vitorias_) {
        return vitorias_ > outro.vitorias_;
    }
    return kills_ > outro.kills_;
}

bool Time::operator==(const Time& outro) const {
    return vitorias_ == outro.vitorias_ && kills_ == outro.kills_;
}
