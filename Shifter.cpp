#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

/*Function of Shifter*/
/*Shifts the signed value present at the first port by a number of bits equal to the value present at the second port*/
class Shifter: public Device
{
public:
    // const int cycles = 1;
    // const int area = 200;
    // const double power = 0.5;
    //Constructer
    Shifter(Latch &data, Latch &position_to_shift, Latch &control_input, Latch &output)
    {
        Shifter::in[0].connection = &data;
        Shifter::in[1].connection = &position_to_shift;
        Shifter::control.connection = &control_input;
        Shifter::out = &output;
        std::cout << "Shifter is being created" << std::endl;
    } 
    //Inherit from Device
    void receive_clock() 
    { 
        Shifter::out->before = result;
    }
    //Inherit from Device
    void do_function()
    {
        if (Shifter::control.connection->after == 0)  //0x00 for right
        {
            result = Shifter::in[0].connection->after >> Shifter::in[1].connection->after;
        }
        else if (Shifter::control.connection->after == 1)//0x01 for left
        {
            result = Shifter::in[0].connection->after << Shifter::in[1].connection->after;
        }
    }


private:
    Port in[2];
    Latch *out; 
    Port control;
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
//     Latch input1, input2, control, output;

//     //Initialize latches
//     input1.before = 0b0000111101; //use this format if you want binary representation
//     input2.before = 0b0000000010;
//     control.before = 0b00;

//     //Create Device
//     Shifter device (input1, input2, control, output);
    
//     //send clock to latches
//     input1.receive_clock();input2.receive_clock();control.receive_clock();output.receive_clock();
//     //std::cout << input1.after <<std::endl;

//     //propogate data through device
//     device.do_function();
//     device.receive_clock();

//     //result should now be output.before 
//     std::cout << output.before <<std::endl;
//     std::cout << std::bitset<10>(output.before) <<std::endl;
    
// }