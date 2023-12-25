#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
    int numero;

    std::cout << "Inserte el numero de elementos del vector: ";
    std::cin>>numero;

    std::vector<int> vec(numero);

    for(int i=0; i<numero; i++)
    {
        std::cout << "v[" << i << "]: ";
        std::cin >> vec[i];
    }

    std::sort(vec.begin(), vec.end());
    
    std::cout << "\nVector:\n";
    for(int i=0; i<numero; i++)
    {
        std::cout <<"["<< vec[i] <<  "] ";
    }

    return 0;
}