#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

using namespace std;

/*Function of Mux*/
/*Routes the input on the input port specified by the control signal to the output latch.*/
class Multiplexer: public Device
{
public:
    const static double cycles = 0.5;
    const static int area = 500;
    const static double power = 0.25;
    //Constructer
    Multiplexer(Latch data[4], int32_t control)
    {
        for (int i = 0; i < 4; i++){
            in[i].connection = data[i];
        }

        control_signal = control;
        cout << "Mux is being created" << endl;
    } 
    //Inherit
    void receive_clock() 
    { 
        out.before = result;
    }

    //Inherit
    void do_function()
    {
        switch (control_signal)
        {
        case 0x00:
            result = in[0].connection.after;
            break;
        case 0x01:
            result = in[1].connection.after;
            break;
        case 0x10:
            result = in[2].connection.after;
            break;
        case 0x11:
            result = in[3].connection.after;
            break;
        default:
            cout << "No control signal for MUX" << endl;
            break;
        }
    }

    //Result getter
    long long get_latch_result()
    {
        return out.before;
    }

private:
    Port in[4];
    Latch out; 
    int32_t control_signal;
    long long result;
};


/*Testing*/
int main()
{
    //Initialize Ports
    Latch latch[4];
    latch[0].after = 1024;
    latch[1].after = 256;
    latch[2].after = 512;
    latch[3].after = 2;
    //Create shifter
    Multiplexer multiplexer (latch, 0x10);
    multiplexer.do_function();
    //Receive the clk and see the result
    multiplexer.receive_clock();
    cout << multiplexer.get_latch_result() <<endl;
}