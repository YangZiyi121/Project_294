#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
#include "Logic.cpp"
#include "Adder.cpp"
#include "Adder4.cpp"
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
#include "Decoder_test.cpp"
#include "PC_calc.cpp"

int const NUM_LATCHES = 200; // not a real 
Latch latches[NUM_LATCHES]; // 80-100 for input of control array
std::vector<Device*> devices;
Device tmp_device;



int build_arch();

int main()
{

    int file_number;
    std::cout << "Please enter the program you want to execute. 1 for helloworld, 2 for logic, 3 for fact6, 4 for arithmetic" << std::endl;
    std::cin >> file_number;
    /*load instructions to storage*/
    readfile(file_number); //load the file

    /*load instructions to storage*/


    // builds the architecture
    build_arch();

    //makes sure all latches are clean
    for (int i = 0; i < NUM_LATCHES; i++) 
    {
        latches[i].before = 0;
    } 

    latches[1].before = 0xff; //set op code so as to not send 0 instruct

    latches[70].before = 0;//control signal for pc_calc is set to send
    latches[0].before = 0xffffffffffffffff; //send no instruction for IM

    for (int j = 0;; j++)
    {
        //this simulates the pc counter for now
        // if(j % 15 == 0)
        // {
        //     pc++;
        //     latches[0].before = pc;
        // }
        // else
        // {
        //     latches[0].before = 0xffffffffffffffff; //i.e send invalid address to IM to simulate not sending
        // }
        if(j ==1)
        {
            latches[70].before = 1; // tell PC_calc to send first instruction
        }
        //call send a clock signal to all latches
        for (int i = 0; i < NUM_LATCHES; i++) 
        {
            latches[i].receive_clock();
        }

        //propogate data through devices
        for (int i = 0; i < devices.size(); i++) 
        {
            devices.at(i)->do_function();
            devices.at(i)->receive_clock();
        }
    }
     std::cout << "" <<std::endl; //if this is not here then any output not with endl will be lost
}

