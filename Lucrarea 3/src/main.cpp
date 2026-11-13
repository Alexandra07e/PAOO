#include "Buffer.hpp"
#include <utility>

int main() {
    std::cout << "  1.Initializare si Incapsulare\n";
    Buffer b1(4, 10);
    b1.print();
    b1.setAt(0, 99);
    b1.print();

    std::cout << "\n    2.Copy Constructor (Deep Copy)\n";
    Buffer b2 = b1; 
    b2.setAt(1, 77);

    std::cout << "b1 original: ";
    b1.print();
    std::cout << "b2 copie:    ";
    b2.print();

    std::cout << "\n    3.Move Constructor\n";
    Buffer b3 = std::move(b2); 

    std::cout << "b3 (a preluat resursele): ";
    b3.print();
    std::cout << "b2 dupa move:    ";
    b2.print();

    std::cout << "\n    4.Final\n";
    return 0;
}