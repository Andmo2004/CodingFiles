#include <string>
#include <vector>
#include <iostream>
#include "tv.h"

int main (){
    
    Tv p1("LD090XX","SM-T090LD", 1299.9, "SAMSUNG", "AMAZON", 55.0);

    std::cout<< p1.GetId() <<std::endl;
    std::cout<< p1.GetName() <<std::endl;
    std::cout<< p1.GetPrice() <<std::endl;
    std::cout<< p1.GetMaker() <<std::endl;
    std::cout<< p1.GetSeller() <<std::endl;
    std::cout<< p1.GetInch() <<std::endl;
    
    return 0;
}