#ifndef TAROLO_H
#define TAROLO_H

#include <stdexcept>
#include <string>

template <typename T>
class Tarolo {
    T** elements;
    int count;
    int capacity;

    void resize();

public:
    Tarolo();
    ~Tarolo();
    
    void add(T* element);
    T* operator[](unsigned int index) const;
    T* keres(const std::string& nev) const;
    int getMennyiseg() const;
};

#endif