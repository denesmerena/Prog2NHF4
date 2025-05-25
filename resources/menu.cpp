#include "menu.h"
#include "fajlkezelo.h"
#include <iostream>
#include "memtrace.h"

Menu::Menu(Tarolo<Alapanyag>& alapanyagTarolo, Tarolo<Recept>& receptTarolo)
    : alapanyagTarolo(alapanyagTarolo), receptTarolo(receptTarolo) {}

void Menu::clearInputBuffer() {
    std::cin.clear();
    while (std::cin.peek() != '\n' && std::cin.peek() != EOF) {
        std::cin.ignore(1);
    }
    if (std::cin.peek() == '\n')
        std::cin.ignore(1);
}

void Menu::displayMenu() const {
    std::cout << "=== Italrecept Nyilvantarto ===\n";
    std::cout << "1. uj alapanyag bevitele\n";
    std::cout << "2. uj recept bevitele\n";
    std::cout << "3. Recept torlese\n";
    std::cout << "4. Hozzavalok listazasa\n";
    std::cout << "5. Adatbazis mentese fajlba\n";
    std::cout << "6. Adatbazis betoltese fajlbol\n";
    std::cout << "7. Kilepes\n";
    std::cout << "Valassz egy opciot: ";
}

void Menu::ujAlapanyagBevitel() {
    std::string nev, mertekegyseg;

    std::cout << "uj alapanyag neve: ";
    std::getline(std::cin, nev);

    std::cout << "Mertekegyseg: ";
    std::getline(std::cin, mertekegyseg);

    alapanyagTarolo.add(new Alapanyag(nev, mertekegyseg));
    std::cout << "Sikeres alapanyag bevitel.\n\n";
}

void Menu::ujReceptBevitel() {
    if (alapanyagTarolo.getMennyiseg() == 0) {
        std::cout << "Nincsenek alapanyagok a recepthez. Eloszor adjon hozza alapanyagokat!\n\n";
        return;
    }

    std::string nev;
    std::cout << "uj recept neve: ";
    std::getline(std::cin, nev);

    Recept* ujRecept = new Recept(nev);
    char valasz;

    do {
        std::cout << "\nElerheto alapanyagok:\n";
        for (int i = 0; i < alapanyagTarolo.getMennyiseg(); ++i) {
            std::cout << i+1 << ". " << *alapanyagTarolo[i] << "\n";
        }

        int alapanyagIndex;
        double mennyiseg;

        std::cout << "Valassza ki az alapanyag sorszamat: ";
        std::cin >> alapanyagIndex;
        clearInputBuffer();

        if (alapanyagIndex < 1 || alapanyagIndex > alapanyagTarolo.getMennyiseg()) {
            std::cout << "ervenytelen sorszam!\n";
            continue;
        }

        std::cout << "Mennyiseg (" << alapanyagTarolo[alapanyagIndex-1]->getMertekegyseg() << "): ";
        std::cin >> mennyiseg;
        clearInputBuffer();

        ujRecept->hozzavalohozzaad(*alapanyagTarolo[alapanyagIndex-1], mennyiseg);

        std::cout << "Szeretne meg hozzavalot hozzaadni? (i/n): ";
        std::cin >> valasz;
        clearInputBuffer();
    } while (valasz == 'i' || valasz == 'I');

    receptTarolo.add(ujRecept);
    std::cout << "Recept mentve.\n\n";
}

void Menu::receptTorles() {
    if (receptTarolo.getMennyiseg() == 0) {
        std::cout << "Nincsenek receptek a torleshez.\n\n";
        return;
    }

    std::cout << "Elerheto receptek:\n";
    for (int i = 0; i < receptTarolo.getMennyiseg(); ++i) {
        std::cout << i+1 << ". " << receptTarolo[i]->getNev() << "\n";
    }

    int index;
    std::cout << "Valassza ki a torlendo recept sorszamat: ";
    std::cin >> index;
    clearInputBuffer();

    if (index < 1 || index > receptTarolo.getMennyiseg()) {
        std::cout << "ervenytelen sorszam!\n\n";
        return;
    }
    
    receptTarolo.remove(index-1);
    std::cout << "Recept torolve.\n\n";
}

void Menu::hozzavalokListazasa() {
    if (receptTarolo.getMennyiseg() == 0) {
        std::cout << "Nincsenek receptek a listazashoz.\n\n";
        return;
    }

    std::cout << "Elerheto receptek:\n";
    for (int i = 0; i < receptTarolo.getMennyiseg(); ++i) {
        std::cout << i+1 << ". " << receptTarolo[i]->getNev() << "\n";
    }

    int index;
    std::cout << "Valassza ki a recept sorszamat: ";
    std::cin >> index;
    clearInputBuffer();

    if (index < 1 || index > receptTarolo.getMennyiseg()) {
        std::cout << "ervenytelen sorszam!\n\n";
        return;
    }

    const Recept* recept = receptTarolo[index-1];
    std::cout << "\n" << recept->getNev() << " recept hozzavaloi:\n";
    for (int i = 0; i < recept->getHozzavaloCount(); ++i) {
        const Hozzavalo* h = recept->operator[](i);
        std::cout << "- " << h->getAlapanyag().getNev() << ": "
                  << h->getMennyiseg() << " "
                  << h->getAlapanyag().getMertekegyseg() << "\n";
    }
    std::cout << "\n";
}

void Menu::adatbazisMentes() {
    std::string fajlnev;
    std::cout << "Adja meg a fajl nevet: ";
    std::getline(std::cin, fajlnev);

    try {
        Fajlkezelo::mentes(receptTarolo, alapanyagTarolo, fajlnev);
        std::cout << "Adatbazis sikeresen mentve a '" << fajlnev << "' fajlba.\n\n";
    } catch (const std::exception& e) {
        std::cerr << "Hiba tortent a mentes soran: " << e.what() << "\n\n";
    }
}

void Menu::adatbazisBetoltes() {
    std::string fajlnev;
    std::cout << "Adja meg a fajl nevet: ";
    std::getline(std::cin, fajlnev);

    try {
        Fajlkezelo::betoltes(receptTarolo, alapanyagTarolo, fajlnev);
        std::cout << "Adatbazis sikeresen betoltve a '" << fajlnev << "' fajlbol.\n\n";
    } catch (const std::exception& e) {
        std::cerr << "Hiba tortent a betoltes soran: " << e.what() << "\n\n";
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
            case 7:
                std::cout << "Kilepes...\n";
                break;
            default:
                std::cout << "ervenytelen valasztas!\n\n";
                break;
        }
    } while (valasztas != 7);
}
