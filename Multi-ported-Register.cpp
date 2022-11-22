#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
using namespace std;

class Latch
{
public:
    long long before;
    long long after;
    long long receive_clock();
};

class Port
{
public:
    Latch* connection;
};

class Device {

public:
    virtual void do_function() {};
    virtual void receive_clock() {};
};

/*Function of Register File*/
/*Stores an array of 32 registers of 64-bit each. Results varies according to the control signals.*/
class MultiportRegs: public Device
{
public:
    static const int cycles = 1;
    static const int area = 25000;
    static const double power = 6;

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

    receive_clock() {
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
                break;
            case 0x0010://RR
                static_assert (MultiportRegs::in[0].connection->after != MultiportRegs::in[1].connection->after, "Register File access failure. The RR (0x10) control signal is accompanied with two input that refer to the same register.");
                MultiportRegs::result[0] = MultiportRegs::rf[MultiportRegs::in[0].connection->after];
                MultiportRegs::result[1] = MultiportRegs::rf[MultiportRegs::in[1].connection->after];
                break;
            case 0x0011://RRR
                static_assert (MultiportRegs::in[0].connection->after != MultiportRegs::in[1].connection->after && MultiportRegs::in[1].connection->after != MultiportRegs::in[2].connection->after && MultiportRegs::in[0].connection->after != MultiportRegs::in[2].connection->after, "Register File access failure. The RR (0x10) control signal is accompanied with two input that refer to the same register.");
                MultiportRegs::result[0] = MultiportRegs::rf[MultiportRegs::in[0].connection->after];
                MultiportRegs::result[1] = MultiportRegs::rf[MultiportRegs::in[1].connection->after];
                MultiportRegs::result[2] = MultiportRegs::rf[MultiportRegs::in[2].connection->after];
                break;
            case 0x0100://RRRR
                static_assert (MultiportRegs::in[0].connection->after != MultiportRegs::in[1].connection->after && MultiportRegs::in[1].connection->after != MultiportRegs::in[2].connection->after && MultiportRegs::in[0].connection->after != MultiportRegs::in[2].connection->after && MultiportRegs::in[0].connection->after != MultiportRegs::in[3].connection->after && MultiportRegs::in[1].connection->after != MultiportRegs::in[3].connection->after && MultiportRegs::in[2].connection->after != MultiportRegs::in[3].connection->after, "Register File access failure. The RR (0x10) control signal is accompanied with two input that refer to the same register.");
                MultiportRegs::result[0] = MultiportRegs::rf[MultiportRegs::in[0].connection->after];
                MultiportRegs::result[1] = MultiportRegs::rf[MultiportRegs::in[1].connection->after];
                MultiportRegs::result[2] = MultiportRegs::rf[MultiportRegs::in[2].connection->after];
                MultiportRegs::result[3] = MultiportRegs::rf[MultiportRegs::in[3].connection->after];
                break;
            case 0x0101://RRRW
                static_assert (MultiportRegs::in[0].connection->after != MultiportRegs::in[1].connection->after && MultiportRegs::in[1].connection->after != MultiportRegs::in[2].connection->after && MultiportRegs::in[0].connection->after != MultiportRegs::in[2].connection->after && MultiportRegs::in[0].connection->after != MultiportRegs::in[3].connection->after && MultiportRegs::in[1].connection->after != MultiportRegs::in[3].connection->after && MultiportRegs::in[2].connection->after != MultiportRegs::in[3].connection->after, "Register File access failure. The RR (0x10) control signal is accompanied with two input that refer to the same register.");
                MultiportRegs::result[0] = MultiportRegs::rf[MultiportRegs::in[0].connection->after];
                MultiportRegs::result[1] = MultiportRegs::rf[MultiportRegs::in[1].connection->after];
                MultiportRegs::result[2] = MultiportRegs::rf[MultiportRegs::in[2].connection->after];
                MultiportRegs::rf[MultiportRegs::in[3].connection->after] = MultiportRegs::in[4].connection->after;
                break;
            case 0x0110://RRW
                static_assert (MultiportRegs::in[0].connection->after != MultiportRegs::in[1].connection->after && MultiportRegs::in[1].connection->after != MultiportRegs::in[2].connection->after && MultiportRegs::in[0].connection->after != MultiportRegs::in[2].connection->after, "Register File access failure. The RR (0x10) control signal is accompanied with two input that refer to the same register.");
                MultiportRegs::result[0] = MultiportRegs::rf[MultiportRegs::in[0].connection->after];
                MultiportRegs::result[1] = MultiportRegs::rf[MultiportRegs::in[1].connection->after];
                MultiportRegs::rf[MultiportRegs::in[2].connection->after] = MultiportRegs::in[3].connection->after;
                break;
            case 0x0111://RW
                static_assert (MultiportRegs::in[0].connection->after != MultiportRegs::in[1].connection->after, "Register File access failure. The RR (0x10) control signal is accompanied with two input that refer to the same register.");
                MultiportRegs::result[0] = MultiportRegs::rf[MultiportRegs::in[0].connection->after];
                MultiportRegs::rf[MultiportRegs::in[1].connection->after] = MultiportRegs::in[2].connection->after;
                break;
            case 0x1000://W
                MultiportRegs::rf[MultiportRegs::in[1].connection->after] = MultiportRegs::in[0].connection->after;
                break;
            case 0x1001://WW
                static_assert (MultiportRegs::in[0].connection->after != MultiportRegs::in[2].connection->after, "Register File access failure. The RR (0x10) control signal is accompanied with two input that refer to the same register.");
                MultiportRegs::rf[MultiportRegs::in[0].connection->after] = MultiportRegs::in[1].connection->after;
                MultiportRegs::rf[MultiportRegs::in[2].connection->after] = MultiportRegs::in[3].connection->after;
                break;
        }
    }



private:
    Port in[4];
    Latch *out[4];
    Port control;
    long long result[4];

    Latch rf[32]; //The register file container. The register is basically an array of latches (of course, here an abuse of notion for the sake of a simple simulation).
    //TODO: extremely meticulous level: a register is a group of parallelly signaled (by the same clock) latches. A register file is a group of serialized registers.
};

/*Testing*/
int main()
{
    //TODO:
    //make a test for each case
}