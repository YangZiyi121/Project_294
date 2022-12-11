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
#include "IO.cpp"
#include "control_arry_2.cpp"
int const NUM_LATCHES = 100;
//int const NUM_DEVICES = 24; // use devices.size() instead of this
Latch latches[NUM_LATCHES]; // 80-100 for input of control array
std::vector<Device*> devices;
Device tmp_device;


//TESTING
//NEVER LET THIS UNCOMMENTED UNLESS TESTING AND YOU KNOW WHAT YOU ARE DOING!!!!!



int build_arch();

int main()
{
    
    // std::cout << "past devices" <<std::endl;
    build_arch();

    std::cout << devices.size() <<std::endl;

    //make sure all latches are clean
    for (int i = 0; i < NUM_LATCHES; i++) 
    {
        latches[i].before = 0;
    }
    
    //send clock to latches
    for (int j = 0; j < 8; j++)
    {
        if(j == 0) // write to R1
        {
            latches[27].before = 0; //input1 rf
            latches[22].before = 1; //input2 rf
            latches[30].before = 0b11; //RF control
        }
        if(j == 1) // write to R2
        {
            latches[27].before = 0; //input1 rf
            latches[22].before = 2; //input2 rf
            latches[30].before = 0b11; //RF control
        }
        if(j == 2) // put stuff after IM
        {
            latches[2].before = 1; //Rs
            latches[3].before = 0; //Rt
            latches[4].before = 66; //L
            latches[5].before = 2; //Rd
            latches[30].before = 0b00; //RF control

        }
        if(j == 3) // wait 1
        {
            latches[2].before = 0; //Rs
            latches[3].before = 0; //Rt
            latches[4].before = 0; //L
            latches[5].before = 0; //Rd
            latches[30].before = 0b00; //RF control
        }
        if(j == 4) // mux1
        {
            latches[15].before = 1; //pick Rd
        }
        if(j == 5) // mux2 mux3
        {
            latches[21].before = 0; //mux2 Rs
            latches[26].before = 0; //mux3 Rt
        }
        if(j == 6) // RF
        {
            latches[30].before = 0b10; //RF control
        }
        if(j == 7) // io
        {
            latches[30].before = 0b00; //RF control
            latches[43].before = 0b01; //control io
        }
        if(j == 8) // wait 1
        {
            latches[43].before = 0; //control io
        }
        if(j == 9) // wait 2
        {
                //hi
        }
        if(j == 10) // mux5
        {
            //std::cout << "time: " << j << " ALU 1: " << latches[45].before << std::endl;
            latches[47].before = 0b01; //pick alu result
        }  
        if(j == 11) // mux5
        {  

            //std::cout << "time: " << j << " WB 1: " << latches[23].before << std::endl;
            latches[21].before = 0b01; //mux2 WB
            latches[26].before = 0b01; //mux3 Rd
        }
        if(j == 12) // write
        {  
            latches[30].before = 0b11; //RF control
        }
        if(j == 13) // read
        {  
            latches[27].before = 3; //input1 rf
            latches[30].before = 0b01; //RF control
        }

        //std::cout << "time: " << j << std::endl;
        std::cout << "time: " << j << " mux4 L: " << latches[52].before << std::endl;
        //std::cout << "time: " << j << " RF 2: " << latches[22].before << std::endl << std::endl;

        for (int i = 0; i < NUM_LATCHES; i++) 
        {
            
            latches[i].receive_clock();
        }

        //std::cout << latches[0].after <<std::endl;

        // std::cout << "past clock latches" <<std::endl;

        //propogate data through device
        for (int i = 0; i < devices.size(); i++) 
        {
            devices.at(i)->do_function();
            // std::cout << "past do_function" <<std::endl;
            devices.at(i)->receive_clock();
            // std::cout << "past receive_clock" <<std::endl;
        }
    }

    // std::cout << "past clock devices" <<std::endl;
    

    //result should now be output.before 
    std::cout <<std::dec << latches[42].before <<std::endl;
    //std::cout << latches[29].before <<std::endl;
    //std::cout << std::bitset<10>(latches[2].before) <<std::endl;
    
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
    Latch *IM_L_buffer_out_3 = &latches[50];
    devices.push_back(new Register(*IM_L_buffer_in_3, *IM_L_buffer_out_3));
    Latch *IM_L_buffer_in_4 = IM_L_buffer_out_3;
    Latch *IM_L_buffer_out_4 = &latches[51];
    devices.push_back(new Register(*IM_L_buffer_in_4, *IM_L_buffer_out_4));
    Latch *IM_L_buffer_in_5 = IM_L_buffer_out_4;
    Latch *IM_L_buffer_out_5 = &latches[52];
    devices.push_back(new Register(*IM_L_buffer_in_5, *IM_L_buffer_out_5));

    Latch *IM_Rd_buffer_in_1 = IM_Rd;
    Latch *IM_Rd_buffer_out_1 = &latches[12];
    devices.push_back(new Register(*IM_Rd_buffer_in_1, *IM_Rd_buffer_out_1));
    Latch *IM_Rd_buffer_in_2 = IM_Rd_buffer_out_1;
    Latch *IM_Rd_buffer_out_2 = &latches[13];
    devices.push_back(new Register(*IM_Rd_buffer_in_2, *IM_Rd_buffer_out_2));
    Latch *IM_Rd_buffer_in_3 = IM_Rd_buffer_out_2;
    Latch *IM_Rd_buffer_out_3 = &latches[53];
    devices.push_back(new Register(*IM_Rd_buffer_in_3, *IM_Rd_buffer_out_3));
    Latch *IM_Rd_buffer_in_4 = IM_Rd_buffer_out_3;
    Latch *IM_Rd_buffer_out_4 = &latches[54];
    devices.push_back(new Register(*IM_Rd_buffer_in_4, *IM_Rd_buffer_out_4));
    Latch *IM_Rd_buffer_in_5 = IM_Rd_buffer_out_4;
    Latch *IM_Rd_buffer_out_5 = &latches[55];
    devices.push_back(new Register(*IM_Rd_buffer_in_5, *IM_Rd_buffer_out_5));
    Latch *IM_Rd_buffer_in_6 = IM_Rd_buffer_out_5;
    Latch *IM_Rd_buffer_out_6 = &latches[56];
    devices.push_back(new Register(*IM_Rd_buffer_in_6, *IM_Rd_buffer_out_6));
    Latch *IM_Rd_buffer_in_7 = IM_Rd_buffer_out_6;
    Latch *IM_Rd_buffer_out_7 = &latches[57];
    devices.push_back(new Register(*IM_Rd_buffer_in_7, *IM_Rd_buffer_out_7));
    Latch *IM_Rd_buffer_in_8 = IM_Rd_buffer_out_7;
    Latch *IM_Rd_buffer_out_8 = &latches[58];
    devices.push_back(new Register(*IM_Rd_buffer_in_8, *IM_Rd_buffer_out_8));
    Latch *IM_Rd_buffer_in_9 = IM_Rd_buffer_out_8;
    Latch *IM_Rd_buffer_out_9 = &latches[59];
    devices.push_back(new Register(*IM_Rd_buffer_in_9, *IM_Rd_buffer_out_9));

    //mux 1 between Rt and Rd
    Latch *MUX_1_Rt = IM_Rt_buffer_out_2;
    Latch *MUX_1_Rd = IM_Rd_buffer_out_2;
    Latch *MUX_1_useless1 = &latches[16];
    Latch *MUX_1_useless2 = &latches[17];
    Latch *MUX_1_c = &latches[15];
    Latch *MUX_1_output = &latches[18];
    devices.push_back(new Multiplexer(*MUX_1_Rt, *MUX_1_Rd, *MUX_1_useless1, *MUX_1_useless2, *MUX_1_c, *MUX_1_output));

    //mux 2 between mux1 and Rd
    Latch *MUX_2_mux1 = MUX_1_output;
    Latch *MUX_2_Rd = IM_Rd_buffer_out_9; //this will be changed later after Rd is super buffered
    Latch *MUX_2_useless1 = &latches[19];
    Latch *MUX_2_useless2 = &latches[20];
    Latch *MUX_2_c = &latches[21];
    Latch *MUX_2_output = &latches[22];
    devices.push_back(new Multiplexer(*MUX_2_mux1, *MUX_2_Rd, *MUX_2_useless1, *MUX_2_useless2, *MUX_2_c, *MUX_2_output));

    //mux 3 between Rs and write data
    Latch *MUX_3_Rs = IM_Rs_buffer_out_3;
    Latch *MUX_3_WD = &latches[23]; //this comes from the very last mux
    Latch *MUX_3_useless1 = &latches[24];
    Latch *MUX_3_useless2 = &latches[25];
    Latch *MUX_3_c = &latches[26];
    Latch *MUX_3_output = &latches[27];
    devices.push_back(new Multiplexer(*MUX_3_Rs, *MUX_3_WD, *MUX_3_useless1, *MUX_3_useless2, *MUX_3_c, *MUX_3_output));
    
    //RF component
    Latch *RF_mux3 = MUX_3_output;
    Latch *RF_mux2 = MUX_2_output;
    Latch *RF_RD1 = &latches[28];
    Latch *RF_RD2 = &latches[29];
    Latch *RF_c = &latches[30];
    devices.push_back(new RegisterFile(*RF_mux3, *RF_mux2, *RF_RD1, *RF_RD2, *RF_c));

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
    Latch *ALU_output_buffer_in_1 = ALU_output;
    Latch *ALU_output_buffer_out_1 = &latches[45];
    devices.push_back(new Register(*ALU_output_buffer_in_1, *ALU_output_buffer_out_1));

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
    Latch *DM_address = ALU_output;
    Latch *DM_WD = WD_buffer_out_1;
    Latch *DM_output = &latches[40];
    Latch *DM_c = &latches[41];
    devices.push_back(new MemoryData(*DM_address, *DM_WD, *DM_output, *DM_c));

    //IO component
    Latch *IO_RD1 = RF_RD1; //28
    Latch *IO_RD2 = RF_RD2; //29
    Latch *IO_output = &latches[42];
    Latch *IO_c = &latches[43];
    devices.push_back(new IO(*IO_RD1, *IO_RD2, *IO_c, *IO_output));

    //output of adder is buffered multiple time to sync up with other outputs
    Latch *IO_buffer_in_1 = ADDER_WD_WD;
    Latch *IO_buffer_out_1 = &latches[44];
    devices.push_back(new Register(*IO_buffer_in_1, *IO_buffer_out_1));
    Latch *IO_buffer_in_2 = IO_buffer_out_1;
    Latch *IO_buffer_out_2 = &latches[49];
    devices.push_back(new Register(*IO_buffer_in_2, *IO_buffer_out_2));

    //mux 5 between IO,ALU,DM results to writeback
    Latch *MUX_5_IO = IO_buffer_out_2;
    Latch *MUX_5_ALU = ALU_output_buffer_out_1;
    Latch *MUX_5_DM = DM_output;
    Latch *MUX_5_useless = &latches[46];
    Latch *MUX_5_c = &latches[47];
    Latch *MUX_5_output = MUX_3_WD;
    devices.push_back(new Multiplexer(*MUX_5_IO, *MUX_5_ALU, *MUX_5_DM, *MUX_5_useless, *MUX_5_c, *MUX_5_output));
    
    // control array takes whole latches array and takes slices of it based on input output
    devices.push_back(new ControlArray(latches));



}