#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

class Adder : Device {
public:
	static const int cycles = 1;
	static const int area = 400;
	static const double power = 0.5;
	Adder(Latch& input1, Latch& input2, Latch& output)
	{
		//connect(0, l1);
		//connect(1, l2);
		Adder::in[0].connection = &input1;
		Adder::in[1].connection = &input2;
		Adder::out = &output;

		std::cout << "Adder is being created" << std::endl;

		//cycles = cycles + 1;
	} // Initialize the input ports and the latch as necessary
	void receive_clock() { Adder::out->before = Adder::result; //cout << "   " << Adder::out->before << endl; 
	}
	void do_function()
	{

		Adder::result = Adder::in[0].connection->after + Adder::in[1].connection->after;

	}

private:
	Port in[2];
	Latch* out;
	long long result;
};

/*Testing*/
int main()
{
	//Initialize Ports
	Latch latch1, latch2, output;
	latch1.before = 1050;
	latch2.before = 1000;

	//Create device
	Adder Adder(latch1, latch2, output);

	//Send clk to latches
	latch1.receive_clock();
	latch2.receive_clock();
	output.receive_clock();

	//propagate data through device
	Adder.do_function();
	Adder.receive_clock();

	//Receive the clk and see the result
	std::cout << output.before <<std::endl;

}

