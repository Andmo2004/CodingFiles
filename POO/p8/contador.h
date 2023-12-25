#ifndef CONTADOR_H
#define CONTADOR_H

class Contador
{
    private:
        
        int val_;
        int val_min_;
        int val_max_;

    public:
        
        Contador(int val = 0, int val_min = 0, int val_max = 1000);
        
        int get(){return val_;}

        //OPERADOR =:
        Contador operator=(int value);
        Contador operator=(const Contador& cont);

        //OPERADOR ++:
        Contador operator++(void);
        Contador operator++(int);

        //OPERADOR --:
        Contador operator--(void);
        Contador operator--(int);

        //OPERADOR +:
        friend int operator+(Contador ob, int i);
        friend int operator+(int i, Contador ob);

        //OPERADOR -:
        friend int operator-(Contador ob, int i);
        friend int operator-(int i, Contador ob);

        //EXTRACTOR E INSERTADOR
        friend std::ostream &operator<<(std::ostream &stream, const Contador &cont);
        friend std::istream &operator>>(std::istream &stream, Contador &cont);        
};

#endif