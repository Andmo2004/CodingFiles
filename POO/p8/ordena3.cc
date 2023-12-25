#include <iostream>
#include <vector>
#include <algorithm>

bool wayToSort(int i, int j)
{
    return i<j;
}

int main()
{
    float numero;
    int option;

    std::cout << "Introduzca el nº de elementos del vector: ";
    std::cin>>numero;

    std::vector<float> vec(numero);

    for(int i=0; i<numero; i++)
    {
        std::cout << i << std::endl;
        std::cin >> vec[i];
    }
    std::cout << "\nComo quieres ordenar el vector?\n";
    std::cout << "1.-Descendente \n";
    std::cout << "2.-Ascendente \n";
    std::cout << "Seleciona una opción: ";
    std::cin >> option;
    
    switch(option)
    {
        case 1:
            std::sort(vec.begin(), vec.end(), std::greater<float>());
            break;
        case 2:
            std::sort(vec.begin(), vec.end(), wayToSort);
            break;
        default:
            std::cout << "\nopción no existente\n";
            break;

    }
    
    std::cout << "\nVector:\n";
    for(int i=0; i<numero; i++)
    {
        std::cout <<"["<< vec[i] <<  "] ";
    }

    return 0;
}