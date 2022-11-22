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

class Divider : Device {
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

		cout << "Divider is being created" << endl;

		//cycles = cycles + 1;
	} // Initialize the input ports and the latch as necessary
	void receive_clock() { Divider::out->before = Divider::result; cout << "   " << Divider::out->before << endl; }
	void do_function()
	{
		if (Divider::in[1].connection->after != 0)
		{
			Divider::result = Divider::in[0].connection->after / Divider::in[1].connection->after;
		}
		else
		{
			throw runtime_error("Math error: Attempted to divide by Zero\n");
		}
		

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

	Divider Divider(latch1, latch2, output);

	Divider.do_function();
	Divider.receive_clock();
	//Receive the clk and see the result

}

