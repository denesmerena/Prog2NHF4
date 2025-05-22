#include "fajlkezelo.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "../memtrace.h"

void Fajlkezelo::mentes(const Tarolo<Recept>& receptTarolo,
                        const Tarolo<Alapanyag>& alapanyagTarolo,
                        const std::string& fajlnev) {
    std::ofstream file(fajlnev);
    if (!file) throw std::runtime_error("Fajl megnyitasi hiba");

    // Alapanyagok mentése
    file << "# Alapanyagok\n";
    for (int i = 0; i < alapanyagTarolo.getMennyiseg(); ++i) {
        file << alapanyagTarolo[i]->getNev() << ";"
             << alapanyagTarolo[i]->getMertekegyseg() << "\n";
    }

    // Receptek mentése
    file << "\n# Receptek\n";
    for (int i = 0; i < receptTarolo.getMennyiseg(); ++i) {
        const Recept* recept = receptTarolo[i];
        file << recept->getNev() << ";";

        for (int j = 0; j < recept->getHozzavaloCount(); ++j) {
            const Hozzavalo* h = recept->getHozzavalo(j);
            file << h->getAlapanyag().getNev() << ":" << h->getMennyiseg();
            if (j < recept->getHozzavaloCount() - 1) file << ",";
        }
        file << "\n";
    }
}

void Fajlkezelo::betoltes(Tarolo<Recept>& receptTarolo,
                         Tarolo<Alapanyag>& alapanyagTarolo,
                         const std::string& fajlnev) {
    std::ifstream file(fajlnev);
    if (!file) throw std::runtime_error("Fajl megnyitasi hiba");

    std::string line;
    bool alapanyagok_szekcio = false;
    bool receptek_szekcio = false;

    while (std::getline(file, line)) {
        // Üres sor és kommentek átugrása
        if (line.empty() || line[0] == '#') continue;

        // Szekcióváltás észlelése
        if (line == "# Alapanyagok") {
            alapanyagok_szekcio = true;
            receptek_szekcio = false;
            continue;
        }
        else if (line == "# Receptek") {
            alapanyagok_szekcio = false;
            receptek_szekcio = true;
            continue;
        }

        // Alapanyag feldolgozása
        if (alapanyagok_szekcio) {
            size_t delim = line.find(';');
            if (delim == std::string::npos) continue;

            std::string nev = line.substr(0, delim);
            std::string mertekegyseg = line.substr(delim + 1);
            alapanyagTarolo.add(new Alapanyag(nev, mertekegyseg));
        }
        // Recept feldolgozása
        else if (receptek_szekcio) {
            size_t delim = line.find(';');
            if (delim == std::string::npos) continue;

            std::string nev = line.substr(0, delim);
            Recept* recept = new Recept(nev);

            std::istringstream iss(line.substr(delim + 1));
            std::string hozzavalo;
            while (std::getline(iss, hozzavalo, ',')) {
                size_t colon = hozzavalo.find(':');
                if (colon == std::string::npos) continue;

                std::string alapanyagNev = hozzavalo.substr(0, colon);
                double mennyiseg = std::stod(hozzavalo.substr(colon + 1));

                Alapanyag* alapanyag = alapanyagTarolo.keres(alapanyagNev);
                if (alapanyag) {
                    recept->hozzavalohozzaad(*alapanyag, mennyiseg);
                }
            }
            receptTarolo.add(recept);
        }
    }
}