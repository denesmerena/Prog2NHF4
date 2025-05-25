#include "recept.h"
#include <stdexcept>

#include "memtrace.h"

Recept::Recept(const std::string& nev)
    : nev(nev), hozzavalok(new Hozzavalo*[10]), count(0), capacity(10) {}

Recept::~Recept() {
    for (int i = 0; i < count; ++i) {
        delete hozzavalok[i];
    }
    delete[] hozzavalok;
}

const std::string& Recept::getNev() const { return nev; }

void Recept::hozzavalohozzaad(const Alapanyag& alapanyag, double mennyiseg) {
    if (count == capacity) {
        resize();
    }
    hozzavalok[count++] = new Hozzavalo(alapanyag, mennyiseg);
}

int Recept::getHozzavaloCount() const { return count; }

void Recept::resize() {
    capacity *= 2;
    Hozzavalo** newHozzavalok = new Hozzavalo*[capacity];
    for (int i = 0; i < count; ++i) {
        newHozzavalok[i] = hozzavalok[i];
    }
    delete[] hozzavalok;
    hozzavalok = newHozzavalok;
}

const Hozzavalo* Recept::operator[](int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Invalid hozzavalo index");
    }
    return hozzavalok[index];
}
