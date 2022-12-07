#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

class Logic : public Device
{
    public:
    static const int cycles = 1;
    static const int area = 600;
    static const double power = 0.75;

    Logic(Latch &input1, Latch &input2, Latch &controlN, Latch &output)
    {
        in[0].connection = &input1;
        in[1].connection = &input2;
        control.connection = &controlN;
        out = &output;
    }

    void receive_clock() { out->before = result;}

    void receive_clock_latches() 
    {
        
    }

    void do_function()
    {
        long long a = in[0].connection->after;
        long long b = in[1].connection->after;
        long long z = control.connection->after;

        if(z == 0)
            result = ~a;
        if(z == 1)
            result = a&b;
        if(z == 2)
            result = a|b;
        if(z == 3)
            result = a^b;
    }
     
    private:
    Port in[2];
    Latch *out;
    Port control;

    long long result;
};