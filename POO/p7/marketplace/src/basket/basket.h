#ifndef BASKET_H
#define BASKET_H

// Delaración de la clase Basket

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <list>
#include "product.h"

class Basket{
    private:

        //Crea un mapa
        std::map<std::string,int> product_quantity_;

        // Crea una lista de productos
        std::list<Product> product_list_;

        float total_;

    public:

        Basket(){total_=0.0;};
        void AddProduct(Product p);
        bool DeleteProduct(Product p){return DeleteProduct(p.GetId());};
        bool DeleteProduct(std::string pid);
        void DeleteBasket();
        int GetSize(){return product_list_.size();}
        float GetTotal(){return total_;}
        std::vector<std::string> GetIds();
        std::vector<int> GetQs();

}; 

#endif