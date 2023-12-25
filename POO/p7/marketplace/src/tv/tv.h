#ifndef TV_H
#define TV_H

// Delaración de la clase Person

#include <string>
#include <vector>
#include <iostream>
#include "product.h"


class Tv : public Product{
    private:
        float inch_;

    public:
        Tv(std::string id, std::string name="empty", 
        float price = 0.0, std::string maker="empty", std::string seller="empty", 
        float inch = 0.0):Product(id,name,price,maker,seller){inch_=inch;};
    //GETS
        float GetInch(){return inch_;}
        std::string GetDataStr();
    //SETS
        bool SetInch(float inch);

};

#endif