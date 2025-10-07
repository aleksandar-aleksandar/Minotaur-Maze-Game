#pragma once
#include <string>
#include "Lavirint.h"

enum class TipPredmeta {
    MAGLA,
    MAC,
    STIT,
    CEKIC
};

class Predmet {
private:
    TipPredmeta tip;
    int trajanje;
public:
    Predmet(TipPredmeta t, int tr);

    TipPredmeta getTip() const;
    int getTrajanje() const;
    void setTrajanje(int tr);
    void iskoristi();

    void smanjiTrajanje();
    bool aktivan() const;

    std::string naziv() const;
};
