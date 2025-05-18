#include "tarolo.h"
#include <algorithm>

#include "recept.h"

#include "memtrace.h"

template <typename T>
Tarolo<T>::Tarolo() : elements(new T*[10]), count(0), capacity(10) {}

template <typename T>
Tarolo<T>::~Tarolo() {
    for (int i = 0; i < count; ++i) {
        delete elements[i];
    }
    delete[] elements;
}

template <typename T>
void Tarolo<T>::add(T* element) {
    if (count == capacity) {
        resize();
    }
    elements[count++] = element;
}

template <typename T>
T* Tarolo<T>::operator[](unsigned int index) const {
    if (index >= static_cast<unsigned int>(count)) {
        throw std::out_of_range("Index out of range");
    }
    return elements[index];
}

template <typename T>
T* Tarolo<T>::keres(const std::string& nev) const {
    for (int i = 0; i < count; ++i) {
        if (elements[i]->getNev() == nev) {
            return elements[i];
        }
    }
    return nullptr;
}

template <typename T>
int Tarolo<T>::getMennyiseg() const {
    return count;
}

template <typename T>
void Tarolo<T>::resize() {
    capacity *= 2;
    T** newElements = new T*[capacity];
    std::copy(elements, elements + count, newElements);
    delete[] elements;
    elements = newElements;
}

template <typename T>
void Tarolo<T>::remove(int index) {
    if (index < 0 || index >= count) throw std::out_of_range("Index out of range");
    delete elements[index];
    for (int i = index; i < count - 1; ++i) {
        elements[i] = elements[i + 1];
    }
    --count;
}

// Explicit instantiations
template class Tarolo<Alapanyag>;
template class Tarolo<Recept>;