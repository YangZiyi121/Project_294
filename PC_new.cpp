#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

//br rd    0b001
//brr rd   0b010
//brr L    0b011
//brnz rd rs 0b100
//brgt rd rs rt 0b101

class PC_new : public Device
{
    public:

    PC_new (Latch &ALU, Latch &Rd, Latch &L, Latch &PC, Latch &controlN, Latch &output)
    {
        in[0].connection = &ALU;
        in[1].connection = &Rd;
        in[2].connection = &L;
        in[3].connection = &PC;
        control.connection = &controlN; //3-bits
        out = &output;
    }

    void receive_clock() { 
        out->before = result;
    }

    void do_function()
    {
        switch(control.connection->after){
            case 0b001:    //br rd
                result = in[1].connection->after;
                break;

            case 0b010:    //brr rd
                result = in[3].connection->after + in[1].connection->after;
                break;
            
            case 0b011:   //brr L
                result = in[3].connection->after + in[2].connection->after;
                break;
            
            case 0b100:  //brnz rd rs 
                if(in[0].connection->after == 0){    //rs = 0
                    result = in[3].connection->after + 4;
                }else{
                    result = in[1].connection->after;
                }
                break;
            case 0b101: //brgt rd rs rt 0b101
                if(in[0].connection->after > 0){ //rs<=rt
                    result = in[1].connection->after;
                }else{
                    result = in[3].connection->after + 4;
                }

        }
        
    }
     
    private:
    Port in[4];
    Latch *out;
    Port control;
    long long result;
};

int main()
{
    Latch alu, rd, l, pc, control, output;

    //Initialize latches
    alu.before = 0; //use this format if you want binary representation
    rd.before = 200;
    l.before = 13;
    pc.before = 89;
    control.before = 0b101;

    //Create Device
    PC_new device (alu, rd, l, pc, control, output);
    
    //send clock to latches
    alu.receive_clock();rd.receive_clock();l.receive_clock();pc.receive_clock();control.receive_clock(); output.receive_clock();
    //std::cout << input1.after <<std::endl;

    //propogate data through device
    device.do_function();
    device.receive_clock();

    //result should now be output.before 
    std::cout << output.before <<std::endl;
    //std::cout << std::bitset<10>(output.before) <<std::endl;
    
}