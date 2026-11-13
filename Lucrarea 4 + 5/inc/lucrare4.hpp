#ifndef LUCRARE4_HPP
#define LUCRARE4_HPP

#include <string>


// ITEM 4: Make sure that objects are initialized before they're used.


// GRESIT: valorile se pun prin ATRIBUIRE in corpul constructorului
class BadInit {
public:
    BadInit(const std::string& title, int credits);
private:
    std::string title_;
    int credits_;
};

// CORECT: valorile se pun in LISTA DE INITIALIZARE
class Course {
public:
    Course(const std::string& title, int credits);
    void print() const;
private:
    std::string title_;
    int credits_;
    const int maxStudents_;   // const -> se poate initializa DOAR in lista
};


// ITEM 5: Know what functions C++ silently writes and calls.


// clasa goala: compilatorul ii scrie singur constructor, copy constructor,
// operator= si destructor
class Empty {};

// pointer brut: copy constructor-ul scris de compilator copiaza DOAR pointerul
class ShallowBuf {
public:
    explicit ShallowBuf(int v) : p(new int(v)) {}
    int* p;
};


// ITEM 6: Explicitly disallow the use of compiler-generated functions you do not want.

// = delete interzice copierea si atribuirea
class Account {
public:
    explicit Account(int id) : id_(id) {}
    Account(const Account&) = delete;
    Account& operator=(const Account&) = delete;
    int id() const { return id_; }
private:
    int id_;
};

void demoItem4();
void demoItem5();
void demoItem6();

#endif