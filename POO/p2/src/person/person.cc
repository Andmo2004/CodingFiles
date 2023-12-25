#include <string>
#include <vector>
#include <iostream>
#include "person.h"
            
            
            
void Person::ShowPreferences(){
    std::cout << "\nLas preferencias son: " << std::endl;
    for (auto s: preferences_){
        std::cout << s << std::endl;
    }
}
void Person::AddPreferences(std::string s1,std::string s2,std::string s3){
    preferences_.insert(preferences_.begin(), s1);
    preferences_.insert(preferences_.end(), s3);
    preferences_.insert(preferences_.begin()+(preferences_.size()/2), s2);
}

void Person::ChangePreference(int pos, std::string cad){
    try{
        preferences_.at(555) = "surf";
    }
    catch (std::out_of_range const& exc){
        std::cout << exc.what() << '\n';
    }

}

