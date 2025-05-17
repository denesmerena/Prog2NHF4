#include "menu.h"
#include "fajlkezelo.h"
#include <iostream>
#include <limits>

Menu::Menu(Tarolo<Alapanyag>& alapanyagTarolo, Tarolo<Recept>& receptTarolo)
    : alapanyagTarolo(alapanyagTarolo), receptTarolo(receptTarolo) {}

void Menu::clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Menu::displayMenu() const {
    std::cout << "=== Italrecept Nyilvántartó ===\n";
    std::cout << "1. Új alapanyag bevitele\n";
    std::cout << "2. Új recept bevitele\n";
    std::cout << "3. Recept törlése\n";
    std::cout << "4. Hozzávalók listázása\n";
    std::cout << "5. Adatbázis mentése fájlba\n";
    std::cout << "6. Adatbázis betöltése fájlból\n";
    std::cout << "0. Kilépés\n";
    std::cout << "Válassz egy opciót: ";
}

void Menu::ujAlapanyagBevitel() {
    std::string nev, mertekegyseg;

    std::cout << "Új alapanyag neve: ";
    std::getline(std::cin, nev);

    std::cout << "Mértékegység: ";
    std::getline(std::cin, mertekegyseg);

    alapanyagTarolo.add(new Alapanyag(nev, mertekegyseg));
    std::cout << "Sikeres alapanyag bevitel.\n\n";
}

void Menu::ujReceptBevitel() {
    if (alapanyagTarolo.getMennyiseg() == 0) {
        std::cout << "Nincsenek alapanyagok a recepthez. Először adjon hozzá alapanyagokat!\n\n";
        return;
    }

    std::string nev;
    std::cout << "Új recept neve: ";
    std::getline(std::cin, nev);

    Recept* ujRecept = new Recept(nev);
    char valasz;

    do {
        std::cout << "\nElérhető alapanyagok:\n";
        for (int i = 0; i < alapanyagTarolo.getMennyiseg(); ++i) {
            std::cout << i+1 << ". " << *alapanyagTarolo[i] << "\n";
        }

        int alapanyagIndex;
        double mennyiseg;

        std::cout << "Válassza ki az alapanyag sorszámát: ";
        std::cin >> alapanyagIndex;
        clearInputBuffer();

        if (alapanyagIndex < 1 || alapanyagIndex > alapanyagTarolo.getMennyiseg()) {
            std::cout << "Érvénytelen sorszám!\n";
            continue;
        }

        std::cout << "Mennyiség (" << alapanyagTarolo[alapanyagIndex-1]->getMertekegyseg() << "): ";
        std::cin >> mennyiseg;
        clearInputBuffer();

        ujRecept->hozzavalohozzaad(*alapanyagTarolo[alapanyagIndex-1], mennyiseg);

        std::cout << "Szeretne még hozzávalót hozzáadni? (i/n): ";
        std::cin >> valasz;
        clearInputBuffer();
    } while (valasz == 'i' || valasz == 'I');

    receptTarolo.add(ujRecept);
    std::cout << "Recept mentve.\n\n";
}

void Menu::receptTorles() {
    if (receptTarolo.getMennyiseg() == 0) {
        std::cout << "Nincsenek receptek a törléshez.\n\n";
        return;
    }

    std::cout << "Elérhető receptek:\n";
    for (int i = 0; i < receptTarolo.getMennyiseg(); ++i) {
        std::cout << i+1 << ". " << receptTarolo[i]->getNev() << "\n";
    }

    int index;
    std::cout << "Válassza ki a törlendő recept sorszámát: ";
    std::cin >> index;
    clearInputBuffer();

    if (index < 1 || index > receptTarolo.getMennyiseg()) {
        std::cout << "Érvénytelen sorszám!\n\n";
        return;
    }

    // A Tarolo osztályban implementálni kell a remove metódust
    // receptTarolo.remove(index-1);
    std::cout << "Recept törölve.\n\n";
}

void Menu::hozzavalokListazasa() {
    if (receptTarolo.getMennyiseg() == 0) {
        std::cout << "Nincsenek receptek a listázáshoz.\n\n";
        return;
    }

    std::cout << "Elérhető receptek:\n";
    for (int i = 0; i < receptTarolo.getMennyiseg(); ++i) {
        std::cout << i+1 << ". " << receptTarolo[i]->getNev() << "\n";
    }

    int index;
    std::cout << "Válassza ki a recept sorszámát: ";
    std::cin >> index;
    clearInputBuffer();

    if (index < 1 || index > receptTarolo.getMennyiseg()) {
        std::cout << "Érvénytelen sorszám!\n\n";
        return;
    }

    const Recept* recept = receptTarolo[index-1];
    std::cout << "\n" << recept->getNev() << " recept hozzávalói:\n";
    for (int i = 0; i < recept->getHozzavaloCount(); ++i) {
        const Hozzavalo* h = recept->getHozzavalo(i);
        std::cout << "- " << h->getAlapanyag().getNev() << ": "
                  << h->getMennyiseg() << " "
                  << h->getAlapanyag().getMertekegyseg() << "\n";
    }
    std::cout << "\n";
}

void Menu::adatbazisMentes() {
    std::string fajlnev;
    std::cout << "Adja meg a fájl nevét: ";
    std::getline(std::cin, fajlnev);

    try {
        Fajlkezelo::mentes(receptTarolo, alapanyagTarolo, fajlnev);
        std::cout << "Adatbázis sikeresen mentve a '" << fajlnev << "' fájlba.\n\n";
    } catch (const std::exception& e) {
        std::cerr << "Hiba történt a mentés során: " << e.what() << "\n\n";
    }
}

void Menu::adatbazisBetoltes() {
    std::string fajlnev;
    std::cout << "Adja meg a fájl nevét: ";
    std::getline(std::cin, fajlnev);

    try {
        Fajlkezelo::betoltes(receptTarolo, alapanyagTarolo, fajlnev);
        std::cout << "Adatbázis sikeresen betöltve a '" << fajlnev << "' fájlból.\n\n";
    } catch (const std::exception& e) {
        std::cerr << "Hiba történt a betöltés során: " << e.what() << "\n\n";
    }
}

void Menu::run() {
    int valasztas;

    do {
        displayMenu();
        std::cin >> valasztas;
        clearInputBuffer();

        switch (valasztas) {
            case 1:
                ujAlapanyagBevitel();
                break;
            case 2:
                ujReceptBevitel();
                break;
            case 3:
                receptTorles();
                break;
            case 4:
                hozzavalokListazasa();
                break;
            case 5:
                adatbazisMentes();
                break;
            case 6:
                adatbazisBetoltes();
                break;
            case 0:
                std::cout << "Kilépés...\n";
                break;
            default:
                std::cout << "Érvénytelen választás!\n\n";
                break;
        }
    } while (valasztas != 0);
}