#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"


/*Two's compliment function.*/
class Twos_complement : public Device
{
    public:
    // const int cycles = 1;
    // const int area = 200;
    // const double power = 0.25;

    Twos_complement(Latch &input1, Latch& output)
    {
        in[0].connection = &input1;
        out = &output;
    }

    void receive_clock() { out->before = result;}

    void do_function()
    {
        long long a = in[0].connection->after;

        result = ~a; //Flip the bits
        result++; //Add 1
    }
     
    private:
    Port in[1];
    Latch *out;

    long long result;
};