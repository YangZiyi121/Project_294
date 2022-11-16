#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

class Logic : Device
{
    public:
    static int cycles = 1;
    static int area = 200;
    static double power = 0.25;

    Logic(Latch input1)
    {
        in[0] = input1;
    }

    receive_clock() { out.before = result;}

    do_function()
    {
        long long a = in[0].connection.after;

        result = ~a;
        result++;
    }
     
    private:
    Port in[1];
    Latch out;
    Port control;

    long long result;
};