#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"


//TODO: Define those codes based on the architectural needs

// #define ADDcode
// #define MULTcode
// #define DIVcode
// #define NOTCcode
// #define ANDcode
// #define ORcode
// #define XORcode
// #define SRLcode
// #define SLLcode

//FOR TESTING PURPOSES

#define ADDcode 1
#define ADDcode 2
#define MULTcode 3
#define DIVcode 4
#define NOTCcode 5
#define ANDcode 6
#define ORcode 7
#define XORcode 8
#define SRLcode 9
#define SLLcode 10
#define PASS0code 11
#define PASS1code 12


class ALU : public Device {
public:

	//TODO: Make meaningful characteristics


	// static const int cycles = 1;
	// static const int area = 400;
	// static const double power = 0.5;





	ALU(Latch& input1, Latch& input2, Latch& output, Latch &control_in)
	{
		//connect(0, l1);
		//connect(1, l2);
		ALU::in[0].connection = &input1;
		ALU::in[1].connection = &input2;
		ALU::out = &output;
		ALU::control.connection = &control_in;
		std::cout << "ALU is being created" << std::endl;

		//cycles = cycles + 1;
	} // Initialize the input ports and the latch as necessary
	void receive_clock() { ALU::out->before = ALU::result; //cout << "   " << ALU::out->before << endl; 
	}
	void do_function()
	{

		

		switch (ALU::control.connection->after)
        {
            case ADDcode:
				ALU::result = ALU::in[0].connection->after + ALU::in[1].connection->after;
                break;
            case SUBcode:
				ALU::result = ALU::in[0].connection->after - ALU::in[1].connection->after;
                break;
            case MULTcode:
                ALU::result = ALU::in[0].connection->after * ALU::in[1].connection->after;
                break;
            case DIVcode:
                ALU::result = ALU::in[0].connection->after / ALU::in[1].connection->after;
                break;
            case NOTCcode:
                ALU::result = ~ ALU::in[0].connection->after;
                break;
			case ANDcode:
				ALU::result = ALU::in[0].connection->after & ALU::in[1].connection->after;
                break;
			case ORcode:
				ALU::result = ALU::in[0].connection->after | ALU::in[1].connection->after;
                break;
			case XORcode:
				ALU::result = ALU::in[0].connection->after ^ ALU::in[1].connection->after;
                break;
			case SRLcode:
				ALU::result = ALU::in[0].connection->after >> ALU::in[1].connection->after;
                break;
			case SLLcode:
				ALU::result = ALU::in[0].connection->after << ALU::in[1].connection->after;
                break;
			case PASS0code:
				ALU::result = ALU::in[0].connection->after;
                break;
			case PASS1code:
				ALU::result = ALU::in[1].connection->after;
                break;
			default:
				assert(false); //Dangerous if this code is edited. Never forget to put the breaks
				break;
			//TODO: Substruction?
        }

	}

private:
	Port in[2];
	Latch* out;
	long long result;
	Port control; 
};

/*Testing*/
int main()
{
	//Initialize Ports
	Latch latch1, latch2, output;
	Port control; 

	//Create device
	ALU ALU(latch1, latch2, output, control);

	//ADD TEST
	std::cout << "ADD TEST" << std::endl;
	control.before = 1; latch1.before = 100; latch2.before = 254;
	//Send clk to latches
	latch1.receive_clock();latch2.receive_clock();control.receive_clock();output.receive_clock();
	//Propagate data through device
	ALU.do_function();ALU.receive_clock();
	//Receive the clk and see the result
	std::cout << output.before <<std::endl;

}

