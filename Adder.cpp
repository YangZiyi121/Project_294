#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"

using namespace std;

class Latch
{
public:
	long long before;
	long long after;
	long long receive_clock();
};

class Port
{
public:
	Latch* connection;
};

class Device {

public:
	virtual void do_function() {};
	virtual void receive_clock() {};
};

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

		cout << "Adder is being created" << endl;

		//cycles = cycles + 1;
	} // Initialize the input ports and the latch as necessary
	void receive_clock() { Adder::out->before = Adder::result; cout << "   " << Adder::out->before << endl; }
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
	latch1.after = 1050;
	latch2.after = 1050;
	//Create shifter

	Adder Adder(latch1, latch2, output);

	Adder.do_function();
	Adder.receive_clock();
	//Receive the clk and see the result

}

