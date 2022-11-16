#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

using namespace std;

/*Function of Multiplier*/
/*Multiplies the signed values present at the input ports and produces a signed value.*/
class Multiplier: public Device
{
public:
    static const int cycles = 3;
    static const int area = 2000;
    static const double power = 1.5;

    //Constructer
    Multiplier(Latch data1, Latch data2)
    {
        in[0].connection = data1;
        in[1].connection = data2;
        cout << "Multiplier is being created" << endl;
    } 

    receive_clock() { out.before = result;}

    //Inherit
    void do_function()
    {

        result = in[0].connection.after * in[1].connection.after;

    }

    //Result getter
    long long get_latch_result()
    {
        return out.before;
    }

private:
    Port in[2];
    Latch out; 

    long long result;
};

/*Testing*/
int main()
{
    //Initialize Ports
    Latch latch1,latch2;
    latch1.after = 5;
    latch2.after = 12;
    //Create shifter
    Comparator comparator (latch1, latch2);
    comparator.do_function();
    //Receive the clk and see the result
    cout << comparator.get_latch_result() <<endl;
    cout << comparator.power << endl;
}