#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"


class PC_calc : public Device {
public:
	// static const int cycles = 1;
	// static const int area = 100;
	// static const double power = 0.1;

	//Constructor
	PC_calc(Latch &input1, Latch &output, Latch &c)
	{
		PC_calc::in.connection = &input1;
		PC_calc::out = &output;
        PC_calc::control = &c;
		std::cout << "PC_calc is being created" << std::endl;

	} // Initialize the input ports and the latch as necessary

	void receive_clock() 
    { 
        PC_calc::out->before = PC_calc::result; 
    }

	void do_function()
	{
        
		// std::cout << "PC control is " <<  control->after<< std::endl;
        long long z = PC_calc::control->after;
        if(z == 0)
		    PC_calc::result = 0xffffffffffffffff; // send a bogus address to notify IM not to execute
        else if (z == 1)
		{	
			// std::cout << "PC next is " <<  PC+1<< std::endl;
            PC_calc::result = PC++;
			control->before = 0;
			control->after = 0;
			// cout << endl ;
		}
	}

private:
	Port in;
	Latch *out;
    Latch *control;
    long long PC;
	long long result;
};

// /*Testing*/
// int main()
// {
// 	//Initialize Ports
// 	Latch latch1, output;
// 	latch1.before = 1000;

// 	//Create Adder
// 	Adder4 Adder4(latch1, output);

//     //send clk to latches
//     latch1.receive_clock();

//     //propagate data through device
// 	Adder4.do_function();
// 	Adder4.receive_clock();
	
//     //results
//     std::cout << output.before <<std::endl;
// }

