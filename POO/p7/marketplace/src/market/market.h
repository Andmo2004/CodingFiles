#ifndef MARKET_H
#define MARKET_H

#include <list>
#include <iostream>
#include <string>
#include "client.h"
#include "seller.h"

class Market{
    private:

        std::list<Client> client_list_; //Lista de Clientes.
        std::list<Seller> seller_list_; //Lista de Vendedores.
        std::string slogan_;

    public:

        //CONSTRUCTOR
        Market(std::string slogan){slogan_= slogan;};

        //GETS Y SETS
        std::string GetSlogan(){return slogan_;};
        void SetSlogan(std::string slogan){
            slogan_ = slogan;
        };

        //FUNCIONES
        bool AddClient(Client c1);
        bool AddSeller(Seller s1);
        int NClients(){return client_list_.size();};
        int NSellers(){return seller_list_.size();};
        bool DeleteClient(Client c1);
        bool DeleteSeller(Seller s1);
        bool AddProductSeller(Product p1, std::string id_seller);
        bool AddProductClient(Product p1, std::string id_client);
        bool DeleteProductSeller(Product p1, std::string id_seller);
        bool DeleteProductClient(Product p1, std::string id_client);
        float GetMoneyInBasket();
        bool DumpMarket(int outmode);
        

};

#endif