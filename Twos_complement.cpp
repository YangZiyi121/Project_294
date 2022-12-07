#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

class Twos_complement : public Device
{
    public:
    static const int cycles = 1;
    static const int area = 200;
    static const double power = 0.25;

    Twos_complement(Latch &input1, Latch& output)
    {
        in[0].connection = &input1;
        out = &output;
    }

    void receive_clock() { out->before = result;}

    void do_function()
    {
        long long a = in[0].connection->after;

        result = ~a;
        result++;
    }
     
    private:
    Port in[1];
    Latch *out;

    long long result;
};