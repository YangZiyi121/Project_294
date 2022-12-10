#include <iostream>
#include <typeinfo>
#include "Latch.h"
#include "Device.h"
#include "Port.h"


/*Function of Mux*/
/*Routes the input on the input port specified by the control signal to the output latch.*/
class Multiplexer: public Device
{
public:
    const double cycles = 0.5;
    const int area = 500;
    const double power = 0.25;
    //Constructer
    Multiplexer(Latch &data1, Latch &data2, Latch &data3, Latch &data4, Latch &control_input, Latch &output)
    {
        Multiplexer::in0.connection = &data1;
        Multiplexer::in1.connection = &data2;
        Multiplexer::in2.connection = &data3;
        Multiplexer::in3.connection = &data4;
        Multiplexer::control.connection = &control_input;
        Multiplexer::out = &output;
        std::cout << "Mux is being created" << std::endl;
    } 
    //Inherit from Device
    void receive_clock() 
    { 
        Multiplexer::out->before = result;
    }

    //Inherit
    void do_function()
    {
        switch (Multiplexer::control.connection->after)
        {
        case 0b00:
            result = Multiplexer::in0.connection->after;
            break;
        case 0b01:
            result = Multiplexer::in1.connection->after;
            break;
        case 0b10:
            result = Multiplexer::in2.connection->after;
            break;
        case 0b11:
            result = Multiplexer::in3.connection->after;
            break;
        default:
            std::cout << "No control signal for MUX" << std::endl;
            break;
        }
    }

private:
    Port in0, in1, in2, in3;
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

/*Testing*/
// int main()
// {
//     Latch input[4];
//     Latch control, output;

//     //Initialize latches
//     input[0].before = 0b1010100011;
//     input[1].before = 0b1110000000;
//     input[2].before = 0b0000111101; //use this format if you want binary representation
//     input[3].before = 0b0000000010;
//     control.before = 0b00;

//     //std::cout<< typeid(input[1]).name() <<std::endl;
//     //std::cout<< typeid(control).name() <<std::endl;

//     //Create Device
//     Multiplexer device (input[0], input[1], input[2], input[3], control, output);
    
//     //send clock to latches
//     for (int i = 0; i < 4; i++){
//         input[i].receive_clock();
//     }
//     control.receive_clock();
//     output.receive_clock();

//     //propogate data through device
//     device.do_function();
//     device.receive_clock();

//     //result should now be output.before 
//     std::cout << output.before <<std::endl;
//     std::cout << std::bitset<10>(output.before) <<std::endl;
    
// }