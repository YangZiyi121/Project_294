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
    // const int cycles = 1;
    // const int area = 2000;
    // const double power = 4;

    //Constructer
    RegisterFile(Latch &data1, Latch &data2, Latch &output1, Latch &output2, Latch &control_in)
    {
        in[0].connection = &data1;
        in[1].connection = &data2;
        out[0] = &output1;
        out[1] = &output2;
        control.connection = &control_in;
        std::cout << "Register File is being created" << std::endl;
        for (int i = 0; i < 32; i++) // Initialize all the registers
        {
            rf[i] = 0;
        }
        
    } 

    void receive_clock() { 
        out[0]->before = result[0]; //Update output 1 i.e. RD1
        out[1]->before = result[1]; //Update output 2 i.e. RD2
    }

    //Inherit
    void do_function()
    {
        switch (control.connection->after)
        {
            case 0b00: //NOP
                result[0] = 0;
                result[1] = 0;
                break;
            case 0b01: //One read
                result[0] = rf[in[0].connection->after];
                result[1] = 0 ;
                break;
            case 0b10: //Two reads
                result[0] = rf[in[0].connection->after];
                result[1] = rf[in[1].connection->after];
                break;
            case 0b11: //One write
                rf[in[1].connection->after] = in[0].connection->after;
                result[0] = 0;
                result[1] = 0;
                break;
        }
    }



private:
    Port in[2];
    Latch* out[2];
    Port control; 
    long long result[2];
    int64_t rf[32]; //The register file container.
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