#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
#include <assert.h>

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
#define SUBcode 2
#define MULTcode 3
#define DIVcode 4
#define NOTcode 5
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
	void receive_clock() {
		if(--delay > 0){
			;
		}
		else
			ALU::out->before = ALU::result; //cout << "   " << ALU::out->before << endl; 
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
				delay = 3;
                break;
            case DIVcode:
                ALU::result = ALU::in[0].connection->after / ALU::in[1].connection->after;
				delay = 8;
                break;
            case NOTcode:
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
				//assert(false); //Dangerous if this code is edited. Never forget to put the breaks
				break;
			//TODO: Substruction?
        }

	}

private:
	Port in[2];
	Latch* out;
	long long result;
	Port control; 
	char delay = 1;

};

// /*Testing*/
// int main()
// {
// 	//Initialize Ports
// 	Latch latch1, latch2, output;
// 	Latch control; 

// 	//Create device
// 	ALU ALU(latch1, latch2, output, control);

// 	//ADD TEST
// 	std::cout << "ADD TEST" << std::endl;
// 	control.before = ADDcode; latch1.before = 100; latch2.before = 254;
// 	//Send clk to latches
// 	latch1.receive_clock();latch2.receive_clock();control.receive_clock();output.receive_clock();
// 	//Propagate data through device
// 	ALU.do_function();ALU.receive_clock();
// 	//Receive the clk and see the result
// 	std::cout << output.before <<std::endl;
// 	assert(output.before == 354);

// 	//MULT TEST
// 	std::cout << "MULT TEST" << std::endl;
// 	control.before = MULTcode; latch1.before = 100; latch2.before = 254;
// 	//Send clk to latches
// 	latch1.receive_clock();latch2.receive_clock();control.receive_clock();output.receive_clock();
// 	//Propagate data through device
// 	ALU.do_function();ALU.receive_clock();ALU.receive_clock();ALU.receive_clock();
// 	//Receive the clk and see the result
// 	std::cout << output.before <<std::endl;
// 	assert(output.before == 25400);

// 	//SUB TEST
// 	std::cout << "SUB TEST" << std::endl;
// 	control.before = SUBcode; latch1.before = 1000; latch2.before = 254;
// 	//Send clk to latches
// 	latch1.receive_clock();latch2.receive_clock();control.receive_clock();output.receive_clock();
// 	//Propagate data through device
// 	ALU.do_function();ALU.receive_clock();
// 	//Receive the clk and see the result
// 	std::cout << output.before <<std::endl;
// 	assert(output.before == 746);

// 	//DIV TEST
// 	std::cout << "DIV TEST" << std::endl;
// 	control.before = DIVcode; latch1.before = 100; latch2.before = 2;
// 	//Send clk to latches
// 	latch1.receive_clock();latch2.receive_clock();control.receive_clock();
// 	//Propagate data through device
// 	ALU.do_function();ALU.receive_clock();ALU.receive_clock();ALU.receive_clock();ALU.receive_clock();ALU.receive_clock();ALU.receive_clock();ALU.receive_clock();ALU.receive_clock();
// 	//Receive the clk and see the result
// 	std::cout << output.before <<std::endl;
// 	assert(output.before == 50);

// 	//NOT TEST
// 	std::cout << "NOT TEST" << std::endl;
// 	control.before = NOTcode; latch1.before = 0b1111/*That's a 15 and should be flipped into -16 (ones-complement?)*/; latch2.before = 0;
// 	//Send clk to latches
// 	latch1.receive_clock();latch2.receive_clock();control.receive_clock();output.receive_clock();
// 	//Propagate data through device
// 	ALU.do_function();ALU.receive_clock();
// 	//Receive the clk and see the result
// 	std::bitset<16> y(output.before);
// 	assert(output.before == -16);

// 	//AND TEST
// 	std::cout << "AND TEST" << std::endl;
// 	control.before = ANDcode; latch1.before = 0b1101; latch2.before = 0b1010;
// 	//Send clk to latches
// 	latch1.receive_clock();latch2.receive_clock();control.receive_clock();output.receive_clock();
// 	//Propagate data through device
// 	ALU.do_function();ALU.receive_clock();
// 	//Receive the clk and see the result
// 	std::cout << output.before <<std::endl;
// 	assert(output.before == 0b1000);

// 	//OR TEST
// 	std::cout << "OR TEST" << std::endl;
// 	control.before = ORcode; latch1.before = 0b1101; latch2.before = 0b1010;
// 	//Send clk to latches
// 	latch1.receive_clock();latch2.receive_clock();control.receive_clock();output.receive_clock();
// 	//Propagate data through device
// 	ALU.do_function();ALU.receive_clock();
// 	//Receive the clk and see the result
// 	std::cout << output.before <<std::endl;
// 	assert(output.before == 0b1111);

// 	//XOR TEST
// 	std::cout << "XOR TEST" << std::endl;
// 	control.before = XORcode; latch1.before = 0b1101; latch2.before = 0b1010;
// 	//Send clk to latches
// 	latch1.receive_clock();latch2.receive_clock();control.receive_clock();output.receive_clock();
// 	//Propagate data through device
// 	ALU.do_function();ALU.receive_clock();
// 	//Receive the clk and see the result
// 	std::cout << output.before <<std::endl;
// 	assert(output.before == 0b0111);

// 	//SRL TEST
// 	std::cout << "SRL TEST" << std::endl;
// 	control.before = SRLcode; latch1.before = 0b1000; latch2.before = 0b10;
// 	//Send clk to latches
// 	latch1.receive_clock();latch2.receive_clock();control.receive_clock();output.receive_clock();
// 	//Propagate data through device
// 	ALU.do_function();ALU.receive_clock();
// 	//Receive the clk and see the result
// 	std::cout << output.before <<std::endl;
// 	assert(output.before == 0b10);

// 	//SLL TEST
// 	std::cout << "SLL TEST" << std::endl;
// 	control.before = SLLcode; latch1.before = 0b1000; latch2.before = 0b10;
// 	//Send clk to latches
// 	latch1.receive_clock();latch2.receive_clock();control.receive_clock();output.receive_clock();
// 	//Propagate data through device
// 	ALU.do_function();ALU.receive_clock();
// 	//Receive the clk and see the result
// 	std::cout << output.before <<std::endl;
// 	assert(output.before == 0b100000);

// 	//PASS0 TEST
// 	std::cout << "PASS0 TEST" << std::endl;
// 	control.before = PASS0code; latch1.before = 0b1101; latch2.before = 0b1010;
// 	//Send clk to latches
// 	latch1.receive_clock();latch2.receive_clock();control.receive_clock();output.receive_clock();
// 	//Propagate data through device
// 	ALU.do_function();ALU.receive_clock();
// 	//Receive the clk and see the result
// 	std::cout << output.before <<std::endl;
// 	assert(output.before == 0b1101);

// 	//PASS1 TEST
// 	std::cout << "PASS1 TEST" << std::endl;
// 	control.before = PASS1code; latch1.before = 0b1101; latch2.before = 0b1010;
// 	//Send clk to latches
// 	latch1.receive_clock();latch2.receive_clock();control.receive_clock();output.receive_clock();
// 	//Propagate data through device
// 	ALU.do_function();ALU.receive_clock();
// 	//Receive the clk and see the result
// 	std::cout << output.before <<std::endl;
// 	assert(output.before == 0b1010);

// 	return 0;
// }

