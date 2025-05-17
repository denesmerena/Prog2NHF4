#ifndef MENU_H
#define MENU_H

#include "recept.h"
#include "alapanyag.h"
#include "tarolo.h"

class Menu {
private:
    Tarolo<Alapanyag>& alapanyagTarolo;
    Tarolo<Recept>& receptTarolo;

    void clearInputBuffer();
    void ujAlapanyagBevitel();
    void ujReceptBevitel();
    void receptTorles();
    void hozzavalokListazasa();
    void adatbazisMentes();
    void adatbazisBetoltes();
    void displayMenu() const;

public:
    Menu(Tarolo<Alapanyag>& alapanyagTarolo, Tarolo<Recept>& receptTarolo);
    void run();
};

#endif // MENU_H