#include <iostream>

template <class Temp>

void print_vector(Temp *vec, int numero)
{
    for(int i=0; i<numero; i++)
    {
        std::cout <<"["<< vec[i] <<  "] ";
    }
}

int main()
{
    int a[6]={2,4,7,1,6,8};
    float b[6]={4.3, 3.2, 2.5, 9.2, 3.4, 3.1};
    char c[5]="Pepe";

    std::cout << "Vector de integers: ";
    print_vector(a,6);

    std::cout << "\nVector de floats: ";
    print_vector(b,6);

    std::cout << "\nVector de string: ";
    print_vector(c,5);

    return 0;
}