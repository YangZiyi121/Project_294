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

    Logic(Latch &ALU, Latch &Rd, Latch &L, Latch &PC, Latch &controlN, Latch &output)
    {
        in[0].connection = &ALU;
        in[1].connection = &Rd;
        in[2].connection = &L;
        in[3].connection = &PC;
        control.connection = &controlN;
        out = &output;
    }

    void receive_clock() { out->before = result;}

    void receive_clock_latches() 
    {
        
    }

    void do_function()
    {
        long long alu = in[0].connection->after; // either 
        long long Rd = in[1].connection->after;
        long long L = in[2].connection->after;
        long long PC = in[3].connection->after;
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
    Port in[4];
    Latch *out;
    Port control;

    long long result;
};