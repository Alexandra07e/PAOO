#include "Buffer.hpp"
#include <algorithm>

//3. initializarea membrilor prin member initializer list
Buffer::Buffer(size_t s, int init_val) 
    : size(s), data(s > 0 ? new int[s] : nullptr) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = init_val;
    }
    std::cout << "Alocat buffer de dimensiune " << size 
              << " la adresa " << static_cast<void*>(data) << "\n";
}

//4. eliberarea memoriei de pe heap in destructor
Buffer::~Buffer() {
    std::cout << "Se elibereaza memoria de la adresa " 
              << static_cast<void*>(data) << "\n";
    delete[] data; // Previne memory leak-urile
    data = nullptr;
}

//5. suprascrierea Copy Constructor-ului (DEEP COPY)
// Daca nu il suprascriem, compilatorul genereaza un Shallow Copy implicit
// !!!(detail: doua instante ar pointa catre aceeasi zona de heap, ducand la "double free" crash la distrugere)
Buffer::Buffer(const Buffer& other) 
    : size(other.size), data(other.size > 0 ? new int[other.size] : nullptr) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
    std::cout << "Deep copy (" << size << " elemente). "
              << "Noua adresa: " << static_cast<void*>(data) << "\n";
}

//6. move Constructor (fura pointerul obiectului sursa fara a realoca memorie pe heap)
Buffer::Buffer(Buffer&& other) noexcept 
    : size(other.size), data(other.data) {
    //i-am luat datele => facem null ca sa nu stearga memoria cand crapa
    other.size = 0;
    other.data = nullptr;
    std::cout << "S-au mutat de la adresa " 
              << static_cast<void*>(data) << "\n";
}

size_t Buffer::getSize() const {
    return size;
}

void Buffer::setAt(size_t index, int value) {
    if (index < size) {
        data[index] = value;
    }
}

int Buffer::getAt(size_t index) const {
    if (index < size) {
        return data[index];
    }
    return -1;
}

void Buffer::print() const {
    std::cout << "Buffer (size=" << size << "): [ ";
    for (size_t i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << "]\n";
}