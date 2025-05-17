#ifndef ALAPANYAG_H
#define ALAPANYAG_H

#include <string>
#include <iostream>

class Alapanyag {
	std::string nev;
	std::string mertekegyseg;

public:
	Alapanyag(const std::string& nev, const std::string& mertekegyseg);

	const std::string& getNev() const;
	const std::string& getMertekegyseg() const;

	friend std::ostream& operator<<(std::ostream& os, const Alapanyag& alapanyag);
};

#endif