#ifndef FAJLKEZELO_H
#define FAJLKEZELO_H

#include "tarolo.h"
#include "recept.h"
#include "alapanyag.h"
#include <string>

/**
 * @brief Fájlkezelő osztály az adatok mentéséhez és betöltéséhez
 *
 * Statikus metódusokat tartalmaz a receptek és alapanyagok fájlba mentéséhez
 * és fájlból való betöltéséhez
 */
class Fajlkezelo {
public:
    /**
     * @brief Adatok mentése fájlba
     * @param receptTarolo A recepteket tartalmazó tároló
     * @param alapanyagTarolo Az alapanyagokat tartalmazó tároló
     * @param fajlnev A célfájl neve
     * @throw std::runtime_error Ha a fájl nem nyitható meg
     */
    static void mentes(const Tarolo<Recept>& receptTarolo,
                      const Tarolo<Alapanyag>& alapanyagTarolo,
                      const std::string& fajlnev);

    /**
     * @brief Adatok betöltése fájlból
     * @param receptTarolo A recepteket tartalmazó tároló
     * @param alapanyagTarolo Az alapanyagokat tartalmazó tároló
     * @param fajlnev A forrásfájl neve
     * @throw std::runtime_error Ha a fájl nem nyitható meg vagy hibás formátumú
     */
    static void betoltes(Tarolo<Recept>& receptTarolo,
                        Tarolo<Alapanyag>& alapanyagTarolo,
                        const std::string& fajlnev);
};

#endif