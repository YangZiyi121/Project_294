#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
#include "Logic.cpp"
#include "Adder.cpp"
#include "RegisterFile.cpp"
#include <bitset>
#include <vector>

int const NUM_LATCHES = 6;
int const NUM_DEVICES = 2;
Latch latches[NUM_LATCHES];
std::vector<Device> devices;
Device tmp_device;

int build_arch();

int main()
{
    
    // std::cout << "past devices" <<std::endl;
    build_arch();
    
    //send clock to latches
    for (int j = 0; j < 6; j++)
    {
        if(j == 0) // put 126 in 1
        {
            latches[0].before = 126;
            latches[1].before = 1;
            latches[4].before = 0b11;
        }
        if(j == 1) // put 241 in 2
        {
            latches[0].before = 241;
            latches[1].before = 2;
            latches[4].before = 0b11;
        }
        if(j == 2) // read 1 and 2
        {
            latches[0].before = 1;
            latches[1].before = 2;
            latches[4].before = 0b10;
        }
        if(j == 3) // do nothing
        {
            latches[4].before = 0b00;
        }
        if(j == 4) // put add result in RF
        {
            latches[1].before = 3;
            latches[4].before = 0b11;
        }
        if(j == 5) // read reg 3
        {
            latches[0].before = 3;
            latches[4].before = 0b01;
        }

        for (int i = 0; i < NUM_LATCHES; i++) 
        {
            
            latches[i].receive_clock();
        }

        //std::cout << latches[0].after <<std::endl;

        // std::cout << "past clock latches" <<std::endl;

        //propogate data through device
        for (int i = 0; i < NUM_DEVICES; i++) 
        {
            devices.at(i).do_function();
            // std::cout << "past do_function" <<std::endl;
            devices.at(i).receive_clock();
            // std::cout << "past receive_clock" <<std::endl;
        }
    }

    // std::cout << "past clock devices" <<std::endl;
    

    //result should now be output.before 
    std::cout << latches[2].before <<std::endl;
    std::cout << std::bitset<10>(latches[2].before) <<std::endl;
    
}

int build_arch()
{
    //Initialize latches
    Latch *RF_input1 = &latches[0];
    Latch *RF_input2 = &latches[1];
    Latch *RF_output1 = &latches[2];
    Latch *RF_output2 = &latches[3];
    Latch *RF_c = &latches[4];

    Latch *adder_input1 = RF_output1;
    Latch *adder_input2 = RF_output2;
    Latch *adder_output = RF_input1;



    latches[0].before = 126; //use this format if you want binary representation
    latches[1].before = 241;
    latches[2].before = 0;
    latches[3].before = 0;
    latches[4].before = 0;
    latches[5].before = 0;

    // std::cout << "past latches" <<std::endl;

    //Create Device
    
    // devices.push_back(new RegisterFile(*RF_input1, *RF_input2, *RF_output1, *RF_output2, *RF_c));
    // devices.push_back(new Adder(*adder_input1, *adder_input2, *adder_output));

    tmp_device = RegisterFile(*RF_input1, *RF_input2, *RF_output1, *RF_output2, *RF_c);
    devices.push_back(tmp_device);
    tmp_device = Adder(*adder_input1, *adder_input2, *adder_output);
    devices.push_back(tmp_device);
}