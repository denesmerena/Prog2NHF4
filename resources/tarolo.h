#ifndef TAROLO_H
#define TAROLO_H

#include <stdexcept>
#include <string>

/**
 * @brief Általános tároló sablon
 * @tparam T A tárolandó elem típusa
 *
 * Dinamikus tömbként működő tároló, amely képes elemek hozzáadására, törlésére
 */
template <typename T>
class Tarolo {
private:
    T** elements;     ///< A tárolt elemek tömbje
    int count;        ///< Az elemek aktuális száma
    int capacity;     ///< A tömb kapacitása

    /**
     * @brief A tömb átméretezése
     * 
     * Akkor hívódik meg, amikor új elem hozzáadásakor nincs elég hely
     */
    void resize();

public:
    /**
     * @brief Alapértelmezett konstruktor
     */
    Tarolo();

    /**
     * @brief Destruktor
     */
    ~Tarolo();

    /**
     * @brief Új elem hozzáadása
     * @param element Az új elem pointere
     */
    void add(T* element);

    /**
     * @brief Elem törlése index alapján
     * @param index A törlendő elem indexe
     * @throw std::out_of_range Ha az index érvénytelen
     */
    void remove(int index);

    /**
     * @brief Összes elem törlése
     */
    void clear();

    /**
     * @brief Indexelő operátor
     * @param index A kért elem indexe
     * @return Pointer a kért elemre
     * @throw std::out_of_range Ha az index érvénytelen
     */
    T* operator[](unsigned int index) const;

    /**
     * @brief Elem keresése név alapján
     * @param nev A keresett elem neve
     * @return Pointer a talált elemre, vagy nullptr ha nincs találat
     */
    T* keres(const std::string& nev) const;

    /**
     * @brief Elemek számának lekérdezése
     * @return Az elemek száma
     */
    int getMennyiseg() const;
};

#endif
