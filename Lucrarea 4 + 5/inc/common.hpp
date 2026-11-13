#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>

// functie ajutatoare pentru afisarea titlurilor de sectiune
inline void header(const char* title) {
    std::cout<<"\n--------------"<<title<<"--------------\n";
}

#endif