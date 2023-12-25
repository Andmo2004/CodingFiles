#include <iostream>
#include <string>
#include "person.h"

int main(void) 
{

    Person p1("233445", "andres", "Cordoba", "CR", "ES", 11, 3.1, 2001);
    Person p2("234243", "paco", "Cadiz", "CA", "ES", 13, 2.0, 2002);


    std::cout << "Persona 1: " << p1.GetDataStr() << "\n";
    std::cout << "Persona 2: " << p2.GetDataStr() << "\n";


    p1.SetName("kevin");
    p2.SetAge(26);

    p1.SetId("224342");

    std::cout << "Persona 1 nuevos datos: " << p1.GetDataStr() << "\n";
    std::cout << "Persona 2 nuevos datos: " << p2.GetDataStr() << "\n";
}
