#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

/*Function of Comparator*/
/*Compares the signed value present at the first input port with the value present at the second port. Produces 0 if they are equal, 1 otherwise.*/
class Comparator: public Device
{
public:
    static const int cycles = 1;
    static const int area = 400;
    static const double power = 0.5;

    //Constructer
    Comparator(Latch &data1, Latch &data2, Latch &output)
    {
        Comparator::in[0].connection = &data1;
        Comparator::in[1].connection = &data2;
        Comparator::out = &output;
        std::cout << "Comparator is being created" << std::endl;
    } 
    //Inherit from Device
    void receive_clock()
    { 
        Comparator::out->before = result;
    }

    //Inherit from Device
    void do_function()
    {
        if (Comparator::in[0].connection->after == Comparator::in[1].connection->after)
        {
            result = 0;
        }
        else
        {
            result = 1;
        }
    }

private:
    Port in[2];
    Latch *out; 
    long long result;
};

// steps to blackbox test a device:
//1- initialize all input and output latches for your device and set the before values for the input latches
//2- create the device using the created latches
//3- send a clock signal to all latches
//4- call do_function of device
//5- call receive_clock of device
//6- result should now be in before of output latch

// /*Testing*/
// int main()
// {
//     Latch input1, input2, output;

//     //Initialize latches
//     input1.before = 0b0000111101; //use this format if you want binary representation
//     input2.before = 0b0000111101;

//     //Create Device
//     Comparator device (input1, input2, output);
    
//     //send clock to latches
//     input1.receive_clock();input2.receive_clock();output.receive_clock();
//     //std::cout << input1.after <<std::endl;

//     //propogate data through device
//     device.do_function();
//     device.receive_clock();

//     //result should now be output.before 
//     std::cout << output.before <<std::endl;
//     std::cout << std::bitset<10>(output.before) <<std::endl;
    
// }