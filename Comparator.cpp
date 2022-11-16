#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

using namespace std;

/*Function of Comparator*/
/*Compares the signed value present at the first input port with the value present at the second port. Produces 0 if they are equal, 1 otherwise.*/
class Comparator: public Device
{
public:
    static const int cycles = 1;
    static const int area = 400;
    static const double power = 0.5;

    //Constructer
    Comparator(Latch data1, Latch data2)
    {
        in[0].connection = data1;
        in[1].connection = data2;
        cout << "Comparator is being created" << endl;
    } 
    //Inherit
    void receive_clock()
    { 
        out.before = result;
    }

    //Inherit
    void do_function()
    {
        if (in[0].connection.after == in[1].connection.after)
        {
            result = 0;
        }
        else
        {
            result = 1;
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

    long long result;
};

/*Testing*/
int main()
{
    //Initialize Ports
    Latch latch1,latch2;
    latch1.after = 0;
    latch2.after = 0;
    //Create shifter
    Comparator comparator (latch1, latch2);
    comparator.do_function();
    //Receive the clk and see the result
    comparator.receive_clock();
    cout << comparator.get_latch_result() <<endl;
    //cout << comparator.power << endl;
}