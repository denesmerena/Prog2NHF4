#ifndef MENU_H
#define MENU_H

#include "recept.h"
#include "alapanyag.h"
#include "tarolo.h"

/**
 * @brief A felhasználói felületet kezelő osztály
 *
 * Kezeli a felhasználói interakciót és a program fő funkcióit
 */
class Menu {
private:
    Tarolo<Alapanyag>& alapanyagTarolo;  ///< Referencia az alapanyagok tárolójára
    Tarolo<Recept>& receptTarolo;        ///< Referencia a receptek tárolójára

    /**
     * @brief Input buffer tisztítása
     */
    void clearInputBuffer();

    /**
     * @brief Új alapanyag bevitele a felhasználótól
     */
    void ujAlapanyagBevitel();

    /**
     * @brief Új recept bevitele a felhasználótól
     */
    void ujReceptBevitel();

    /**
     * @brief Recept törlése a felhasználó választása alapján
     */
    void receptTorles();

    /**
     * @brief Egy recept hozzávalóinak listázása
     */
    void hozzavalokListazasa();

    /**
     * @brief Adatbázis mentése fájlba
     */
    void adatbazisMentes();

    /**
     * @brief Adatbázis betöltése fájlból
     */
    void adatbazisBetoltes();

    /**
     * @brief Menü megjelenítése
     */
    void displayMenu() const;

public:
    /**
     * @brief Konstruktor
     * @param alapanyagTarolo Referencia az alapanyagok tárolójára
     * @param receptTarolo Referencia a receptek tárolójára
     */
    Menu(Tarolo<Alapanyag>& alapanyagTarolo, Tarolo<Recept>& receptTarolo);

    /**
     * @brief A menürendszer futtatása
     *
     * A fő programhurok, amely kezeli a felhasználói interakciót
     */
    void run();
};

#endif