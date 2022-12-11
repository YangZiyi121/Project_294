#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
using namespace std;

/*Function of Register File*/
/*Stores an array of 32 registers of 64-bit each. Results varies according to the control signals.*/
class MultiportRegs: public Device
{
public:
    // const int cycles = 1;
    // const int area = 25000;
    // const double power = 6;

    //Constructer
    MultiportRegs(Latch& data1, Latch& data2, Latch& data3, Latch& data4, Latch& control_input, Latch& output1, Latch& output2, Latch& output3, Latch& output4)
    {
        MultiportRegs::in[0].connection = &data1;
        MultiportRegs::in[1].connection = &data2;
        MultiportRegs::in[2].connection = &data3;
        MultiportRegs::in[3].connection = &data4;
        MultiportRegs::control.connection = &control_input;
        MultiportRegs::out[0] = &output1;
        MultiportRegs::out[1] = &output2;
        MultiportRegs::out[2] = &output3;
        MultiportRegs::out[3] = &output4;
        cout << "MultiportRegs File is being created" << endl;
    } 

    void receive_clock() {
        MultiportRegs::out[0]->before = MultiportRegs::result[0]; MultiportRegs::out[1]->before = MultiportRegs::result[1];MultiportRegs::out[2]->before = MultiportRegs::result[2]; MultiportRegs::out[3]->before = MultiportRegs::result[3];
    }

    //Inherit
    void do_function()
    {

        
        switch (MultiportRegs::control.connection->after)
        {
            case 0x0000://NOP
                break;
            case 0x0001://R
                MultiportRegs::result[0] = MultiportRegs::rf[MultiportRegs::in[0].connection->after].before;
                MultiportRegs::result[1] = 0;
                MultiportRegs::result[2] = 0;
                MultiportRegs::result[3] = 0;
                break;
            case 0x0010://RR
                MultiportRegs::result[0] = MultiportRegs::rf[MultiportRegs::in[0].connection->after].before;
                MultiportRegs::result[1] = MultiportRegs::rf[MultiportRegs::in[1].connection->after].before;
                MultiportRegs::result[2] = 0;
                MultiportRegs::result[3] = 0;
                break;
            case 0x0011://RRR
                MultiportRegs::result[0] = MultiportRegs::rf[MultiportRegs::in[0].connection->after].before;
                MultiportRegs::result[1] = MultiportRegs::rf[MultiportRegs::in[1].connection->after].before;
                MultiportRegs::result[2] = MultiportRegs::rf[MultiportRegs::in[2].connection->after].before;
                MultiportRegs::result[3] = 0;
                break;
            case 0x0100://RRRR
                MultiportRegs::result[0] = MultiportRegs::rf[MultiportRegs::in[0].connection->after].before;
                MultiportRegs::result[1] = MultiportRegs::rf[MultiportRegs::in[1].connection->after].before;
                MultiportRegs::result[2] = MultiportRegs::rf[MultiportRegs::in[2].connection->after].before;
                MultiportRegs::result[3] = MultiportRegs::rf[MultiportRegs::in[3].connection->after].before;
                break;
            case 0x0101://RRRW
                MultiportRegs::result[0] = MultiportRegs::rf[MultiportRegs::in[0].connection->after].before;
                MultiportRegs::result[1] = MultiportRegs::rf[MultiportRegs::in[1].connection->after].before;
                MultiportRegs::result[2] = MultiportRegs::rf[MultiportRegs::in[2].connection->after].before;
                MultiportRegs::result[3] = 0;
                MultiportRegs::rf[MultiportRegs::in[3].connection->after].before = MultiportRegs::in[4].connection->after;
                break;
            case 0x0110://RRW
                MultiportRegs::result[0] = MultiportRegs::rf[MultiportRegs::in[0].connection->after].before;
                MultiportRegs::result[1] = MultiportRegs::rf[MultiportRegs::in[1].connection->after].before;
                MultiportRegs::result[2] = 0;
                MultiportRegs::result[3] = 0;
                MultiportRegs::rf[MultiportRegs::in[2].connection->after].before = MultiportRegs::in[3].connection->after;
                break;
            case 0x0111://RW
                MultiportRegs::result[0] = MultiportRegs::rf[MultiportRegs::in[0].connection->after].before;
                MultiportRegs::result[1] = 0;
                MultiportRegs::result[2] = 0;
                MultiportRegs::result[3] = 0;
                MultiportRegs::rf[MultiportRegs::in[1].connection->after].before = MultiportRegs::in[2].connection->after;
                break;
            case 0x1000://W
                MultiportRegs::rf[MultiportRegs::in[1].connection->after].before = MultiportRegs::in[0].connection->after;
                MultiportRegs::result[0] = 0;
                MultiportRegs::result[1] = 0;
                MultiportRegs::result[2] = 0;
                MultiportRegs::result[3] = 0;
                break;
            case 0x1001://WW
                MultiportRegs::rf[MultiportRegs::in[0].connection->after].before = MultiportRegs::in[1].connection->after;
                MultiportRegs::rf[MultiportRegs::in[2].connection->after].before = MultiportRegs::in[3].connection->after;
                MultiportRegs::result[0] = 0;
                MultiportRegs::result[1] = 0;
                MultiportRegs::result[2] = 0;
                MultiportRegs::result[3] = 0;
                break;
        }
    }



private:
    Port in[4];
    Latch *out[4];
    Port control;
    long long result[4];

    Latch rf[32]; //The register file container.
};

// /*Testing*/
// int main()
// {
//     //TODO:
//     //make a test for each case
// }