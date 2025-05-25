#ifndef HOZZAVALO_H
#define HOZZAVALO_H

#include "alapanyag.h"
#include <iostream>

/**
 * @brief Egy recept hozzávalóját reprezentáló osztály
 *
 * A hozzávaló egy alapanyagból és annak mennyiségéből áll.
 */
class Hozzavalo {
private:
    Alapanyag alapanyag;  ///< A hozzávaló alapanyaga
    double mennyiseg;     ///< A hozzávaló mennyisége

public:
    /**
     * @brief Konstruktor egy új hozzávaló létrehozásához
     * @param alapanyag Az alapanyag referenciája
     * @param mennyiseg A mennyiség értéke
     */
    Hozzavalo(const Alapanyag& alapanyag, double mennyiseg);

    /**
     * @brief Alapanyag getter
     * @return Az alapanyag konstans referenciája
     */
    const Alapanyag& getAlapanyag() const;

    /**
     * @brief Mennyiség getter
     * @return A mennyiség értéke
     */
    double getMennyiseg() const;

    /**
     * @brief Kiíró operátor
     * @param os Output stream referencia
     * @param hozzavalo A kiírandó hozzávaló
     * @return Az output stream referenciája
     */
    friend std::ostream& operator<<(std::ostream& os, const Hozzavalo& hozzavalo);
};

#endif