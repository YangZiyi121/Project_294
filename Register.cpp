#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

using namespace std;

/*Function of Register*/
/*Holds a value in an individual register outside the purview of the register file.*/
class Register: public Device
{
public:
    const static double cycles = 0.5;
    static const int area = 200;
    static const double power = 0.05;

    //Constructer
    Register(Latch data)
    {
        in.connection = data1;
        cout << "Register  is being created" << endl;
    } 

    void receive_clock() { out.before = result;}

    //Inherit
    void do_function()
    {
        reg = in.connection;
        result = reg.after;
    }



private:
    Port in;
    Latch out;

    long long result;

    Latch reg;
};

/*Testing*/
int main()
{
    //TODO:
    //make a test
}