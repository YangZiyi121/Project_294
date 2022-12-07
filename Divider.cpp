#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"


class Divider : public Device {
public:
	static const int cycles = 8;
	static const int area = 5000;
	static const double power = 1;
	Divider(Latch& input1, Latch& input2, Latch& output)
	{
		//connect(0, l1);
		//connect(1, l2);
		Divider::in[0].connection = &input1;
		Divider::in[1].connection = &input2;
		Divider::out = &output;

		std::cout << "Divider is being created" << std::endl;

		//cycles = cycles + 1;
	} // Initialize the input ports and the latch as necessary
	void receive_clock() { 
		Divider::out->before = Divider::result; 
		//std::cout << "   " << Divider::out->before << std::endl; 
	}
	void do_function()
	{
		if (Divider::in[1].connection->after != 0)
		{
			Divider::result = Divider::in[0].connection->after / Divider::in[1].connection->after;
		}
		else
		{
			throw std::runtime_error("Math error: Attempted to divide by Zero\n");
		}
		

	}

private:
	Port in[2];
	Latch* out;
	long long result;
};

// /*Testing*/
// int main()
// {
// 	//Initialize Ports
// 	Latch latch1, latch2, output;
// 	latch1.before = 1050;
// 	latch2.before = 50;

// 	//Create divider
// 	Divider divider(latch1, latch2, output);

// 	//send clk to latches
// 	latch1.receive_clock();
// 	latch2.receive_clock();
// 	output.receive_clock();

// 	//propagate data 
// 	divider.do_function();
// 	divider.receive_clock();

// 	//Receive the clk and see the result
// 	std::cout << output.before <<std::endl;

// }

