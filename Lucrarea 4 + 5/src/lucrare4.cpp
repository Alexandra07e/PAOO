#include "lucrare4.hpp"
#include "common.hpp"
#include <iostream>

// ------------------------------- ITEM 4 --------------------------------------

// RAU: membrii sunt mai intai default-initializati, apoi ATRIBUIT.
// Pentru int, daca uitam credits_ = credits; ramane valoare GUNOI.
BadInit::BadInit(const std::string& title, int credits) {
    title_ = title;
    credits_ = credits;
}

int g_totalCourses = 0;

// BUN: lista de initializare. OBLIGATORIE pentru membri const si referinte.
Course::Course(const std::string& title, int credits)
    : title_(title),
      credits_(credits),
      maxStudents_(30),          // membru const     -> doar in lista
      counter_(g_totalCourses)   // membru referinta -> doar in lista
{
    ++counter_;
}

void Course::print() const {
    std::cout << "  Course{" << title_ << ", " << credits_ << " credite, max "
              << maxStudents_ << " studenti}\n";
}

Tracer::Tracer(const char* name) {
    std::cout << "  init " << name << '\n';
}

// Scriem first_ inainte de second_, dar in clasa second_ e declarat primul
// => se initializeaza second_, apoi first_.
// (Warning-ul -Wreorder este INTENTIONAT aici.)
InitOrder::InitOrder() : first_("first_"), second_("second_") {}

Logger::Logger() { std::cout << "  (Logger construit la primul apel)\n"; }

void Logger::log(const std::string& msg) const {
    std::cout << "  [LOG] " << msg << '\n';
}

Logger& logger() {
    static Logger instance;   // static local: initializat la primul apel
    return instance;
}

void demoItem4() {
    header("ITEM 4: initializarea obiectelor");

    Course c("POO", 5);
    c.print();
    std::cout << "  g_totalCourses = " << g_totalCourses << '\n';

    std::cout << " Ordinea initializarii membrilor:\n";
    InitOrder order;
    (void)order;

    std::cout << " Singleton (static local):\n";
    logger().log("salut");
}

// ------------------------------- ITEM 5 --------------------------------------

void demoItem5() {
    header("ITEM 5: functiile scrise silentios de compilator");

    Empty e1;
    Empty e2(e1);   // copy ctor generat
    e2 = e1;        // operator= generat
    std::cout << "  Empty: ctor, copy ctor, operator=, dtor generate (static_assert in .hpp)\n";

    std::cout << " Copiere shallow (generata de compilator):\n";
    ShallowBuf a(1);
    ShallowBuf b = a;   // copiaza pointerul, nu valoarea
    *b.p = 99;
    std::cout << "  *a.p = " << *a.p << "  (am modificat doar b, dar a s-a schimbat!)\n";
    std::cout << "  a.p == b.p ? " << std::boolalpha << (a.p == b.p) << '\n';
    delete a.p;         // stergem O SINGURA data (b.p e acelasi pointer)
}

// ------------------------------- ITEM 6 --------------------------------------

void demoItem6() {
    header("ITEM 6: interzicerea functiilor generate");

    Account acc(42);
    std::cout << "  Account id = " << acc.id() << '\n';
    // Account acc2(acc);              // EROARE: use of deleted function
    // Account acc3(0); acc3 = acc;    // EROARE: use of deleted function
    HomeForSale h1;
    (void)h1;
    // HomeForSale h2(h1);             // EROARE: copy ctor inaccesibil
    std::cout << "  Liniile de copiere sunt comentate: decomenteaza-le ca sa vezi eroarea.\n";
}