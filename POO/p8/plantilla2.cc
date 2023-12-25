#include <iostream>

template <class Temp> class MiClase{
    private:
        Temp x_, y_;
    public:
        MiClase (Temp x, Temp y){x_=x; y_=y;};
        Temp div(){return x_/y_;};
};

int main()
{
    MiClase <int> int_obj(10,3);
    MiClase <double> float_obj(3.3, 5.5);

    std::cout << "División de integers = " << int_obj.div() << std::endl;
    std::cout << "División de flotantes = " << float_obj.div() << std::endl;

    return 0;
}
