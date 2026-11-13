#include "lucrare5.hpp"
#include "common.hpp"

#include <algorithm>
#include <iostream>

// ------------------------- Buffer (Item 10 + 11) -----------------------------

Buffer::Buffer(std::size_t size, int fill)
    : size_(size), data_(size ? new int[size] : nullptr) {
    std::fill(data_, data_ + size_, fill);
}

Buffer::Buffer(const Buffer& rhs)
    : size_(rhs.size_), data_(rhs.size_ ? new int[rhs.size_] : nullptr) {
    std::copy(rhs.data_, rhs.data_ + size_, data_);
}

Buffer::~Buffer() { delete[] data_; }

// ITEM 10: intoarce referinta la *this
// ITEM 11: trateaza atribuirea la sine
Buffer& Buffer::operator=(const Buffer& rhs) {
    if (this == &rhs) return *this;          // ITEM 11: identity test

    // ITEM 11 (exception safety): alocam INAINTE sa stergem. Daca new arunca,
    // *this ramane neschimbat.
    int* newData = rhs.size_ ? new int[rhs.size_] : nullptr;
    std::copy(rhs.data_, rhs.data_ + rhs.size_, newData);

    delete[] data_;
    data_ = newData;
    size_ = rhs.size_;

    return *this;                            // ITEM 10
}
// Alternativa (copy-and-swap): Buffer& operator=(Buffer rhs){ swap(rhs); return *this; }

Buffer& Buffer::operator+=(int v) {
    for (std::size_t i = 0; i < size_; ++i) data_[i] += v;
    return *this;                            // ITEM 10
}

// ----------------------- UnsafeBuffer (Item 11, GRESIT) ----------------------

UnsafeBuffer::UnsafeBuffer(std::size_t size) : size_(size), data_(new int[size]()) {}
UnsafeBuffer::~UnsafeBuffer() { delete[] data_; }

UnsafeBuffer& UnsafeBuffer::operator=(const UnsafeBuffer& rhs) {
    delete[] data_;                 // daca &rhs == this, am sters SI datele lui rhs!
    if (this == &rhs) {
        // In codul real ar urma new + copiere din rhs.data_ (pointer dangling = UB).
        // Aici doar simulam rezultatul ca sa nu rulam UB.
        std::cout << "  BUG: self-assignment -> datele au fost sterse inainte sa fie copiate!\n";
        data_ = nullptr;
        size_ = 0;
        return *this;
    }
    data_ = new int[rhs.size_];
    std::copy(rhs.data_, rhs.data_ + rhs.size_, data_);
    size_ = rhs.size_;
    return *this;
}

// ----------------------------- ITEM 12: Customer -----------------------------

Customer::Customer() : name_("<default-constructed>") {}
Customer::Customer(const std::string& n) : name_(n) {}
Customer::Customer(const Customer& rhs) : name_(rhs.name_) {}
Customer& Customer::operator=(const Customer& rhs) {
    name_ = rhs.name_;
    return *this;
}

// GRESIT
BadVipCustomer::BadVipCustomer(const std::string& n, int p) : Customer(n), priority_(p) {}

// Uitat: Customer(rhs) => baza e construita cu constructorul IMPLICIT!
// (Warning-ul -Wextra "should be explicitly initialized" este INTENTIONAT.)
BadVipCustomer::BadVipCustomer(const BadVipCustomer& rhs) : priority_(rhs.priority_) {}

// Uitat: Customer::operator=(rhs) => partea de baza ramane neschimbata
BadVipCustomer& BadVipCustomer::operator=(const BadVipCustomer& rhs) {
    priority_ = rhs.priority_;
    return *this;
}

// CORECT
VipCustomer::VipCustomer(const std::string& n, int p) : Customer(n), priority_(p) {}

VipCustomer::VipCustomer(const VipCustomer& rhs)
    : Customer(rhs),                 // copiem partea de baza
      priority_(rhs.priority_) {}

VipCustomer& VipCustomer::operator=(const VipCustomer& rhs) {
    Customer::operator=(rhs);        // atribuim partea de baza
    priority_ = rhs.priority_;
    return *this;                    // ITEM 10
}
// Nota: nu apela copy ctor din operator= sau invers; pune codul comun intr-o
// functie privata (ex. init()).

// -------------------------------- DEMO ---------------------------------------

void demoItems10to12() {
    header("ITEM 10: operator= intoarce *this");
    Buffer a(3, 1), b(3, 2), c(3, 3);
    a = b = c;   // functioneaza doar pentru ca operator= intoarce Buffer&
    std::cout << "  dupa a = b = c: a[0]=" << a[0] << " b[0]=" << b[0] << " c[0]=" << c[0] << '\n';
    (a += 10) += 5;
    std::cout << "  dupa (a += 10) += 5: a[0]=" << a[0] << '\n';

    header("ITEM 11: atribuirea la sine");
    std::cout << " Varianta corecta:\n";
    Buffer s(4, 7);
    s = s;
    std::cout << "  s.size()=" << s.size() << " s[0]=" << s[0] << " (neschimbat)\n";
    std::cout << " Varianta gresita (UnsafeBuffer):\n";
    UnsafeBuffer u(4);
    u = u;
    std::cout << "  u.size()=" << u.size() << "  (datele s-au pierdut)\n";

    header("ITEM 12: copiaza toate partile obiectului");
    BadVipCustomer bad1("Ana", 5);
    BadVipCustomer bad2(bad1);
    std::cout << "  [GRESIT] original: " << bad1.name() << ", copie: " << bad2.name()
              << "  (prioritatea s-a copiat: " << bad2.priority() << ", numele NU)\n";

    VipCustomer good1("Ana", 5);
    VipCustomer good2(good1);
    std::cout << "  [CORECT] original: " << good1.name() << ", copie: " << good2.name()
              << ", prioritate copie: " << good2.priority() << '\n';
}