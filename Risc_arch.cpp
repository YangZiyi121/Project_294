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
#include "ALU.cpp"
#include "MemoryInst.cpp"
#include "MemoryData.cpp"

int const NUM_LATCHES = 42;
int const NUM_DEVICES = 24;
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

    //output of IM is buffered multiple time to sync up with control signals and other outputs
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
    Latch *IM_L_buffer_in_3 = IM_L_buffer_out_2;
    Latch *IM_L_buffer_out_3 = &latches[31];
    devices.push_back(new Register(*IM_L_buffer_in_3, *IM_L_buffer_out_3));
    Latch *IM_L_buffer_in_4 = IM_L_buffer_out_3;
    Latch *IM_L_buffer_out_4 = &latches[32];
    devices.push_back(new Register(*IM_L_buffer_in_4, *IM_L_buffer_out_4));
    Latch *IM_L_buffer_in_5 = IM_L_buffer_out_4;
    Latch *IM_L_buffer_out_5 = &latches[33];
    devices.push_back(new Register(*IM_L_buffer_in_5, *IM_L_buffer_out_5));

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

    //mux 3 between Rs and write data
    Latch *MUX_3_Rs = IM_Rs_buffer_out_3;
    Latch *MUX_3_WD = &latches[23]; //this comes from the very last mux and will change later
    Latch *MUX_3_useless1 = &latches[24];
    Latch *MUX_3_useless2 = &latches[25];
    Latch *MUX_3_c = &latches[26];
    Latch *MUX_3_output = &latches[27];
    devices.push_back(new Multiplexer(*MUX_3_Rs, *MUX_3_WD, *MUX_3_useless1, *MUX_3_useless2, *MUX_3_c, *MUX_3_output));
    
    //RF component
    Latch *RF_mux2 = MUX_2_output;
    Latch *RF_mux3 = MUX_3_output;
    Latch *RF_RD1 = &latches[28];
    Latch *RF_RD2 = &latches[29];
    Latch *RF_c = &latches[30];
    devices.push_back(new RegisterFile(*RF_mux2, *RF_mux3, *RF_RD1, *RF_RD2, *RF_c));

    //output of RF is buffered multiple time to sync up with other outputs
    Latch *RF_RD1_buffer_in_1 = RF_RD1;
    Latch *RF_RD1_buffer_out_1 = &latches[31];
    devices.push_back(new Register(*RF_RD1_buffer_in_1, *RF_RD1_buffer_out_1));

    //mux 4 between RD2 and L
    Latch *MUX_4_RD2 = RF_RD2;
    Latch *MUX_4_L = IM_L_buffer_out_5;
    Latch *MUX_4_useless1 = &latches[32];
    Latch *MUX_4_useless2 = &latches[33];
    Latch *MUX_4_c = &latches[34];
    Latch *MUX_4_output = &latches[35];
    devices.push_back(new Multiplexer(*MUX_4_RD2, *MUX_4_L, *MUX_4_useless1, *MUX_4_useless2, *MUX_4_c, *MUX_4_output));
    

    //ALU component
    Latch *ALU_RD1 = RF_RD1_buffer_out_1;
    Latch *ALU_mux4 = MUX_4_output;
    Latch *ALU_output = &latches[36];
    Latch *ALU_c = &latches[37];
    devices.push_back(new ALU(*ALU_RD1, *ALU_mux4, *ALU_output, *ALU_c));

    //output of ALU is buffered multiple time to sync up with other outputs
    // Latch *ALU_output_buffer_in_1 = ALU_output;
    // Latch *ALU_output_buffer_out_1 = &latches[38];
    // devices.push_back(new Register(*ALU_output_buffer_in_1, *ALU_output_buffer_out_1));

    //adder that computes write data
    Latch *ADDER_WD_RD2 = RF_RD2;
    Latch *ADDER_WD_L = IM_L_buffer_out_5;
    Latch *ADDER_WD_WD = &latches[39];
    devices.push_back(new Adder(*ADDER_WD_RD2, *ADDER_WD_L, *ADDER_WD_WD));

    //output of adder is buffered multiple time to sync up with other outputs
    Latch *WD_buffer_in_1 = ADDER_WD_WD;
    Latch *WD_buffer_out_1 = &latches[38];
    devices.push_back(new Register(*WD_buffer_in_1, *WD_buffer_out_1));

    //DM component
    Latch *DM_adress = ALU_output;
    Latch *DM_WD = WD_buffer_out_1;
    Latch *DM_output = &latches[40];
    Latch *DM_c = &latches[41];
    devices.push_back(new MemoryData(*DM_adress, *DM_WD, *DM_output, *DM_c));
}