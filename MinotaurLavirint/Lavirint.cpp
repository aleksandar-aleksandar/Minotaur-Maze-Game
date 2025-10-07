#include "Lavirint.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_map>

using namespace std;

Lavirint::Lavirint(int d1, int d2, int p)
    : dim1(d1), dim2(d2), brojPredmeta(p), matrica(d1, vector<char>(d2, '#')),
    Robot(1, 0), Minotaur(d1 - 2, 0), mac(TipPredmeta::MAC, 0), magla(TipPredmeta::MAGLA, 0), cekic(TipPredmeta::CEKIC, 0), stit(TipPredmeta::STIT, 0)
{
    ulazKolona = rand() % (dim2 - 2) + 1;
    izlazKolona = rand() % (dim2 - 2) + 1;

    Robot.setXY(1, ulazKolona);
    Minotaur.setXY(dim1 - 2, izlazKolona);
}

void Lavirint::generisiLavirint() {
    generisiPrimovAlgoritam();

    matrica[0][ulazKolona] = 'U';
    matrica[dim1 - 1][izlazKolona] = 'I';
    matrica[1][ulazKolona] = 'R';
    matrica[dim1 - 2][izlazKolona] = 'M';

    izlazX = dim1 - 1;
    izlazY = izlazKolona;

    int unutrasnjaPolja = (dim1 - 1) * (dim2 - 1);
    int minZidovi = 2 * (dim1 + dim2); 
    int maksPredmeti = unutrasnjaPolja - minZidovi - 4;

    if (brojPredmeta > maksPredmeti) {
        cout << "Previše predmeta! Maksimalan broj predmeta za dimenzije " << dim1 << "x" << dim2
            << " je " << maksPredmeti << ". Automatski smanjujemo broj predmeta.\n";
        brojPredmeta = maksPredmeti;
    }

    for (int i = 0; i < brojPredmeta; i++) {
        int x, y;
        do {
            x = rand() % (dim1 - 2) + 1;
            y = rand() % (dim2 - 2) + 1;
        } while (matrica[x][y] != '.');

        matrica[x][y] = 'P';
    }
}

void Lavirint::dfs(int x, int y, vector<vector<bool>>& poseceno) {
    if (x < 0 || x >= dim1 || y < 0 || y >= dim2 || matrica[x][y] == '#' || poseceno[x][y]) {
        return;
    }

    poseceno[x][y] = true;

    dfs(x + 1, y, poseceno);
    dfs(x - 1, y, poseceno);
    dfs(x, y + 1, poseceno);
    dfs(x, y - 1, poseceno);
}

bool Lavirint::prohodan() {
    vector<vector<bool>> poseceno(dim1, vector<bool>(dim2, false));
    int ulazY = -1;

    for (int j = 0; j < dim2; j++) {
        if (matrica[0][j] == 'U') {
            ulazY = j;
            break;
        }
    }

    if (ulazY == -1) return false;

    dfs(0, ulazY, poseceno);

    for (int j = 0; j < dim2; j++) {
        if (matrica[dim1 - 1][j] == 'I' && poseceno[dim1 - 1][j]) {
            return true;
        }
    }
    return false;
}

bool Lavirint::proveriPobedu() const {
    return (izlazX == Robot.getX() && izlazY == Robot.getY());
}

bool Lavirint::proveriPoraz() {
    if (Robot.getX()  == Minotaur.getX() && Robot.getY() == Minotaur.getY()) {
        if (mac.aktivan()) {
            std::cout << "Robot je unistio Minotaura pomocu maca!\n";
            matrica[Minotaur.getX()][Minotaur.getY()] = '.';
            Minotaur.pomeri(-1, -1);
            predmeti["Mac"] = 0;
            return false;
        }

        if (stit.aktivan()) {
            std::cout << "Robot je preživeo napad Minotaura pomoću štita!\n";
            stit.iskoristi();
            return false;
        }
        return true;
    }

    return false;
}

