#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <iostream>
#include <cstddef>

class Buffer {
private:
    //2. încapsulare  (date private inaccesibile direct din exterior)
    size_t size;
    int* data;

public:
    //3. inițializarea membrilor din constructor 
    Buffer(size_t s, int init_val = 0);

    //4. eliberarea heap-ului în cadrul destructorului 
    ~Buffer();

    //5. suprascrierea copy constructor-ului 
    Buffer(const Buffer& other);

    //6. crearea unui move constructor 
    Buffer(Buffer&& other) noexcept;

    //public methods (for incapsulation)
    size_t getSize() const;
    void setAt(size_t index, int value);
    int getAt(size_t index) const;
    void print() const;
};

#endif