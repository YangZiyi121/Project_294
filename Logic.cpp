#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

// class Device // C++ defaults to private inheritance
// {
// public:
// 	virtual void receive_clock()
// 	{
// 		//out.value = result;
// 	}
// 	virtual void do_function()
// 	{
// 		//result = in[0].connection.value + in[1].connection.value;
// 	}
// };

class Logic : Device
{
    public:
    static int cycles = 1;
    static int area = 600;
    static double power = 0.75;

    Logic(Latch input1, Latch input2, Latch controlN)
    {
        in[0] = input1;
        in[1] = input2;
        control = controlN;
    }

    receive_clock() { out.before = result;}

    //connect (int port_id, Latch l) { in[port_id].connection = l; }

    do_function()
    {
        long long a = in[0].connection.after;
        long long b = in[0].connection.after;
        long long z = control.connection.after;

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
    Latch out;
    Port control;

    long long result;
};

// class Latch
// {
//     public:
//     long long before;
//     long long after;

//     receive_clock() { after = before; }
// };

// class Port
// {
//     public:
//     Latch connection;
// };