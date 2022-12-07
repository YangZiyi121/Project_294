#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

class Demultiplexer : public Device
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

    void receive_clock() 
    { 
        out[(control.connection->after+0)%4]->before = result;
        out[(control.connection->after+1)%4]->before = 0;
        out[(control.connection->after+2)%4]->before = 0;
        out[(control.connection->after+3)%4]->before = 0;
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