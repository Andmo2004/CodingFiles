#include <iostream>
#include <string>
#include "contador.h"

Contador::Contador(int val, int val_min, int val_max)
{
    //INICIIAZION DE VALOR
    val_=val;
    val_min_=val_min;
    val_max_=val_max;

    //RESTRICCIONES
    if((val<val_min)||(val>val_max))
    {
        val_=0;
    }
    if(val_min>val_max)
    {
        val_min_=0;
        val_max_=1000;
    }
};

Contador Contador::operator=(int value)
{
    if(value>val_max_){val_=val_max_;}
    else if(value<val_min_){val_=val_min_;}
    else{val_=value;}
    return *this; //??
};

Contador Contador::operator=(const Contador& cont)
{
    if(cont.val_>val_max_){val_=val_max_;}
    else if(cont.val_<val_min_){val_=val_min_;}
    else{val_=cont.val_;}
    return *this;
};

Contador Contador::operator++(void)
{
    if(val_<val_max_){val_++;}
    return *this;
};

Contador Contador::operator++(int)
{
    Contador aux = *this;
    if(val_<val_max_){val_++;}
    return aux;
};

Contador Contador::operator--(void)
{
    if(val_>val_min_){val_--;}
    return *this;
};

Contador Contador::operator--(int)
{
    Contador aux=*this;
    if(val_!=0 && val_!=val_min_){val_--;}
    return aux;
};

int operator+(Contador cont, int i)
{
    if((cont.val_+i)<=cont.val_max_){return (cont.val_+i);}
    return cont.val_max_;
};

int operator+(int i, Contador cont)
{
    if((i+cont.val_)<=cont.val_max_){return (i+cont.val_);}
    return cont.val_max_;
};

int operator-(Contador cont, int i)
{
    if((cont.val_-i)>=cont.val_min_){return(cont.val_-i);}
    return cont.val_min_;
};

int operator-(int i, Contador cont)
{
    if((i-cont.val_)<=cont.val_min_){return(i-cont.val_);}
    return cont.val_min_;
};

std::ostream &operator<<(std::ostream &stream, const Contador &cont){ //insertador
    stream << "Contador: ";
    stream << cont.val_;
    return stream;
};

std::istream &operator>>(std::istream &stream, Contador &cont){ //extractor
    std::cout << "Introduce el valor del contador: ";
    stream >> cont.val_;
    return stream;
};

