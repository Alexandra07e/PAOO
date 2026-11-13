#ifndef LUCRARE4_HPP
#define LUCRARE4_HPP

#include <string>
#include <type_traits>

//  ITEM 4: Make sure that objects are initialized before they're used.

// (a) atribuire in corpul constructorului (varianta RAU)
class BadInit {
public:
    BadInit(const std::string& title, int credits);
private:
    std::string title_;
    int credits_;
};

extern int g_totalCourses;   // contor extern, referentiat de Course

// varianta BUNA: lista de initializare (obligatorie pentru const si referinte)
class Course {
public:
    Course(const std::string& title, int credits);
    void print() const;
private:
    std::string title_;
    int credits_;
    const int maxStudents_;
    int& counter_;
};

// (b) ordinea initializarii = ordinea DECLARARII in clasa
struct Tracer {
    explicit Tracer(const char* name);
};

class InitOrder {
public:
    InitOrder();
private:
    Tracer second_;   // declarat primul -> initializat primul
    Tracer first_;
};

// (c) obiect static LOCAL (Singleton Meyers) in loc de static non-local
class Logger {
public:
    void log(const std::string& msg) const;
private:
    friend Logger& logger();
    Logger();
};

Logger& logger();


//  ITEM 5: Know what functions C++ silently writes and calls.

// clasa "goala": compilatorul ii scrie ctor, copy ctor, operator=, dtor
class Empty {};

static_assert(std::is_default_constructible<Empty>::value, "ctor implicit generat");
static_assert(std::is_copy_constructible<Empty>::value,    "copy ctor generat");
static_assert(std::is_copy_assignable<Empty>::value,       "operator= generat");
static_assert(std::is_destructible<Empty>::value,          "destructor generat");

// membru referinta / const => compilatorul NU genereaza operator=
class NoAssign {
public:
    NoAssign(int& r, int c) : ref_(r), c_(c) {}
private:
    int& ref_;
    const int c_;
};

static_assert(!std::is_default_constructible<NoAssign>::value,
              "daca declari un constructor, NU se mai genereaza cel implicit");
static_assert(std::is_copy_constructible<NoAssign>::value, "copy ctor se genereaza");
static_assert(!std::is_copy_assignable<NoAssign>::value,
              "operator= NU se genereaza (referinta / const)");

// copy ctor generat = copiere SHALLOW (copiaza doar pointerul)
class ShallowBuf {
public:
    explicit ShallowBuf(int v) : p(new int(v)) {}
    int* p;
    // Cu ~ShallowBuf() { delete p; } ar fi DOUBLE DELETE la copiere.
};

//  ITEM 6: Explicitly disallow the use of compiler-generated functions you do not want.


// varianta C++11: = delete
class Account {
public:
    explicit Account(int id) : id_(id) {}
    Account(const Account&) = delete;
    Account& operator=(const Account&) = delete;
    int id() const { return id_; }
private:
    int id_;
};

// varianta C++03 din carte: baza Uncopyable cu functii private si nedefinite
class Uncopyable {
protected:
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

class HomeForSale : private Uncopyable {};

static_assert(!std::is_copy_constructible<Account>::value,     "Account: copiere interzisa");
static_assert(!std::is_copy_assignable<Account>::value,        "Account: atribuire interzisa");
static_assert(!std::is_copy_constructible<HomeForSale>::value, "HomeForSale: copiere interzisa");
static_assert(!std::is_copy_assignable<HomeForSale>::value,    "HomeForSale: atribuire interzisa");

// functii de demonstratie
void demoItem4();
void demoItem5();
void demoItem6();

#endif