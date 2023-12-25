#include <string>
#include <vector>
#include <iostream>
#include "product.h"

int main(){
Product p1("Caja", "777", 7.0, "Chino", "Chino");

    std::cout<< p1.GetId() <<std::endl;
    std::cout<< p1.GetName() <<std::endl;
    std::cout<< p1.GetPrice() <<std::endl;
    std::cout<< p1.GetMaker() <<std::endl;
    std::cout<< p1.GetSeller() <<std::endl;
    
    return 0;
}