void Lavirint::ispisiLavirint() {
    if (magla.aktivan()) {
        int startX = max(0, Robot.getX() - 1);
        int endX = min(dim1 - 1, Robot.getX() + 1);
        int startY = max(0, Robot.getY() - 1);
        int endY = min(dim2 - 1, Robot.getY() + 1);

        for (int i = 0; i < dim1; i++) {
            for (int j = 0; j < dim2; j++) {
                if (i >= startX && i <= endX && j >= startY && j <= endY) {
                    cout << matrica[i][j];
                }
                else {
                    cout << '?';
                }
            }
            cout << endl;
        }
    }
    else {
        for (const auto& red : matrica) {
            for (char polje : red) {
                cout << polje;
            }
            cout << endl;
        }
    }
}

void Lavirint::izbrojElemente() {
    unordered_map<char, int> brojac;
    brojac['#'] = 0;
    brojac['.'] = 0;
    brojac['U'] = 0;
    brojac['R'] = 0;
    brojac['I'] = 0;
    brojac['M'] = 0;
    brojac['P'] = 0;

    for (const auto& red : matrica) {
        for (char polje : red) {
            brojac[polje]++;
        }
    }

    cout << "\n------Statistika lavirinta-------" << endl;
    cout << "Visina: " << dim1 << endl;
    cout << "Sirina: " << dim2 << endl;
    cout << "Zidovi (#): " << brojac['#'] << endl;
    cout << "Zidovi (#) min: " << 2*(dim1+dim2) << endl;
    cout << "Prolazi (.): " << brojac['.'] << endl;
    cout << "Ulaz (U): " << brojac['U'] << endl;
    cout << "Robot (R): " << brojac['R'] << endl;
    cout << "Izlaz (I): " << brojac['I'] << endl;
    cout << "Minotaur (M): " << brojac['M'] << endl;
    cout << "Predmeti (P): " << brojac['P'] << endl;
    cout << "---------------------------------" << endl;

}

void Lavirint::ispisiAktivnePredmete() {
    cout << "\n--- Aktivni predmeti ---\n";

    bool imaAktivnih = false;

    if (magla.aktivan()) {
        cout << magla.naziv() << " (" << magla.getTrajanje() << " poteza preostalo)\n";
        imaAktivnih = true;
    }

    if (mac.aktivan()) {
        cout << mac.naziv() << " (" << mac.getTrajanje() << " poteza preostalo)\n";
        imaAktivnih = true;
    }

    if (stit.aktivan()) {
        cout << stit.naziv() << " (" << stit.getTrajanje() << " poteza preostalo)\n";
        imaAktivnih = true;
    }

    if (cekic.aktivan()) {
        cout << cekic.naziv() << " (" << cekic.getTrajanje() << " poteza preostalo)\n";
        imaAktivnih = true;
    }

    if (!imaAktivnih) {
        cout << "Nema aktivnih predmeta.\n";
    }

    cout << "-------------------------\n";
}

void Lavirint::smanjiTrajanjePredmeta() {
    if (magla.aktivan()) magla.smanjiTrajanje();
    if (mac.aktivan()) mac.smanjiTrajanje();
    if (stit.aktivan()) stit.smanjiTrajanje();
    if (cekic.aktivan()) cekic.smanjiTrajanje();
}

