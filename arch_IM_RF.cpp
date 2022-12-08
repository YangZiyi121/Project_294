#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
#include "Logic.cpp"
#include "Adder.cpp"
#include "RegisterFile.cpp"
#include <bitset>
#include <vector>
#include "Register.cpp"
#include "Multiplexer.cpp"

int const NUM_LATCHES = 6;
int const NUM_DEVICES = 2;
Latch latches[NUM_LATCHES];
std::vector<Device*> devices;

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
            devices.at(i)->do_function();
            // std::cout << "past do_function" <<std::endl;
            devices.at(i)->receive_clock();
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
    //IM component
    Latch *IM_PC = &latches[0];
    Latch *IM_OP = &latches[1];
    Latch *IM_Rs = &latches[2];
    Latch *IM_Rt = &latches[3];
    Latch *IM_L = &latches[4];
    Latch *IM_Rd = &latches[5];
    devices.push_back(new MemoryInst(*IM_PC, *IM_OP, *IM_Rd, *IM_Rs, *IM_Rt, *IM_L));

    //output of IM is buffered multiple time to sync up with control signals
    Latch *IM_Rs_buffer_in_1 = IM_Rs;
    Latch *IM_Rs_buffer_out_1 = &latches[6];
    devices.push_back(new Register(*IM_Rs_buffer_in_1, *IM_Rs_buffer_out_1));
    Latch *IM_Rs_buffer_in_2 = IM_Rs_buffer_out_1;
    Latch *IM_Rs_buffer_out_2 = &latches[7];
    devices.push_back(new Register(*IM_Rs_buffer_in_2, *IM_Rs_buffer_out_2));
    Latch *IM_Rs_buffer_in_3 = IM_Rs_buffer_out_2;
    Latch *IM_Rs_buffer_out_3 = &latches[14];
    devices.push_back(new Register(*IM_Rs_buffer_in_3, *IM_Rs_buffer_out_3));

    Latch *IM_Rt_buffer_in_1 = IM_Rt;
    Latch *IM_Rt_buffer_out_1 = &latches[8];
    devices.push_back(new Register(*IM_Rt_buffer_in_1, *IM_Rt_buffer_out_1));
    Latch *IM_Rt_buffer_in_2 = IM_Rt_buffer_out_1;
    Latch *IM_Rt_buffer_out_2 = &latches[9];
    devices.push_back(new Register(*IM_Rt_buffer_in_2, *IM_Rt_buffer_out_2));

    Latch *IM_L_buffer_in_1 = IM_L;
    Latch *IM_L_buffer_out_1 = &latches[10];
    devices.push_back(new Register(*IM_L_buffer_in_1, *IM_L_buffer_out_1));
    Latch *IM_L_buffer_in_2 = IM_L_buffer_out_1;
    Latch *IM_L_buffer_out_2 = &latches[11];
    devices.push_back(new Register(*IM_L_buffer_in_2, *IM_L_buffer_out_2));

    Latch *IM_Rd_buffer_in_1 = IM_Rd;
    Latch *IM_Rd_buffer_out_1 = &latches[12];
    devices.push_back(new Register(*IM_Rd_buffer_in_1, *IM_Rd_buffer_out_1));
    Latch *IM_Rd_buffer_in_2 = IM_Rd_buffer_out_1;
    Latch *IM_Rd_buffer_out_2 = &latches[13];
    devices.push_back(new Register(*IM_Rd_buffer_in_2, *IM_Rd_buffer_out_2));

    //mux between Rt and Rd
    Latch *MUX_1_Rt = IM_Rt_buffer_out_2;
    Latch *MUX_1_Rd = IM_Rd_buffer_out_2;
    Latch *MUX_1_useless1 = &latches[16];
    Latch *MUX_1_useless2 = &latches[17];
    Latch *MUX_1_c = &latches[15];
    Latch *MUX_1_output = &latches[18];
    devices.push_back(new Multiplexer(*MUX_1_Rt, *MUX_1_Rd, *MUX_1_useless1, *MUX_1_useless2, *MUX_1_c, *MUX_1_output));

    //mux between mux1 and Rd
    Latch *MUX_2_mux1 = MUX_1_output;
    Latch *MUX_2_Rd = IM_Rd_buffer_out_2; //this will be changed later after Rd is super buffered
    Latch *MUX_2_useless1 = &latches[19];
    Latch *MUX_2_useless2 = &latches[20];
    Latch *MUX_2_c = &latches[21];
    Latch *MUX_2_output = &latches[22];
    devices.push_back(new Multiplexer(*MUX_2_mux1, *MUX_2_Rd, *MUX_2_useless1, *MUX_2_useless2, *MUX_2_c, *MUX_2_output));

    //mux between Rs and write data
    Latch *MUX_3_Rs = IM_Rs_buffer_out_3;
    Latch *MUX_3_WD = &latches[23]; //this comes from the very last mux and will change later
    Latch *MUX_3_useless1 = &latches[24];
    Latch *MUX_3_useless2 = &latches[25];
    Latch *MUX_3_c = &latches[26];
    Latch *MUX_3_output = &latches[27];
    devices.push_back(new Multiplexer(*MUX_3_Rs, *MUX_3_WD, *MUX_3_useless1, *MUX_3_useless2, *MUX_3_c, *MUX_3_output));
    
    //RF component
    Latch *RF_input1 = MUX_2_output;
    Latch *RF_input2 = MUX_3_output;
    Latch *RF_output1 = &latches[28];
    Latch *RF_output2 = &latches[29];
    Latch *RF_c = &latches[30];
    devices.push_back(new RegisterFile(*RF_input1, *RF_input2, *RF_output1, *RF_output2, *RF_c));
}