#include <string>
#include <vector>
#include <iostream>
#include "computer.h"

int main(){

    Computer p1("HP15FS", Laptop, "HP-OMEN15", 999.9, "HP", "PCCOMP" );
    
    std::cout<< p1.GetId() <<std::endl;
    std::cout<< p1.GetName() <<std::endl;
    std::cout<< p1.GetPrice() <<std::endl;
    std::cout<< p1.GetMaker() <<std::endl;
    std::cout<< p1.GetSeller() <<std::endl;
    std::cout<< p1.GetType() <<std::endl;
    
    return 0;
}