#ifndef PRODUCT_H
#define PRODUCT_H

// Delaración de la clase Person

#include <string>
#include <vector>
#include <iostream>


class Product{

        private:
            std::string name_;
            std::string id_; //poner barra baja detrás del nombre de la variable ( _ ).
            float price_;
            std::string maker_;
            std::string seller_;
        
        public: 
            Product(std::string id, std::string name="empty", float price = 0.0, std::string maker="empty",
            std::string seller="empty"){
                id_ = id;
                name_ = name;
                price_ = price;
                maker_ = maker;
                seller_ = seller;
            };
            //GETS
            std::string GetName(){return name_;}
            std::string GetId(){return id_;}
            float GetPrice(){return price_;}
            std::string GetMaker(){return maker_;}
            std::string GetSeller(){return seller_;}
            //SETS
            void SetName(std::string name){name_=name;}
            void SetId(std::string id){id_=id;}
            void SetPrice(float price){price_ = price;}
            void SetMaker(std::string maker){maker_ = maker;}
            void SetSeller(std::string seller){seller_= seller;}
};



#endif