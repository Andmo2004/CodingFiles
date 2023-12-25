#include <string>
#include <vector>
#include <iostream>
#include "tv.h"
#include "product.h"

bool Tv::SetInch(float inch){
            if(inch>0){
                inch_ = inch;
                return true;
            }
            else{return false;}
}
std::string Tv::GetDataStr(){
    std::string cad ="Tv: \n";
    cad += "ID: "+ Product::GetId()+"\n";
    return cad;
}