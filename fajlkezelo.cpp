#include "fajlkezelo.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "memtrace.h"

void Fajlkezelo::mentes(const Tarolo<Recept>& receptek, const Tarolo<Alapanyag>& alapanyagok, const std::string& fajlnev) {
    std::ofstream out(fajlnev);
    if (!out) {
        throw std::runtime_error("Nem sikerült megnyitni a fajlt írásra.");
    }

    // Alapanyagok mentése
    out << alapanyagok.getMennyiseg() << '\n';
    for (int i = 0; i < alapanyagok.getMennyiseg(); ++i) {
        out << alapanyagok[i]->getNev() << ';' << alapanyagok[i]->getMertekegyseg() << '\n';
    }

    // Receptek mentése
    out << receptek.getMennyiseg() << '\n';
    for (int i = 0; i < receptek.getMennyiseg(); ++i) {
        const Recept* r = receptek[i];
        out << r->getNev() << '\n';
        out << r->getHozzavaloCount() << '\n';
        for (int j = 0; j < r->getHozzavaloCount(); ++j) {
            const Hozzavalo* h = r->getHozzavalo(j);
            out << h->getAlapanyag().getNev() << ';' << h->getMennyiseg() << '\n';
        }
    }
}

void Fajlkezelo::betoltes(Tarolo<Recept>& receptek, Tarolo<Alapanyag>& alapanyagok, const std::string& fajlnev) {
    std::ifstream in(fajlnev);
    if (!in) {
        throw std::runtime_error("Nem sikerült megnyitni a fajlt olvasásra.");
    }

    // Előző adatok ürítése
    alapanyagok.clear();
    receptek.clear();

    int alapanyagDb;
    in >> alapanyagDb;
    in.ignore(); // sorvége miatt

    // Alapanyagok beolvasása
    for (int i = 0; i < alapanyagDb; ++i) {
        std::string sor;
        std::getline(in, sor);
        std::istringstream iss(sor);
        std::string nev, mertekegyseg;
        if (std::getline(iss, nev, ';') && std::getline(iss, mertekegyseg)) {
            alapanyagok.add(new Alapanyag(nev, mertekegyseg));
        }
    }

    int receptDb;
    in >> receptDb;
    in.ignore();

    for (int i = 0; i < receptDb; ++i) {
        std::string receptNev;
        std::getline(in, receptNev);

        Recept* recept = new Recept(receptNev);

        int hozzavalokSzama;
        in >> hozzavalokSzama;
        in.ignore();

        for (int j = 0; j < hozzavalokSzama; ++j) {
            std::string sor;
            std::getline(in, sor);
            std::istringstream iss(sor);
            std::string alapanyagNev, mennyisegStr;

            if (std::getline(iss, alapanyagNev, ';') && std::getline(iss, mennyisegStr)) {
                std::istringstream mennyisegSS(mennyisegStr);
                double mennyiseg;
                mennyisegSS >> mennyiseg;

                Alapanyag* alapanyag = alapanyagok.keres(alapanyagNev);
                if (alapanyag) {
                    recept->hozzavalohozzaad(*alapanyag, mennyiseg);
                }
            }
        }

        receptek.add(recept);
    }
}

