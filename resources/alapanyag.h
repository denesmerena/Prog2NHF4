#ifndef ALAPANYAG_H
#define ALAPANYAG_H

#include <string>
#include <iostream>

/**
 * @brief Egy alapanyagot reprezentáló osztály
 *
 * Az alapanyag egy névből és egy mértékegységből áll, amelyek
 * együtt határozzák meg az alapanyag tulajdonságait.
 */
class Alapanyag {
private:
    std::string nev;          ///< Az alapanyag neve
    std::string mertekegyseg; ///< Az alapanyag mértékegysége (pl. ml, g, db)

public:
    /**
     * @brief Konstruktor egy új alapanyag létrehozásához
     * @param nev Az alapanyag neve
     * @param mertekegyseg Az alapanyag mértékegysége
     */
    Alapanyag(const std::string& nev, const std::string& mertekegyseg);

    /**
     * @brief Név getter
     * @return Az alapanyag neve konstans referenciával
     */
    const std::string& getNev() const;

    /**
     * @brief Mértékegység getter
     * @return Az alapanyag mértékegysége konstans referenciával
     */
    const std::string& getMertekegyseg() const;

    /**
     * @brief Kiíró operátor túlterhelése
     * @param os Output stream referencia
     * @param alapanyag A kiírandó alapanyag objektum
     * @return Referencia a stream objektumra
     *
     * Az alapanyagot "név (mértékegység)" formátumban írja ki
     */
    friend std::ostream& operator<<(std::ostream& os, const Alapanyag& alapanyag);
};

#endif
