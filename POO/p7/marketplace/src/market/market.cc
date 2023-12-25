#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include "client.h"
#include "seller.h"
#include "market.h"

bool Market::AddClient(Client c1){
    
    if (client_list_.empty()){

        client_list_.push_back(c1);
        return true;
    }

    else{

        for(auto it=client_list_.begin(); it!=client_list_.end();it++){
            if(it->GetId()==c1.GetId()){
                return false;
            }
        }
        client_list_.push_back(c1);
        return true;
    }
}

bool Market::AddSeller(Seller s1){
    
    if (seller_list_.empty()){

        seller_list_.push_back(s1);
        return true;
    }

    else{

        for(auto it=seller_list_.begin(); it!=seller_list_.end();it++){
            if(it->GetId()==s1.GetId()){
                return false;
            }
        }
        seller_list_.push_back(s1);
        return true;
    }
}

bool Market::DeleteClient(Client c1){
    if (client_list_.empty()) return false;

    for(auto it=client_list_.begin(); it!=client_list_.end();it++){
     if(it->GetId()==c1.GetId()){
        client_list_.erase(it);
        return true;
     }
    }
    return false;

}

bool Market::DeleteSeller(Seller s1){
    if (seller_list_.empty()) return false;

    for(auto it=seller_list_.begin(); it!=seller_list_.end();it++){
     if(it->GetId()==s1.GetId()){
        seller_list_.erase(it);
        return true;
     }
    }
    return false;

}

bool Market::AddProductSeller(Product p1, std::string id_seller){
    if(seller_list_.empty()) return false;
    for(auto it=seller_list_.begin(); it!=seller_list_.end();it++){
     if(it->GetId()==id_seller){
        it->AddProduct(p1);
        return true;
     }
    }
    return false;
}

bool Market::AddProductClient(Product p1, std::string id_client){
    
    if(client_list_.empty() || seller_list_.empty()) {return false;}
  
    for(auto it=seller_list_.begin(); it!=seller_list_.end();it++){
        if(it->DeleteProduct(p1)){
            for(auto ot=client_list_.begin(); ot!=client_list_.end();ot++){
                if(ot->GetId()== id_client){ 
                    ot->AddProduct(p1);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Market::DeleteProductSeller(Product p1, std::string id_seller){

    if(seller_list_.empty()) return false;
    else{
        for(auto it=seller_list_.begin(); it!=seller_list_.end();it++){
            if(it->GetId() == id_seller){
                return it->DeleteProduct(p1);
            }
        }
        return false;
    }
}

bool Market::DeleteProductClient(Product p1, std::string id_client){

    if(client_list_.empty()) return false;
    
    else{
        for(auto it=client_list_.begin(); it!=client_list_.end();it++){
            if(it->GetId()==id_client){
                return it->DeleteProduct(p1);
            }
        }
        return true;
    }
}

float Market::GetMoneyInBasket(){
    float suma = 0.0;
    if(client_list_.empty()) return 0.0;
    for(auto it=client_list_.begin(); it!=client_list_.end();it++){
       suma += it->GetTotal();
    }
    return suma;
}

bool Market::DumpMarket(int outmode){
    std::vector <int> vector;
    std::vector <std::string> vectchar;
    auto it=client_list_.begin();
    float total = GetMoneyInBasket();

    if(outmode == 1){
        std::ofstream archivo("ventas.txt");
        if(archivo.is_open()){
            archivo<<"|----------------|"<<std::endl;

            for(it=client_list_.begin(); it!=client_list_.end();it++){
                vectchar= it->GetIds();
                vector= it->GetQs();
                
                for(int i=0;i<it->GetSize();i++){
                    archivo<<"|"<<it->GetId()<<"  |"<<vector[i]<<"    |"<<vectchar[i]<<"   |"<<"\n";
                }
            }
            archivo<<"|----------------|"<<std::endl;
            archivo<<"|TOTAL: "<<total<<"€"<<"     |"<<"\n";
            archivo<<"|----------------|"<<std::endl;
        }
        archivo.close();
        return true;
    }
    if(outmode == 0){
        std::cout<<"|----------------|"<<std::endl;
        for(it=client_list_.begin(); it!=client_list_.end();it++){
            vectchar = it->GetIds();
            vector = it->GetQs();
            for(int i=0;i<it->GetSize();i++){
                std::cout<<"|"<<it->GetId()<<"  |"<<vector[i]<<"    |"<<vectchar[i]<<"   |"<<std::endl;
            } 
        }
        std::cout<<"|----------------|"<<std::endl;
        std::cout<<"|TOTAL: "<<total<<"€"<<"     |"<<std::endl; 
        std::cout<<"|----------------|"<<std::endl;    
        return true;
    }        
    return false;
}