void Lavirint::pomeriMinotaura() {
    if (Minotaur.getX() == -1 && Minotaur.getY() == -1) return; // mrtav

    int mx = Minotaur.getX();
    int my = Minotaur.getY();
    int rx = Robot.getX();
    int ry = Robot.getY();

    int dist = abs(mx - rx) + abs(my - ry);  // Manhattan distance

    vector<pair<int, int>> opcije;

    if (dist <= 3) {
        // Robot je blizu – pokušaj da ga juriš
        if (mx < rx) opcije.push_back({ 1, 0 });
        if (mx > rx) opcije.push_back({ -1, 0 });
        if (my < ry) opcije.push_back({ 0, 1 });
        if (my > ry) opcije.push_back({ 0, -1 });
    }
    else {
        // Robot je daleko – nasumično kretanje
        opcije = { {1,0}, {-1,0}, {0,1}, {0,-1} };
        random_shuffle(opcije.begin(), opcije.end());
    }

    for (auto& p : opcije) {
        int dx = p.first;
        int dy = p.second;

        int noviX = mx + dx;
        int noviY = my + dy;

        if (noviX < 0 || noviX >= dim1 || noviY < 0 || noviY >= dim2) continue;
        if (matrica[noviX][noviY] == '#') continue;

        // Napad na robota
        if (noviX == rx && noviY == ry) {
            if (mac.aktivan()) {
                cout << "Robot je unistio Minotaura pomocu maca!\n";
                matrica[mx][my] = '.';
                Minotaur.setXY(-1, -1);
                mac.setTrajanje(0);
                return;
            }
            else if (stit.aktivan()) {
                cout << "Robot je preziveo napad Minotaura!\n";
                stit.setTrajanje(0);
                return;
            }
            else {
                matrica[mx][my] = '.';
                Minotaur.setXY(noviX, noviY);
                return;
            }
        }

        // Uništavanje predmeta
        if (matrica[noviX][noviY] == 'P') {
            cout << "Minotaur je unistio predmet!\n";
        }

        // Pomeranje
        matrica[mx][my] = '.';
        Minotaur.setXY(noviX, noviY);
        matrica[noviX][noviY] = 'M';
        return;
    }

    // Ako nijedna opcija nije moguća – ostaje u mestu
}

bool Lavirint::odigrajPotez(int dx, int dy) {
    int noviX = Robot.getX() + dx;
    int noviY = Robot.getY() + dy;

    if (noviX < 0 || noviX >= dim1 || noviY < 0 || noviY >= dim2) {
        cout << "Nemoguce se pomeriti: izlazite iz granica lavirinta.\n";
        return false;
    }

    // Ne može da se ide na zid ako nema čekić
    if (matrica[noviX][noviY] == '#' && !cekic.aktivan()) {
        cout << "Nemoguce se pomeriti: zid na tom mestu.\n";
        return false;
    }

    if (matrica[noviX][noviY] == '#' && cekic.aktivan()) {
        cekic.iskoristi();
    }

    // Ne može da ide direktno na Minotaura
    if (noviX == Minotaur.getX() && noviY == Minotaur.getY()) {
        proveriPoraz();
        return false;
    }

    // Smanji trajanje aktivnih predmeta
    smanjiTrajanjePredmeta();

    // Aktiviraj predmet ako postoji
    if (matrica[noviX][noviY] == 'P') {
        aktivirajPredmet();
    }

    // Pomeranje robota
    matrica[Robot.getX()][Robot.getY()] = '.';
    Robot.setXY(noviX, noviY);
    matrica[noviX][noviY] = 'R';

    // Pomeri Minotaura
    pomeriMinotaura();


    // Proveri poraz posle pomeranja Minotaura
    if (proveriPoraz()) {
        ispisiLavirint();
        ispisiAsciiPoraz();
        exit(0);
    }

    // ✅ Provera da li je robot zarobljen
    if (okruzen()) {
        ispisiLavirint();
        ispisiAsciiPoraz();
        exit(0);
    }

    ispisiAktivnePredmete();
    return true;
}

