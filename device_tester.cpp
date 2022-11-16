#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
#include "Logic.cpp"



int main()
{
    Latch input1, input2, control, output;

    //Initialize Ports
    input1.before = 0b0010101;
    input1.before = 0b0010100;
    control.before = 2;

    //Create Device
    Logic device (latch1, latch2 , control , output);
    
    //send clock to latches
    input1.receive_clock();input2.receive_clock();control.receive_clock();output.receive_clock();

    //propogate data through device
    device.do_function();
    device.receive_clock();

    //result should now be output.before 
    cout << output.before <<endl;
}