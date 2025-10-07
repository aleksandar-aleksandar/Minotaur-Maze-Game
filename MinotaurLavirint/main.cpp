#include "Lavirint.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

    int dim1, dim2, brojPredmeta;

    cout << "Unesite dimenzije lavirinta (visina i sirina): ";
    cin >> dim1 >> dim2;

    if (dim1 < 4 || dim2 < 4) {
        cout << "Dimenzije lavirinta moraju biti najmanje 4x4.\n";
        dim1 = max(dim1, 4);
        dim2 = max(dim2, 4);
    }

    cout << "Unesite broj predmeta: ";
    cin >> brojPredmeta;

    Lavirint lavirint(dim1, dim2, brojPredmeta);
    lavirint.generisiLavirint();
    lavirint.ispisiLavirint();
    lavirint.izbrojElemente();
    lavirint.ispisiAktivnePredmete();

    bool run = true;

    while (run) {

        if (lavirint.proveriPoraz()) {
            cout << "Poraz";
            lavirint.ispisiAsciiPoraz();
            return 0;
        }

        lavirint.ispisiLavirint();

        if (lavirint.proveriPobedu()) {
            cout << "Pobeda";
            lavirint.ispisiAsciiPobeda();
            return 0;
        }

        cout << "Unesite komandu za kretanje (W, A, S, D) ili X za izlaz: ";

        string unos;
        getline(cin, unos);

        if (unos.size() != 1) {
            cout << "Neispravan unos! Unesite samo jednu komandu (W, A, S, D, ili X).\n";
            continue; 
        }

        char x = tolower(unos[0]);

        if (x == 'x') {
            run = false;
        }
        else if (x == 'w') {
            lavirint.odigrajPotez(-1, 0);
        }
        else if (x == 'a') {
            lavirint.odigrajPotez(0, -1);
        }
        else if (x == 's') {
            lavirint.odigrajPotez(1, 0);
        }
        else if (x == 'd') {
            lavirint.odigrajPotez(0, 1);
        }
        else {
            cout << "Ne prepoznajemo komandu! Pokušajte ponovo.\n";
        }

    }

    return 0;
}
