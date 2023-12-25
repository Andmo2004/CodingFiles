#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <list>
#include "basket.h"
#include "product.h"

//Añade un producto a la cesta:
void Basket::AddProduct(Product p1) {
    
    if (product_quantity_.count(p1.GetId()) == 0) {
        // Si el producto no existe en el mapa, te dice que no existe.
        product_list_.push_back(p1);
        product_quantity_[p1.GetId()]=1;
        std::cout<<"Ese producto no existe...\n"; 
        
     } 
    else {
        // Si el producto ya existe en el mapa, incrementa la cantidad en 1.
        product_quantity_[p1.GetId()]++; 
       
    }
    
    total_+=p1.GetPrice();
}

//Eliminar un producto de la cesta:
bool Basket::DeleteProduct(std::string pid){
    float price;
    if (product_list_.empty()) return false;

    for(auto it=product_list_.begin(); it!=product_list_.end();it++)
     if(it->GetId()==pid){
        price=it->GetPrice();
        if(product_quantity_[it->GetId()]>1){
            product_quantity_[it->GetId()]=product_quantity_[it->GetId()]-1;
        }
        else{
            product_quantity_.erase(pid);
            product_list_.erase(it);
        }
        total_-=price;
        return true;
     }
    return false;
}

void Basket::DeleteBasket(){
    product_list_.clear();
    product_quantity_.clear();
    total_=0.0;
}

std::vector<std::string> Basket::GetIds() {
    std::vector<std::string> vecaux;

    if (product_list_.empty()) {
        return vecaux;
    } else {
        for (auto it = product_list_.begin(); it != product_list_.end(); it++) {
            vecaux.push_back(it->GetId());
        }
    }

    return vecaux;
}


std::vector<int> Basket::GetQs() {
    std::vector<int> vec2;

    if (product_list_.empty()) {
        return vec2;
    } else {
        for (auto it = product_list_.begin(); it != product_list_.end(); it++) {
            vec2.push_back(product_quantity_[it->GetId()]);
        }
    }

    return vec2;
}
