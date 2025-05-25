#ifndef RECEPT_H
#define RECEPT_H

#include <string>
#include "hozzavalo.h"

/**
 * @brief Italreceptet reprezentáló osztály
 *
 * A recept névből és hozzávalók dinamikus tömbéből áll.
 */
class Recept {
private:
    std::string nev;          ///< A recept neve
    Hozzavalo** hozzavalok;   ///< A hozzávalók dinamikus tömbje
    int count;                ///< A hozzávalók aktuális száma
    int capacity;             ///< A tömb kapacitása

    /**
     * @brief A hozzávalók tömbjének átméretezése
     * 
     * Akkor hívódik meg, amikor új elem hozzáadásakor nincs elég hely
     */
    void resize();

public:
    /**
     * @brief Konstruktor új recept létrehozásához
     * @param nev A recept neve
     */
    Recept(const std::string& nev);

    /**
     * @brief Destruktor
     *
     * Felszabadítja a dinamikusan foglalt memóriaterületeket
     */
    ~Recept();

    /**
     * @brief Név getter
     * @return A recept neve
     */
    const std::string& getNev() const;

    /**
     * @brief Új hozzávaló hozzáadása a recepthez
     * @param alapanyag Az alapanyag referenciája
     * @param mennyiseg A hozzávaló mennyisége
     */
    void hozzavalohozzaad(const Alapanyag& alapanyag, double mennyiseg);

    /**
     * @brief Hozzávalók számának lekérdezése
     * @return A hozzávalók száma
     */
    int getHozzavaloCount() const;

    /**
     * @brief Adott indexű hozzávaló lekérdezése
     * @param index A hozzávaló indexe
     * @return Pointer a hozzávalóra
     * @throw std::out_of_range Ha az index érvénytelen
     */
    const Hozzavalo* operator[] (int index) const;
};



#endif