//builds the architecture
// we first define the latches for each device
// then we define the device
// then we buffer outputs of a device if needed
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
    Latch *IM_L_buffer_in_6 = IM_L_buffer_out_5;
    Latch *IM_L_buffer_out_6 = &latches[150];
    devices.push_back(new Register(*IM_L_buffer_in_6, *IM_L_buffer_out_6));
    Latch *IM_L_buffer_in_7 = IM_L_buffer_out_6;
    Latch *IM_L_buffer_out_7 = &latches[151];
    devices.push_back(new Register(*IM_L_buffer_in_7, *IM_L_buffer_out_7));

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

    //mux 1 between Rt and Rd to choose RF read 2
    Latch *MUX_1_Rt = IM_Rt_buffer_out_2;
    Latch *MUX_1_Rd = IM_Rd_buffer_out_2;
    Latch *MUX_1_useless1 = &latches[16];
    Latch *MUX_1_useless2 = &latches[17];
    Latch *MUX_1_c = &latches[71];  //MUX_1 control 1 bit
    Latch *MUX_1_output = &latches[18];
    devices.push_back(new Multiplexer(*MUX_1_Rt, *MUX_1_Rd, *MUX_1_useless1, *MUX_1_useless2, *MUX_1_c, *MUX_1_output));

    //mux 2 between mux1 and Rd to read or write
    Latch *MUX_2_mux1 = MUX_1_output;
    Latch *MUX_2_Rd = IM_Rd_buffer_out_9; 
    Latch *MUX_2_useless1 = &latches[19];
    Latch *MUX_2_useless2 = &latches[20];
    Latch *MUX_2_c = &latches[72];  //MUX_2 control 1 bit
    Latch *MUX_2_output = &latches[22];
    devices.push_back(new Multiplexer(*MUX_2_mux1, *MUX_2_Rd, *MUX_2_useless1, *MUX_2_useless2, *MUX_2_c, *MUX_2_output));

    //mux 3 between Rs and write data to read write
    Latch *MUX_3_Rs = IM_Rs_buffer_out_3;
    Latch *MUX_3_WD = &latches[23]; //this comes from the very last mux
    Latch *MUX_3_useless1 = &latches[24];
    Latch *MUX_3_useless2 = &latches[25];
    Latch *MUX_3_c = &latches[73]; //MUX_3 control 1 bit
    Latch *MUX_3_output = &latches[27];
    devices.push_back(new Multiplexer(*MUX_3_Rs, *MUX_3_WD, *MUX_3_useless1, *MUX_3_useless2, *MUX_3_c, *MUX_3_output));
    
    //RF component
    Latch *RF_mux3 = MUX_3_output;
    Latch *RF_mux2 = MUX_2_output;
    Latch *RF_RD1 = &latches[28];
    Latch *RF_RD2 = &latches[29];
    Latch *RF_c = &latches[74]; //RF control 2bits
    devices.push_back(new RegisterFile(*RF_mux3, *RF_mux2, *RF_RD1, *RF_RD2, *RF_c));

    //output of RF is buffered multiple time to sync up with other outputs
    Latch *RF_RD1_buffer_in_1 = RF_RD1;
    Latch *RF_RD1_buffer_out_1 = &latches[31];
    devices.push_back(new Register(*RF_RD1_buffer_in_1, *RF_RD1_buffer_out_1));

    Latch *RF_RD2_buffer_in_1 = RF_RD2;
    Latch *RF_RD2_buffer_out_1 = &latches[152];
    devices.push_back(new Register(*RF_RD2_buffer_in_1, *RF_RD2_buffer_out_1));
    Latch *RF_RD2_buffer_in_2 = RF_RD2_buffer_out_1;
    Latch *RF_RD2_buffer_out_2 = &latches[153];
    devices.push_back(new Register(*RF_RD2_buffer_in_2, *RF_RD2_buffer_out_2));

    //mux 4 between RD2 and L
    Latch *MUX_4_RD2 = RF_RD2;
    Latch *MUX_4_L = IM_L_buffer_out_5;
    Latch *MUX_4_useless1 = &latches[32];
    Latch *MUX_4_useless2 = &latches[33];
    Latch *MUX_4_c = &latches[75]; //MUX4 control 1 bit
    Latch *MUX_4_output = &latches[35];
    devices.push_back(new Multiplexer(*MUX_4_RD2, *MUX_4_L, *MUX_4_useless1, *MUX_4_useless2, *MUX_4_c, *MUX_4_output));
    

    //ALU component
    Latch *ALU_RD1 = RF_RD1_buffer_out_1;
    Latch *ALU_mux4 = MUX_4_output;
    Latch *ALU_output = &latches[36];
    Latch *ALU_c = &latches[76];  //ALU 4-bit
    devices.push_back(new ALU(*ALU_RD1, *ALU_mux4, *ALU_output, *ALU_c));

    //output of ALU is buffered multiple time to sync up with other outputs
    Latch *ALU_output_buffer_in_1 = ALU_output;
    Latch *ALU_output_buffer_out_1 = &latches[45];
    devices.push_back(new Register(*ALU_output_buffer_in_1, *ALU_output_buffer_out_1));

    //adder that computes write data to DM
    Latch *ADDER_WD_RD2 = RF_RD2;
    Latch *ADDER_WD_L = IM_L_buffer_out_5;
    Latch *ADDER_WD_WD = &latches[39];
    devices.push_back(new Adder(*ADDER_WD_RD2, *ADDER_WD_L, *ADDER_WD_WD));

    //output of adder is buffered multiple time to sync up with other outputs
    Latch *WD_buffer_in_1 = ADDER_WD_WD;
    Latch *WD_buffer_out_1 = &latches[69]; //IO 2 bits
    devices.push_back(new Register(*WD_buffer_in_1, *WD_buffer_out_1));

    //DM component
    Latch *DM_address = ALU_output;
    Latch *DM_WD = WD_buffer_out_1;
    Latch *DM_output = &latches[40];
    Latch *DM_c = &latches[78]; //DM 1-bit
    devices.push_back(new MemoryData(*DM_address, *DM_WD, *DM_output, *DM_c));

    //IO component
    Latch *IO_RD1 = RF_RD1; //28
    Latch *IO_RD2 = RF_RD2; //29
    Latch *IO_output = &latches[42];
    Latch *IO_c = &latches[77];
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
    Latch *MUX_5_c = &latches[79];   //MUX5 2-bit
    Latch *MUX_5_output = MUX_3_WD;
    devices.push_back(new Multiplexer(*MUX_5_IO, *MUX_5_ALU, *MUX_5_DM, *MUX_5_useless, *MUX_5_c, *MUX_5_output));
    
    // control array takes whole latches array and takes slices of it based on input output
    devices.push_back(new ControlArray(latches));

    //PC MUX
    // Latch *MUX_PC_same = IM_PC;
    // Latch *MUX_PC_inc = &latches[60];
    // Latch *MUX_PC_new = &latches[61];
    // Latch *MUX_PC_useless = &latches[63];
    // Latch *MUX_PC_c = &latches[170];
    // Latch *MUX_PC_output = IM_PC;
    // devices.push_back(new Multiplexer(*MUX_PC_same, *MUX_PC_inc, *MUX_PC_new, *MUX_PC_useless, *MUX_PC_c, *MUX_PC_output));

    // //output of pc mux is buffered for branching
    // Latch *PC_buffer_in_1 = MUX_PC_output;
    // Latch *PC_buffer_out_1 = &latches[161];
    // devices.push_back(new Register(*PC_buffer_in_1, *PC_buffer_out_1));
    // Latch *PC_buffer_in_2 = PC_buffer_out_1;
    // Latch *PC_buffer_out_2 = &latches[154];
    // devices.push_back(new Register(*PC_buffer_in_2, *PC_buffer_out_2));
    // Latch *PC_buffer_in_3 = PC_buffer_out_2;
    // Latch *PC_buffer_out_3 = &latches[155];
    // devices.push_back(new Register(*PC_buffer_in_3, *PC_buffer_out_3));
    // Latch *PC_buffer_in_4 = PC_buffer_out_3;
    // Latch *PC_buffer_out_4 = &latches[156];
    // devices.push_back(new Register(*PC_buffer_in_4, *PC_buffer_out_4));
    // Latch *PC_buffer_in_5 = PC_buffer_out_4;
    // Latch *PC_buffer_out_5 = &latches[157];
    // devices.push_back(new Register(*PC_buffer_in_5, *PC_buffer_out_5));
    // Latch *PC_buffer_in_6 = PC_buffer_out_5;
    // Latch *PC_buffer_out_6 = &latches[158];
    // devices.push_back(new Register(*PC_buffer_in_6, *PC_buffer_out_6));
    // Latch *PC_buffer_in_7 = PC_buffer_out_6;
    // Latch *PC_buffer_out_7 = &latches[159];
    // devices.push_back(new Register(*PC_buffer_in_7, *PC_buffer_out_7));
    // Latch *PC_buffer_in_8 = PC_buffer_out_7;
    // Latch *PC_buffer_out_8 = &latches[160];
    // devices.push_back(new Register(*PC_buffer_in_8, *PC_buffer_out_8));


    Latch *DEC_OP = IM_OP;
    devices.push_back(new Decoder(*DEC_OP, latches));

    //PC_calc finds the next address
    Latch *PC_CALC_branch = &latches[61]; // this comes from branch
    Latch *PC_CALC_output = IM_PC;
    Latch *PC_CALC_c = &latches[70];
    devices.push_back(new PC_calc(*PC_CALC_branch, *PC_CALC_output, *PC_CALC_c));

//     //PC_new for branch instructions
//     Latch *PC_NEW_ALU = ALU_output;
//     Latch *PC_NEW_Rd = RF_RD2_buffer_out_2;
//     Latch *PC_NEW_L = IM_L_buffer_out_7;
//     Latch *PC_NEW_PC = PC_buffer_out_8;
//     Latch *PC_c = &latches[161];
//     Latch *PC_NEW_output = MUX_PC_new;
//     devices.push_back(new PC_new(*PC_NEW_ALU, *PC_NEW_Rd, *PC_NEW_L, *PC_NEW_PC, *PC_c, *PC_NEW_output));
}