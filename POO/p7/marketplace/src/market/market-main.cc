#include <iostream>
#include "market.h"

int main(){
    
    Market m("Te gusta conducir? -BMW");     
    std::cout<<m.GetSlogan()<<std::endl;
    return 0;
}