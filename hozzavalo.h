#ifndef HOZZAVALO_H
#define HOZZAVALO_H

#include "alapanyag.h"

class Hozzavalo {
	const Alapanyag& alapanyag;  // pointer a referencia helyett
	double mennyiseg;

public:
	Hozzavalo(const Alapanyag& alapanyag, double mennyiseg);

	const Alapanyag& getAlapanyag() const;
	double getMennyiseg() const;

	friend std::ostream& operator<<(std::ostream& os, const Hozzavalo& hozzavalo);
};

#endif
