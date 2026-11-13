#include "lucrare4.hpp"
#include "common.hpp"

#include <iostream>

// ------------------------------- ITEM 4 ------------------------------------

// GRESIT: membrii sunt mai intai construiti implicit, apoi ATRIBUITI.
// Daca uitam "credits_ = credits;", credits_ ramane cu valoare gunoi.
BadInit::BadInit(const std::string& title, int credits) {
    title_ = title;
    credits_ = credits;
}

// CORECT: lista de initializare (dupa ':') initializeaza direct membrii.
// Pentru membri const (maxStudents_) este OBLIGATORIE.
Course::Course(const std::string& title, int credits)
    : title_(title), credits_(credits), maxStudents_(30) {}

void Course::print() const {
    std::cout << "  Course{" << title_ << ", " << credits_
              << " credite, max " << maxStudents_ << " studenti}\n";
}

void demoItem4() {
    header("ITEM 4: initializarea obiectelor");
    Course c("POO", 5);
    c.print();
}

// ------------------------------- ITEM 5 ------------------------------------

void demoItem5() {
    header("ITEM 5: functii scrise de compilator");

    // Empty nu are nimic scris de noi, dar le putem folosi pe toate:
    Empty e1;        // constructor generat
    Empty e2(e1);    // copy constructor generat
    e2 = e1;         // operator= generat
    std::cout << "  Empty: constructor, copy ctor, operator= si destructor generate\n";

    // PERICOL: copierea generata copiaza doar pointerul, nu valoarea
    ShallowBuf a(1);
    ShallowBuf b = a;   // b.p == a.p (aceeasi zona de memorie)
    *b.p = 99;
    std::cout << "  Am modificat b, dar *a.p = " << *a.p << " (s-a schimbat si a!)\n";
    delete a.p;         // o singura stergere, pentru ca a.p == b.p
}

// ------------------------------- ITEM 6 ------------------------------------

void demoItem6() {
    header("ITEM 6: interzicerea copierii");

    Account acc(42);
    std::cout << "  Account id = " << acc.id() << '\n';

    // erorile de compilare:
    // Account acc2(acc);   // EROARE: use of deleted function (copy constructor)
    // Account acc3(0);
    // acc3 = acc;          // EROARE: use of deleted function (operator=)
}