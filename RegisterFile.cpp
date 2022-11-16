#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

using namespace std;

/*Function of Register File*/
/*Stores an array of 32 registers of 64-bit each. Results varies according to the control signals.*/
class RegisterFile: public Device
{
public:
    static const int cycles = 1;
    static const int area = 2000;
    static const double power = 4;

    //Constructer
    RegisterFile(Latch data1, Latch data2, int64_t control)
    {
        in[0].connection = data1;
        in[1].connection = data2;
        control_signal.connection = control;
        cout << "Register File is being created" << endl;
    } 

    receive_clock() { out[0].before = result[0]; out[1].before = result[1];}

    //Inherit
    void do_function()
    {
        switch (control_signal)
        {
            case 0x00:
                break;
            case 0x01:
                result[0].before = rf[in[0].connection.after];
                break;
            case 0x10:
                static_assert (in[0].connection.after != in[1].connection.after, "Register File access failure. The RR (0x10) control signal is accompanied with two input that refer to the same register.");
                result[0].before = rf[in[0].connection.after];
                result[1].before = rf[in[1].connection.after];
                break;
            case 0x11:
                rf[in[1].connection.after] = in[0].connection.after;
                break;
        }
    }



private:
    Port in[2];
    Latch out[2];
    int64_t control_signal; 

    long long result[2];

    Latch rf[32]; //The register file container. The register is basically an array of latches (of course, here an abuse of notion for the sake of a simple simulation).
    //TODO: extremely meticulous level: a register is a group of parallelly signaled (by the same clock) latches. A register file is a group of serialized registers.
};

/*Testing*/
int main()
{
    //TODO:
    //make a test for each case
}