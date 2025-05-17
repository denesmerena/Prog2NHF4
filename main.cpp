#include <iostream>
#include "recept.h"
#include "tarolo.h"
#include "alapanyag.h"
#include "menu.h"


int main() {
    Tarolo<Alapanyag> alapanyagTarolo;
    Tarolo<Recept> receptTarolo;

    try {
        Menu menu(alapanyagTarolo, receptTarolo);
        menu.run();
    } catch (const std::exception& e) {
        std::cerr << "Váratlan hiba történt: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}