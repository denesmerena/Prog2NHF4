#ifndef RECEPT_H
#define RECEPT_H

#include <string>
#include "hozzavalo.h"

class Recept {
	std::string nev;
	Hozzavalo** hozzavalok;
	int count;
	int capacity;

	void resize();

public:
	Recept(const std::string& nev);
	~Recept();

	const std::string& getNev() const;
	void hozzavalohozzaad(const Alapanyag& alapanyag, double mennyiseg);
	int getHozzavaloCount() const;
	const Hozzavalo* getHozzavalo(int index) const;

	friend std::ostream& operator<<(std::ostream& os, const Recept& recept);
};

#endif