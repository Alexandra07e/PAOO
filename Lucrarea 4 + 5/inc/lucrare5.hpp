#ifndef LUCRARE5_HPP
#define LUCRARE5_HPP

#include <cstddef>
#include <string>

// Clasa cu memorie din heap (data_). Are nevoie de copy constructor, operator= si destructor proprii.
class Buffer {
public:
    Buffer(std::size_t size, int fill);
    Buffer(const Buffer& rhs);               // copiaza si datele (deep copy)
    ~Buffer();                               // elibereaza heap-ul

    Buffer& operator=(const Buffer& rhs);    // ITEM 10 si ITEM 11

    std::size_t size() const { return size_; }
    int first() const { return data_[0]; }
private:
    std::size_t size_;
    int* data_;
};

// ITEM 12: Copy all parts of an object
class Customer {
public:
    Customer();
    explicit Customer(const std::string& name);
    Customer(const Customer& rhs);
    Customer& operator=(const Customer& rhs);
    const std::string& name() const { return name_; }
private:
    std::string name_;
};

// GRESIT: copiaza doar membrul propriu, uita partea de baza (Customer)
class BadVipCustomer : public Customer {
public:
    BadVipCustomer(const std::string& name, int priority);
    BadVipCustomer(const BadVipCustomer& rhs);
    int priority() const { return priority_; }
private:
    int priority_;
};

// CORECT: copiaza TOATE partile (baza + membrul propriu)
class VipCustomer : public Customer {
public:
    VipCustomer(const std::string& name, int priority);
    VipCustomer(const VipCustomer& rhs);
    VipCustomer& operator=(const VipCustomer& rhs);
    int priority() const { return priority_; }
private:
    int priority_;
};

void demoItems10to12();

#endif