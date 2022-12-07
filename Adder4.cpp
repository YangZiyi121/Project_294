#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"


class Adder4 : public Device {
public:
	static const int cycles = 1;
	static const int area = 100;
	static const double power = 0.1;

	Adder4(Latch &input1, Latch &output)
	{
		Adder4::in.connection = &input1;
		Adder4::out = &output;

		std::cout << "Adder4 is being created" << std::endl;

		//cycles = cycles + 1;
	} // Initialize the input ports and the latch as necessary

	void receive_clock() 
    { 
        Adder4::out->before = Adder4::result; 
    }

	void do_function()
	{
		Adder4::result = Adder4::in.connection->after + 4;
	}

private:
	Port in;
	Latch *out;
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

