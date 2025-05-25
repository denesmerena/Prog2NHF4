#include "hozzavalo.h"
#include "memtrace.h"

Hozzavalo::Hozzavalo(const Alapanyag& alapanyag, double mennyiseg)
    : alapanyag(alapanyag), mennyiseg(mennyiseg) {}

const Alapanyag& Hozzavalo::getAlapanyag() const {
    return alapanyag;
}

double Hozzavalo::getMennyiseg() const {
    return mennyiseg;
}

std::ostream& operator<<(std::ostream& os, const Hozzavalo& hozzavalo) {
    os << hozzavalo.mennyiseg << " "
       << hozzavalo.alapanyag.getMertekegyseg() << " "
       << hozzavalo.alapanyag.getNev();
    return os;
}
