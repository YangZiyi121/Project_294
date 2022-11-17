#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
#include "Logic.cpp"
#include <bitset>

// steps to blackbox test a device:
//1- initialize all input and output latches for your device and set the before values for the input latches
//2- create the device using the created latches
//3- send a clock signal to all latches
//4- call do_function of device
//5- call receive_clock of device
//6- result should now be in before of output latch



int main()
{
    Latch input1, input2, control, output;

    //Initialize latches
    input1.before = 0b0000111101; //use this format if you want binary representation
    input2.before = 0b0110001001;
    control.before = 3;

    //Create Device
    Logic device (input1, input2, control, output);
    
    //send clock to latches
    input1.receive_clock();input2.receive_clock();control.receive_clock();output.receive_clock();
    //std::cout << input1.after <<std::endl;

    //propogate data through device
    device.do_function();
    device.receive_clock();

    //result should now be output.before 
    std::cout << output.before <<std::endl;
    std::cout << std::bitset<10>(output.before) <<std::endl;
}