#include "lucrare5.hpp"
#include "common.hpp"

#include <iostream>

// ------------------------------- Buffer ------------------------------------

Buffer::Buffer(std::size_t size, int fill) : size_(size), data_(new int[size]) {
    for (std::size_t i = 0; i < size_; ++i) data_[i] = fill;
}

// copy constructor: aloca memorie noua si copiaza valorile
Buffer::Buffer(const Buffer& rhs) : size_(rhs.size_), data_(new int[rhs.size_]) {
    for (std::size_t i = 0; i < size_; ++i) data_[i] = rhs.data_[i];
}

Buffer::~Buffer() {
    delete[] data_;   // eliberam heap-ul
}

Buffer& Buffer::operator=(const Buffer& rhs) {
    // ITEM 11: atribuirea la sine (s = s).
    // Fara aceasta verificare, "delete[] data_" ar sterge si datele lui rhs
    // (care e chiar obiectul curent), iar apoi am copia din memorie stearsa.
    if (this == &rhs) return *this;

    int* newData = new int[rhs.size_];   // alocam INAINTE sa stergem (daca new
                                         // da exceptie, obiectul ramane intact)
    for (std::size_t i = 0; i < rhs.size_; ++i) newData[i] = rhs.data_[i];

    delete[] data_;
    data_ = newData;
    size_ = rhs.size_;

    // ITEM 10: intoarcem referinta la *this, ca sa mearga a = b = c;
    return *this;
}

// ------------------------------- Customer ----------------------------------

Customer::Customer() : name_("<default-constructed>") {}
Customer::Customer(const std::string& name) : name_(name) {}
Customer::Customer(const Customer& rhs) : name_(rhs.name_) {}
Customer& Customer::operator=(const Customer& rhs) {
    name_ = rhs.name_;
    return *this;
}

// ----- GRESIT -----
BadVipCustomer::BadVipCustomer(const std::string& name, int priority)
    : Customer(name), priority_(priority) {}

// Uitat: Customer(rhs). Partea de baza se construieste cu constructorul
// implicit, deci numele se pierde. (Warning-ul de la compilare e intentionat.)
BadVipCustomer::BadVipCustomer(const BadVipCustomer& rhs)
    : priority_(rhs.priority_) {}

// ----- CORECT -----
VipCustomer::VipCustomer(const std::string& name, int priority)
    : Customer(name), priority_(priority) {}

VipCustomer::VipCustomer(const VipCustomer& rhs)
    : Customer(rhs),               // copiem partea de baza
      priority_(rhs.priority_) {}  // copiem membrul propriu

VipCustomer& VipCustomer::operator=(const VipCustomer& rhs) {
    Customer::operator=(rhs);      // atribuim partea de baza
    priority_ = rhs.priority_;     // atribuim membrul propriu
    return *this;                  // ITEM 10
}

// ------------------------------- DEMO --------------------------------------

void demoItems10to12() {
    header("ITEM 10: operator= intoarce *this");
    Buffer a(3, 1), b(3, 2), c(3, 3);
    a = b = c;   // merge doar pentru ca operator= intoarce Buffer&
    std::cout << "  dupa a = b = c: a=" << a.first() << " b=" << b.first()
              << " c=" << c.first() << '\n';

    header("ITEM 11: atribuirea la sine");
    Buffer s(4, 7);
    s = s;       // fara verificarea this == &rhs, am pierde datele
    std::cout << "  dupa s = s: size=" << s.size() << ", valoare=" << s.first()
              << " (neschimbat)\n";

    header("ITEM 12: copiaza toate partile");
    BadVipCustomer bad1("Ana", 5);
    BadVipCustomer bad2(bad1);
    std::cout << "  GRESIT: original=" << bad1.name() << ", copie=" << bad2.name()
              << " (numele s-a pierdut)\n";

    VipCustomer good1("Ana", 5);
    VipCustomer good2(good1);
    std::cout << "  CORECT: original=" << good1.name() << ", copie=" << good2.name()
              << ", prioritate=" << good2.priority() << '\n';
}