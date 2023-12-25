#ifndef PERSON_H
#define PERSON_H

// Delaración de la clase Person

#include <string>

    class Person{

        private:
            std::string name_; //poner barra baja detrás del nombre de la variable ( _ ).
            int age_;
            double rank_;

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
    };


#endif