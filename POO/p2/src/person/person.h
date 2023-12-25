#ifndef PERSON_H
#define PERSON_H

// Delaración de la clase Person

#include <string>
#include <vector>
#include <iostream>

    class Person{

        private:
            std::string name_; //poner barra baja detrás del nombre de la variable ( _ ).
            int age_;
            double rank_;
            std::vector<std::string> preferences_;

        public:
            Person(std::string name, int age, double rank) {name_=name;age_=age;rank_=rank;}
            //inicializacion de las variables ^

            std::string GetName(){return name_;}

            int GetAge(){return age_;}

            double GetRank(){return rank_;}

            std::string GetDataStr(){
                return name_ + " " 
                + std::to_string(age_) + " " 
                + std::to_string(rank_);
            }

            std::vector<std::string> GetPreferences(){return preferences_;}
            void AddPreference(std::string s1){
                preferences_.push_back(s1);
            }
            

            void AddPreferences(std::string s1,std::string s2,std::string s3);
            void ShowPreferences();
            void ChangePreference(int pos, std::string cad);

    };


#endif