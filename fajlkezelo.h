#ifndef FAJLKEZELO_H
#define FAJLKEZELO_H

#include "tarolo.h"
#include "alapanyag.h"
#include "recept.h"

#include <string>

class Fajlkezelo {
public:
    static void mentes(const Tarolo<Recept>& receptek, const Tarolo<Alapanyag>& alapanyagok, const std::string& fajlnev);
    static void betoltes(Tarolo<Recept>& receptek, Tarolo<Alapanyag>& alapanyagok, const std::string& fajlnev);
};

#endif // FAJLKEZELO_H
