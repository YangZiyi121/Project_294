#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"


/*Function of Register*/
/*Holds a value in an individual register outside the purview of the register file.*/
class Register: public Device
{
public:
    const static double cycles = 0.5;
    static const int area = 200;
    static const double power = 0.05;

    //Constructer
    Register(Latch &input, Latch &output)
    {
        Register::in.connection = &input;
        Register::out = &output;
        std::cout << "Register  is being created" << std::endl;
    } 

    void receive_clock() { 
        Register::out->before = Register::result;
        
    }

    //Inherit
    void do_function()
    {
        Register::result = Register::in.connection->after;
    }



private:
    Port in;
    Latch* out;
    long long result;
};

// /*Testing*/
// int main()
// {
//     //Initialize Ports
//     Latch input, output;
//     input.before = 100;

//     //Create Device
//     Register reg(input, output);

//     //send clock to latches
//     input.receive_clock();
//     output.receive_clock();

//     //propagate data 
//     reg.do_function();
//     reg.receive_clock();

//     //result
//     std::cout << output.before << std::endl;
// }