#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

class Demultiplexer : Device
{
    public:
    static const int cycles = 1;
    static const int area = 500;
    static const double power = 0.25;

    Demultiplexer(Latch& input1, Latch& controlN, Latch& output1 , Latch& output2, Latch& output3, Latch& output4)
    {
        in[0].connection = &input1;
        control.connection = &controlN;
        out[0] = &output1;
        out[1] = &output2;
        out[2] = &output3;
        out[3] = &output4;
    }

    void receive_clock() { out[control.connection->after]->before = result;}

    void receive_clock_latches() 
    {
        
    }

    void do_function()
    {
        long long a = in[0].connection->after;
        long long z = control.connection->after;

        result = a;
    }
     
    private:
    Port in[2];
    Latch *out[4];
    Port control;

    long long result;
};