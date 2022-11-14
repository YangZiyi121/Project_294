#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

using namespace std;

/*Function of Shifter*/
/*Shifts the signed value present at the first port by a number of bits equal to the value present at the second port*/
class Shifter: public Device
{
public:
    //Constructer
    Shifter(Port data, Port position_to_shift, int32_t control)
    {
    in[0] = data;
    in[1]=  position_to_shift;
    control_signal = control;
    cout << "Shifter is being created" << endl;
    } 

    //Inherit
    void do_function()
    {
        if (control_signal == 0)  //0x00 for right
        {
            out.before = in[0].connection.after >> in[1].connection.after;
        }
        else if (control_signal == 1)//0x01 for left
        {
            out.before = in[0].connection.after << in[1].connection.after;
        }
    }

    //Result getter
    long long get_latch_result()
    {
        return out.before;
    }

private:
    Port in[2];
    Latch out; 
    int32_t control_signal;
};


/*Testing*/
int main()
{
    //Initialize Ports
    Port port1, port2;
    port1.connection.after = 1024;
    port2.connection.after = 8;
    //Create shifter
    Shifter shifter (port1, port2 , 1);
    shifter.do_function();
    //Receive the clk and see the result
    cout << shifter.get_latch_result()<<endl;
}