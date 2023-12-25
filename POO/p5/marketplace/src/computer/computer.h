#include <string>
#include <vector>
#include <iostream>
#include "product.h"

enum ComputerType{Desktop,Laptop,Server,Tablet,Gaming}; 
class Computer:public Product{
    private:
        ComputerType type_;
    
    public:

    //CONSTRUCTOR
    Computer(std::string id, ComputerType type , std::string name="empty",
    float price = 0.0, std::string maker="empty", 
    std::string seller="empty"):Product(id,name,price,maker,seller){type_=type;};

    //SETTERS
    void SetType(ComputerType type){
        type_= type;}

    //GETTERS
    ComputerType GetType(){return type_;}
    

};