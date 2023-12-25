#include <string>
#include <iostream>
#include "person.h"

/***    using namespace std;    ***/

//person-main.cc
//main de la practica 1

namespace ns1{
int a; // Esta es la variable ns1::a
int b; // Esta es la variable ns1::b
}
namespace ns2{
float a; // Esta es la variable ns2::a
float c; // Esta es la variable ns2::c
}

int main(){

    Person p1 = Person("Juan",32,4.56);
    Person p2 = Person("Ana",41,7.3);

    std::cout<<p1.GetName()<<std::endl; 
    std::cout<<p2.GetName()<<std::endl; 

    std::cout<<p1.GetAge()<<std::endl; 
    std::cout<<p2.GetAge()<<std::endl; 

    std::cout<<p1.GetRank()<<std::endl; 
    std::cout<<p2.GetRank()<<std::endl;

    std::cout << p1.GetDataStr() << std::endl;
    std::cout << p2.GetDataStr() << std::endl;
    // Aquí irían las declaraciones de ns1 y ns2

    int a=55;
    ns1::a=0;
    ns2::a=2.3;
    std::cout<< "ns1::a=" << ns1::a << "\n";
    std::cout<< "ns2::a= " << ns2::a << "\n";
    std::cout<< "a= " << a << "\n";

    return 0;

    int numero;
    std::string cadena;

    std::cout << "Introduce el entero con la posición a cambiar del vector."; // Muestra un mensaje al usuario
    std::cin >> numero; // Lee un número entero desde la entrada estándar (teclado)
   
    std::cout << "Por favor, introduce una cadena de texto a cambiar: ";
    std::getline(std::cin, cadena); // Lee una línea completa, incluyendo espacios en blanco

    p1.ChangePreference(numero,cadena);

    std::cout<<"--END--"<<std::endl;

}

