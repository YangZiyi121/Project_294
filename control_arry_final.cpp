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
const int output_start = 70;
const int output_end = 80;



class ControlArray : public Device {
public:
	const int cycles = 1;
	const int area = 1;
	const double power = 0.001;
	ControlArray(Latch latches[])
	{
        //Latch temp

        
		for (int i = input_start; i < input_end; i++)
		{
		
            ControlArray::in[i - input_start].connection = &(latches[i]);
			
            
		}
        for (int i = output_start; i < output_end; i++)// salman change size to arraysize
        {
            ControlArray::out[i - output_start] = &(latches[i]);
        }
		std::cout << "ControlArray is being created" << std::endl;

		
	} // Initialize the input ports and the latch as necessary
	void receive_clock() {
        string s = std::bitset<17>(result).to_string();
        ControlArray::out[0]->before = convert_bintdec(stoi(s.substr(0, 1)));//PC MUX 1 bit latch70
        ControlArray::out[1]->before = convert_bintdec(stoi(s.substr(1, 1)));//MUX1 1 bit  latch 71
        ControlArray::out[2]->before = convert_bintdec(stoi(s.substr(2, 1)));//MUX2 1 bit latch 72
        ControlArray::out[3]->before = convert_bintdec(stoi(s.substr(3, 1)));//MUX3 1 bit latch 73
        ControlArray::out[4]->before = convert_bintdec(stoi(s.substr(4, 2)));//RF 2 bit latch 74
        ControlArray::out[5]->before = convert_bintdec(stoi(s.substr(6, 1)));//MUX4 1 bit latch 75
        ControlArray::out[6]->before = convert_bintdec(stoi(s.substr(7, 4)));//ALU 4 bit latch 76
        ControlArray::out[7]->before = convert_bintdec(stoi(s.substr(11, 2)));//IO 2 bit latch 77
        ControlArray::out[8]->before = convert_bintdec(stoi(s.substr(13, 2)));//DM 2 bit latch 78
        ControlArray::out[9]->before = convert_bintdec(stoi(s.substr(15, 2)));//MUX5 2 bit latch 79
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

   
	void do_function()
	{

        static int ik = 2;
        static int md[20] = { 0 };
        int t = 0;

        queue< int> q;

        for (int i = 0; i < output_end - output_start; i++) {
            if (ik == 2)
                q.push(ControlArray::in[i].connection->after);
            else
                q.push(ControlArray::in[i].connection->after | md[i]);

        }
        ik = ik + 1;
        
        int removedele = q.front();
        q.pop();
        cout << "removed element-" << removedele << endl;
        
        q.push(t);
        
        int y = 0;
        while (!q.empty())
        {
            md[y] = q.front();
            q.pop();
            cout << md[y] << endl;
            y = y + 1;

        }
        ControlArray::result = removedele;

	}

private:
    Port in[input_end - input_start];
    Latch* out[output_end - output_start];
    long long result;
};


//testing
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