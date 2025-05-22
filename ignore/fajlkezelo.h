#ifndef FAJLKEZELO_H
#define FAJLKEZELO_H

#include "../tarolo.h"
#include "../recept.h"
#include "../alapanyag.h"
#include <string>

class Fajlkezelo {
public:
	static void mentes(const Tarolo<Recept>& receptTarolo,
					  const Tarolo<Alapanyag>& alapanyagTarolo,
					  const std::string& fajlnev);

	static void betoltes(Tarolo<Recept>& receptTarolo,
						Tarolo<Alapanyag>& alapanyagTarolo,
						const std::string& fajlnev);
};

#endif