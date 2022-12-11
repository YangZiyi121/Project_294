#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
//please include header file.
#include <cstdarg>
#include <queue>
#include <string>
#include <cmath>
using namespace std;
const int input_start = 80;
const int input_end = 100;
const int output_start = 80;
const int output_end = 100;



class ControlArray : public Device {
public:
	static const int cycles = 1;
	static const int area = 1;
	//static const double power = 0.001;
	ControlArray(Latch latches[])
	{
        //Latch temp

        
		for (int i = input_start; i < input_end; i++) // array to set inputs, they are 80-100
		{
		
			ControlArray::in[i-input_start].connection = &(latches[i]);
			
            //cout << ControlArray::in[i-45].connection->before << endl;
		}

		for (int i = output_start; i < output_end; i++)// salman change size to arraysize
        {
		ControlArray::out[i-output_start] = &(latches[i]);
        }
		
		std::cout << "ControlArray is being created" << std::endl;

		
	} // Initialize the input ports and the latch as necessary
	void receive_clock() {
        string s = std::bitset<16>(result).to_string();
        cout << s << endl;
		ControlArray::out[0]->before = convert_bintdec( stoi(s.substr(0, 1)));//PC MUX 1 bit latch70
        ControlArray::out[1]->before = convert_bintdec( stoi(s.substr(1, 1)));//MUX1 1 bit  latch 71
        ControlArray::out[2]->before = convert_bintdec( stoi(s.substr(2, 1)));//MUX2 1 bit latch 72
        ControlArray::out[3]->before = convert_bintdec( stoi(s.substr(3, 1)));//MUX3 1 bit latch 73
        ControlArray::out[4]->before = convert_bintdec( stoi(s.substr(4, 2)));//RF 2 bit latch 74
        ControlArray::out[5]->before = convert_bintdec( stoi(s.substr(6, 1)));//MUX4 1 bit latch 75
        ControlArray::out[6]->before = convert_bintdec( stoi(s.substr(7, 4)));//ALU 4 bit latch 76
        ControlArray::out[7]->before = convert_bintdec( stoi(s.substr(11, 1)));//IO 1 bit latch 77
        ControlArray::out[8]->before = convert_bintdec( stoi(s.substr(12, 1)));//DM 1 bit latch 78
        ControlArray::out[9]->before = convert_bintdec( stoi(s.substr(13, 2)));//MUX5 2 bit latch 79
	}
    long long convert_bintdec(long long n) {
        int dec = 0, i = 0, rem;

        while (n != 0) {
            rem = n % 10;
            n /= 10;
            dec += rem * pow(2, i);
            ++i;
        }

        return dec;
    }
    //Important Note:  receive_clock() in Latch should be modified for this case. .... for loop will be required in receive_clock() function ...> in[i].connection->after = in[i].connection->before.
	void do_function()
	{

        static int ik = 2;
        static int md[20] = { 0 };
        int t = 0;

        queue< int> q;

        for (int i = 0; i < output_end-output_start; i++) {//salman change size to arraysize
            if (ik == 2)
                q.push(ControlArray::in[i].connection->after);
            else
                q.push(ControlArray::in[i].connection->after | md[i]);

        }
        ik = ik + 1;
        //print_queue(q);
        int removedele = q.front();
        q.pop();
        cout << "removed element-" << removedele << endl;
        //print_queue(q);
        q.push(t);
        //print_queue(q);
        int y = 0;
        while (!q.empty())
        {
            md[y] = q.front();
            q.pop();
            cout << "i am here "<<md[y] << endl;
            y = y + 1;

        }
        ControlArray::result = removedele;

	}

private:
	Port in[input_end-input_start];
    //const int arraysize = 20;
	Latch* out[output_end-output_start];
	long long result;
    
};

// int main()
// {
//     Latch latches[50], input2[5], control, output[10];
//     int balance[5] = { 0b0000001111101000, 4, 3, 17, 50 };
//     int talance[5] = { 0b0011000001101011, 12, 13, 117, 150 };


//     for (int i = 0; i < 5; i++)
//     {
//         latches[i+45].before = balance[i];
//         //cout << input[i].before << endl;
//     }

//     ControlArray sdfsdfsdf(latches);

//     for (int i = 0; i < 50; i++)
//     {
//         latches[i].receive_clock();
//        // cout << input[1].after << endl;
//     }

//     sdfsdfsdf.do_function();
//     sdfsdfsdf.receive_clock();

//     cout << "PCMUX: " << latches[30+0].before << endl; 
//     cout << "MUX1: " << latches[30+1].before << endl; //latch 15
//     cout << "MUX2: " << latches[30+2].before << endl; //latch 21
//     cout << "MUX3: " << latches[30+3].before << endl;
//     cout << "RF: " << latches[30+4].before << endl;
//     cout << "MUX4: " << latches[30+5].before << endl;
//     cout << "ALU: " << latches[30+6].before << endl;
//     cout << "IO: " << latches[30+7].before << endl;
//     cout << "DM: " << latches[30+8].before << endl;
//     cout << "MUX5: " << latches[30+9].before << endl;
    

//     for (int i = 0; i < 5; i++)
//     {
//         latches[i+45].before = talance[i];
//         //cout << input[i].before << endl;
//     }

//     for (int i = 0; i < 50; i++)
//     {
//         latches[i].receive_clock();
//        // cout << input[1].after << endl;
//     }

//     sdfsdfsdf.do_function();
//     sdfsdfsdf.receive_clock();

//     cout << "PCMUX: " << latches[30+0].before << endl; 
//     cout << "MUX1: " << latches[30+1].before << endl; //latch 15
//     cout << "MUX2: " << latches[30+2].before << endl; //latch 21
//     cout << "MUX3: " << latches[30+3].before << endl;
//     cout << "RF: " << latches[30+4].before << endl;
//     cout << "MUX4: " << latches[30+5].before << endl;
//     cout << "ALU: " << latches[30+6].before << endl;
//     cout << "IO: " << latches[30+7].before << endl;
//     cout << "DM: " << latches[30+8].before << endl;
//     cout << "MUX5: " << latches[30+9].before << endl;
//  }

//  int main()
// {
//    //Latch input1, input2, control, output;

//    //Initialize latches
//    input1.before = 0b0000111101; //use this format if you want binary representation
//    input2.before = 0b0110001001;
//    control.before = 3;

//    //Create Device
//    //Logic device(input1, input2, control, output);

//    //send clock to latches
//    input1.receive_clock();input2.receive_clock();control.receive_clock();output.receive_clock();
//    //std::cout << input1.after <<std::endl;

//    //propogate data through device
//    device.do_function();
//    device.receive_clock();

//    //result should now be output.before 
//    std::cout << output.before << std::endl;
//    std::cout << std::bitset<10>(output.before) << std::endl;


//     Latch CA_input[20];
//     Latch CA_output[10]; //10 outputs

//     //Initialization
//     for (int i = 0; i < 20, i++){
//         CA_input->before = i;
//     }

//     //Create Device
//     ControlArray(Latch CA_input[], Latch CA_output[]);

    


// }