#include "fajlkezelo.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void Fajlkezelo::mentes(const Tarolo<Recept>& receptTarolo,
                       const Tarolo<Alapanyag>& alapanyagTarolo,
                       const std::string& fajlnev) {
    std::ofstream file(fajlnev);
    if (!file) {
        throw std::runtime_error("Could not open file for writing");
    }
    
    // Save alapanyagok
    file << "[Alapanyagok]\n";
    for (int i = 0; i < alapanyagTarolo.getMennyiseg(); ++i) {
        file << alapanyagTarolo[i]->getNev() << ";"
             << alapanyagTarolo[i]->getMertekegyseg() << "\n";
    }
    
    // Save receptek
    file << "\n[Receptek]\n";
    for (int i = 0; i < receptTarolo.getMennyiseg(); ++i) {
        const Recept* recept = receptTarolo[i];
        file << recept->getNev() << ";";
        
        for (int j = 0; j < recept->getHozzavaloCount(); ++j) {
            const Hozzavalo* h = recept->getHozzavalo(j);
            file << h->getAlapanyag().getNev() << ":"
                 << h->getMennyiseg();
            if (j < recept->getHozzavaloCount() - 1) file << ",";
        }
        file << "\n";
    }
}

void Fajlkezelo::betoltes(Tarolo<Recept>& receptTarolo,
                         Tarolo<Alapanyag>& alapanyagTarolo,
                         const std::string& fajlnev) {
    std::ifstream file(fajlnev);
    if (!file) {
        throw std::runtime_error("Could not open file for reading");
    }
    
    std::string line;
    enum Section { NONE, ALAPANYAGOK, RECEPTEK };
    Section currentSection = NONE;
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        if (line == "[Alapanyagok]") {
            currentSection = ALAPANYAGOK;
            continue;
        }
        else if (line == "[Receptek]") {
            currentSection = RECEPTEK;
            continue;
        }
        
        switch (currentSection) {
            case ALAPANYAGOK: {
                size_t delimiter = line.find(';');
                if (delimiter == std::string::npos) continue;
                
                std::string nev = line.substr(0, delimiter);
                std::string mertekegyseg = line.substr(delimiter + 1);
                alapanyagTarolo.add(new Alapanyag(nev, mertekegyseg));
                break;
            }
            case RECEPTEK: {
                size_t nameDelimiter = line.find(';');
                if (nameDelimiter == std::string::npos) continue;
                
                std::string nev = line.substr(0, nameDelimiter);
                Recept* recept = new Recept(nev);
                std::string hozzavalokStr = line.substr(nameDelimiter + 1);
                
                std::istringstream hss(hozzavalokStr);
                std::string hozzavaloPair;
                while (std::getline(hss, hozzavaloPair, ',')) {
                    size_t valueDelimiter = hozzavaloPair.find(':');
                    if (valueDelimiter == std::string::npos) continue;
                    
                    std::string alapanyagNev = hozzavaloPair.substr(0, valueDelimiter);
                    double mennyiseg = std::stod(hozzavaloPair.substr(valueDelimiter + 1));
                    
                    Alapanyag* alapanyag = alapanyagTarolo.keres(alapanyagNev);
                    if (alapanyag) {
                        recept->hozzavalohozzaad(*alapanyag, mennyiseg);
                    }
                }
                receptTarolo.add(recept);
                break;
            }
            default:
                break;
        }
    }
}