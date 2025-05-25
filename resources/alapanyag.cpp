#include "alapanyag.h"

Alapanyag::Alapanyag(const std::string& nev, const std::string& mertekegyseg)
    : nev(nev), mertekegyseg(mertekegyseg) {}

const std::string& Alapanyag::getNev() const { return nev; }
const std::string& Alapanyag::getMertekegyseg() const { return mertekegyseg; }

std::ostream& operator<<(std::ostream& os, const Alapanyag& alapanyag) {
    os << alapanyag.nev << " (" << alapanyag.mertekegyseg << ")";
    return os;
}
