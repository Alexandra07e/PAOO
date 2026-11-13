#ifndef LUCRARE5_HPP
#define LUCRARE5_HPP

#include <cstddef>
#include <string>

// Clasa pentru Item 10 si Item 11: gestioneaza memorie din heap, deci are
// copy ctor / operator= / destructor proprii.
class Buffer {
public:
    explicit Buffer(std::size_t size = 0, int fill = 0);
    Buffer(const Buffer& rhs);       // deep copy
    ~Buffer();

    Buffer& operator=(const Buffer& rhs);   // ITEM 10 + ITEM 11
    Buffer& operator+=(int v);              // ITEM 10 (si pentru operatori compusi)

    std::size_t size() const { return size_; }
    int& operator[](std::size_t i) { return data_[i]; }
    const int& operator[](std::size_t i) const { return data_[i]; }

private:
    std::size_t size_;
    int* data_;
};

// ITEM 11: varianta GRESITA, doar pentru demonstratie
class UnsafeBuffer {
public:
    explicit UnsafeBuffer(std::size_t size);
    ~UnsafeBuffer();
    UnsafeBuffer(const UnsafeBuffer&) = delete;
    UnsafeBuffer& operator=(const UnsafeBuffer& rhs);

    std::size_t size() const { return size_; }
private:
    std::size_t size_;
    int* data_;
};

// ITEM 12: Copy all parts of an object
class Customer {
public:
    Customer();
    explicit Customer(const std::string& n);
    Customer(const Customer& rhs);
    Customer& operator=(const Customer& rhs);
    virtual ~Customer() {}
    const std::string& name() const { return name_; }
private:
    std::string name_;
};

// GRESIT: uita partea de baza
class BadVipCustomer : public Customer {
public:
    BadVipCustomer(const std::string& n, int p);
    BadVipCustomer(const BadVipCustomer& rhs);
    BadVipCustomer& operator=(const BadVipCustomer& rhs);
    int priority() const { return priority_; }
private:
    int priority_;
};

// CORECT: copiaza TOATE partile
class VipCustomer : public Customer {
public:
    VipCustomer(const std::string& n, int p);
    VipCustomer(const VipCustomer& rhs);
    VipCustomer& operator=(const VipCustomer& rhs);
    int priority() const { return priority_; }
private:
    int priority_;
};

void demoItems10to12();

#endif