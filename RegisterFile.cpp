#include <iostream>
#include <type_traits>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
#include <limits>

/*Function of Register File*/
/*Stores an array of 32 registers of 64-bit each. Results varies according to the control signals.*/
class RegisterFile: public Device
{
public:
    static const int cycles = 1;
    static const int area = 2000;
    static const double power = 4;

    //Constructer
    RegisterFile(Latch &data1, Latch &data2, Latch &output1, Latch &output2, Latch &control_in)
    {
        in[0].connection = &data1;
        in[1].connection = &data2;
        out[0] = &output1;
        out[1] = &output2;
        control.connection = &control_in;
        std::cout << "Register File is being created" << std::endl;
    } 

    void receive_clock() { 
        out[0]->before = result[0];
        out[1]->before = result[1];

    }

    //Inherit
    void do_function()
    {
        switch (control.connection->after)
        {
            case 0b00:
                result[0] = std::numeric_limits<int64_t>::max(); //infinite impedance
                result[1] = std::numeric_limits<int64_t>::max(); //infinite impedance
                break;
            case 0b01:
                result[0] = rf[in[0].connection->after];
                result[1] = std::numeric_limits<int64_t>::max(); //infinite impedance
                break;
            case 0b10:
                //std::cout << "Rd: " << in[0].connection->after << std::endl;
                //std::cout << "Rs: " << in[1].connection->after << std::endl;
                // if ((in[0].connection->after == in[1].connection->after))
                    // std::cout << "Register File access failure. The RR (0x10) control signal is accompanied with two input that refer to the same register." << std::endl;
                // assert (in[0].connection->after != in[1].connection->after);
                result[0] = rf[in[0].connection->after];
                result[1] = rf[in[1].connection->after];
                break;
            case 0b11:
                rf[in[1].connection->after] = in[0].connection->after;
                result[0] = std::numeric_limits<int64_t>::max(); //infinite impedance
                result[1] = std::numeric_limits<int64_t>::max(); //infinite impedance
                 //std::cout << "Write "<< in[0].connection->after << "to rf "<< in[1].connection->after << std::endl;
                break;
        }
        //std::cout << "RF10: "<<rf[10]<<std::endl;
    }



private:
    Port in[2];
    Latch* out[2];
    Port control; 
    long long result[2];
    int64_t rf[32]; //The register file container. The register is basically an array of latches (of course, here an abuse of notion for the sake of a simple simulation).
    //TODO: extremely meticulous level: a register is a group of parallelly signaled (by the same clock) latches. A register file is a group of serialized registers.
};

// /*Testing*/
// int main()
// {
//     //TODO:
//     //make a test for each case
//     Latch input1, input2, output1, output2, control;

//     //Write test
//     input1.before = 1000; //use this format if you want binary representation
//     input2.before = 1;
//     control.before = 0x11;

//     //Create Device
//     RegisterFile device (input1, input2, output1, output2, control);
    
//     //send clock to latches
//     input1.receive_clock();input2.receive_clock();control.receive_clock();output1.receive_clock(); output2.receive_clock();


//     //propogate data through device
//     device.do_function();
//     device.receive_clock();

//     //Write test
//     input1.before = 2000; //use this format if you want binary representation
//     input2.before = 2;
//     control.before = 0x11;
    
//     //send clock to latches
//     input1.receive_clock();input2.receive_clock();control.receive_clock();output1.receive_clock(); output2.receive_clock();

//     //propogate data through device
//     device.do_function();
//     device.receive_clock();

    

//     //Read 0x01
//     input1.before = 1;
//     control.before = 0x01;
//     input1.receive_clock();input2.receive_clock();control.receive_clock();output1.receive_clock(); output2.receive_clock();
//     device.do_function();
//     device.receive_clock();
//     std::cout << "Read 0x01 "<< output1.before << std::endl;

//     //Read 0x10
//     input1.before = 1;
//     input2.before = 2;
//     control.before = 0x10;
//     input1.receive_clock();input2.receive_clock();control.receive_clock();output1.receive_clock(); output2.receive_clock();
//     device.do_function();
//     device.receive_clock();
//     std::cout << "Read 0x10 " << output1.before << " " << output2.before << std::endl;


// }