#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Entitet.h"
#include "Predmet.h"

using namespace std;

class Lavirint {
public:
    int dim1, dim2;
    int brojPredmeta;
    int ulazKolona = rand() % (dim2 - 2) + 1;
    int izlazKolona = rand() % (dim2 - 2) + 1;
    vector<vector<char>> matrica;
    unordered_map<string, int> predmeti;
    
    Entitet Robot;
    Entitet Minotaur;

    Predmet mac;
    Predmet magla;
    Predmet stit;
    Predmet cekic;

    int izlazX, izlazY;

    Lavirint(int d1, int d2, int p);
    void ispisiAsciiPoraz();
    void ispisiAsciiPobeda();
    bool odigrajPotez(int dx, int dy);
    void pomeriMinotaura();
    void generisiLavirint();
    void ispisiLavirint();
    bool prohodan();
    bool proveriPobedu() const;
    bool proveriPoraz();
    void aktivirajPredmet();
    void izbrojElemente();
    void ispisiAktivnePredmete();
    void smanjiTrajanjePredmeta();
    bool okruzen();

private:
    void dfs(int x, int y, vector<vector<bool>>& poseceno);
    void generisiPrimovAlgoritam();
};