bool Lavirint::okruzen() {
    int x = Robot.getX();
    int y = Robot.getY();

    // 4 smera: gore, dole, levo, desno
    vector<pair<int, int>> okolni = { {-1,0}, {1,0}, {0,-1}, {0,1} };

    for (auto& p : okolni) {
        int nx = x + p.first;
        int ny = y + p.second;

        // Ako je u granicama i nije zid i nije minotaur — može da se pomeri
        if (nx >= 0 && nx < dim1 && ny >= 0 && ny < dim2) {
            char polje = matrica[nx][ny];
            if (polje != '#' && polje != 'M') {
                return false; // nije potpuno blokiran
            }
        }
    }

    // Ako je ovde stigao – okružen je
    if (!stit.aktivan() && !mac.aktivan()) {
        std::cout << "Robot je okružen i nema izlaza. Poraz!\n";
        return true;
    }

    return false;
}

void Lavirint::ispisiAsciiPoraz() {
    cout << "\033[31m"; // Crvena boja
    cout << R"(
██████╗░░█████╗░██████╗░░█████╗░███████╗
██╔══██╗██╔══██╗██╔══██╗██╔══██╗╚════██║
██████╔╝██║░░██║██████╔╝███████║░░███╔═╝
██╔═══╝░██║░░██║██╔══██╗██╔══██║██╔══╝░░
██║░░░░░╚█████╔╝██║░░██║██║░░██║███████╗
╚═╝░░░░░░╚════╝░╚═╝░░╚═╝╚═╝░░╚═╝╚══════╝
    )" << "\033[0m" << endl; // Reset boje
}

void Lavirint::ispisiAsciiPobeda() {
    cout << "\033[32m"; // Crvena boja
    cout << R"(
██████╗░░█████╗░██████╗░███████╗██████╗░░█████╗░
██╔══██╗██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔══██╗
██████╔╝██║░░██║██████╦╝█████╗░░██║░░██║███████║
██╔═══╝░██║░░██║██╔══██╗██╔══╝░░██║░░██║██╔══██║
██║░░░░░╚█████╔╝██████╦╝███████╗██████╔╝██║░░██║
╚═╝░░░░░░╚════╝░╚═════╝░╚══════╝╚═════╝░╚═╝░░╚═╝
    )" << "\033[0m" << endl; // Reset boje
}

void Lavirint::generisiPrimovAlgoritam() {
    srand(time(0));
    vector<pair<int, int>> granice;

    int startX = 1 + rand() % (dim1 - 2);
    int startY = 1 + rand() % (dim2 - 2);
    matrica[startX][startY] = '.';

    granice.push_back({ startX - 1, startY });
    granice.push_back({ startX + 1, startY });
    granice.push_back({ startX, startY - 1 });
    granice.push_back({ startX, startY + 1 });

    while (!granice.empty()) {
        int index = rand() % granice.size();
        int x = granice[index].first;
        int y = granice[index].second;
        granice.erase(granice.begin() + index);

        if (x <= 0 || x >= dim1 - 1 || y <= 0 || y >= dim2 - 1 || matrica[x][y] == '.') continue;

        int count = 0;
        if (matrica[x - 1][y] == '.') count++;
        if (matrica[x + 1][y] == '.') count++;
        if (matrica[x][y - 1] == '.') count++;
        if (matrica[x][y + 1] == '.') count++;

        if (count == 1) {
            matrica[x][y] = '.';
            granice.push_back({ x - 1, y });
            granice.push_back({ x + 1, y });
            granice.push_back({ x, y - 1 });
            granice.push_back({ x, y + 1 });
        }
    }
}

void Lavirint::aktivirajPredmet() {
    srand(time(0));

    int randomPredmet = rand() % 4 + 1;

    if(randomPredmet == 1){
        cout << "Predmet: Magla rata\n";
        magla.setTrajanje(3);
    }
    else if (randomPredmet == 2) {
        cout << "Predmet: Mac\n";
        mac.setTrajanje(3);
    }
    else if (randomPredmet == 3) {
        cout << "Predmet: Stit\n";
        stit.setTrajanje(3);
    }
    else if (randomPredmet == 4) {
        cout << "Predmet: Cekic\n";
        cekic.setTrajanje(3);
    }
}