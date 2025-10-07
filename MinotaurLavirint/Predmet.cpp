#pragma once
#include <string>
#include "Lavirint.h"
#include "Predmet.h"

Predmet::Predmet(TipPredmeta t, int tr = 3) : tip(t), trajanje(tr) {}

TipPredmeta Predmet::getTip() const { return tip; }
int Predmet::getTrajanje() const { return trajanje; }
void Predmet::setTrajanje(int tr) { trajanje = tr; }

void Predmet::smanjiTrajanje() { if (trajanje > 0) trajanje--; }
void Predmet::iskoristi() { trajanje = 0; }
bool Predmet::aktivan() const { return trajanje > 0; }

std::string Predmet::naziv() const {
    switch (tip) {
    case TipPredmeta::MAGLA: return "Magla rata";
    case TipPredmeta::MAC: return "Mac";
    case TipPredmeta::STIT: return "Stit";
    case TipPredmeta::CEKIC: return "Cekic";
    }
    return "Nepoznat";
}

