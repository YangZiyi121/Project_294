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



class ControlArray : public Device {
public:
	static const int cycles = 1;
	static const int area = 1;
	//static const double power = 0.001;
	ControlArray(Latch input[], Latch output[])
	{
        //Latch temp

        
		for (int i = 0; i < 5; i++)// salman change size to arraysize
		{
		
			ControlArray::in[i].connection = &(input[i]);
			
            cout << ControlArray::in[i].connection->before << endl;
		}

		for (int i = 0; i < 10; i++)// salman change size to arraysize
        {
		ControlArray::out[i] = &(output[i]);
        }
		
		std::cout << "ControlArray is being created" << std::endl;

		
	} // Initialize the input ports and the latch as necessary
	void receive_clock() {
        string s = std::bitset<16>(result).to_string();
        cout << s << endl;
		ControlArray::out[0]->before = convert_bintdec( stoi(s.substr(0, 1)));//PC MUX 1 bit
        ControlArray::out[1]->before = convert_bintdec( stoi(s.substr(1, 1)));//MUX1 1 bit
        ControlArray::out[2]->before = convert_bintdec( stoi(s.substr(2, 1)));//MUX2 1 bit
        ControlArray::out[3]->before = convert_bintdec( stoi(s.substr(3, 1)));//MUX3 1 bit
        ControlArray::out[4]->before = convert_bintdec( stoi(s.substr(4, 2)));//RF 2 bit
        ControlArray::out[5]->before = convert_bintdec( stoi(s.substr(6, 2)));//MUX4 2 bit
        ControlArray::out[6]->before = convert_bintdec( stoi(s.substr(8, 4)));//ALU 4 bit
        ControlArray::out[7]->before = convert_bintdec( stoi(s.substr(12, 1)));//IO 1 bit
        ControlArray::out[8]->before = convert_bintdec( stoi(s.substr(13, 1)));//DM 1 bit
        ControlArray::out[9]->before = convert_bintdec( stoi(s.substr(14, 2)));//MUX5 2 bit
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

        for (int i = 0; i < 5; i++) {//salman change size to arraysize
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
	Port in[20];
    const int arraysize = 20;
	Latch* out[10];
	long long result;
    
};

int main()
{
    Latch input[5], input2[5], control, output[10];
    int balance[5] = { 0b0000001111101000, 4, 3, 17, 50 };
    int talance[5] = { 0b0011000001101011, 12, 13, 117, 150 };


    for (int i = 0; i < 5; i++)
    {
        input[i].before = balance[i];
        //cout << input[i].before << endl;
    }

    ControlArray sdfsdfsdf(input, output);

    for (int i = 0; i < 5; i++)
    {
        input[i].receive_clock();
       // cout << input[1].after << endl;
    }
    for (int i = 0; i < 10; i++)
    {
        output[i].receive_clock();
       // cout << input[1].after << endl;
    }

    sdfsdfsdf.do_function();
    sdfsdfsdf.receive_clock();

    cout << "PCMUX: " << output[0].before << endl;
    cout << "MUX1: " << output[1].before << endl;
    cout << "MUX2: " << output[2].before << endl;
    cout << "MUX3: " << output[3].before << endl;
    cout << "RF: " << output[4].before << endl;
    cout << "MUX4: " << output[5].before << endl;
    cout << "ALU: " << output[6].before << endl;
    cout << "IO: " << output[7].before << endl;
    cout << "DM: " << output[8].before << endl;
    cout << "MUX5: " << output[9].before << endl;
    

    for (int i = 0; i < 5; i++)
    {
        input[i].before = talance[i];
        //cout << input[i].before << endl;
    }

    //ControlArray all(input, output);

    for (int i = 0; i < 5; i++)
    {
        input[i].receive_clock();
        // cout << input[1].after << endl;
    }
    for (int i = 0; i < 10; i++)
    {
        output[i].receive_clock();
       // cout << input[1].after << endl;
    }

    sdfsdfsdf.do_function();
    sdfsdfsdf.receive_clock();

    cout << "PCMUX: " << output[0].before << endl;
    cout << "MUX1: " << output[1].before << endl;
    cout << "MUX2: " << output[2].before << endl;
    cout << "MUX3: " << output[3].before << endl;
    cout << "RF: " << output[4].before << endl;
    cout << "MUX4: " << output[5].before << endl;
    cout << "ALU: " << output[6].before << endl;
    cout << "IO: " << output[7].before << endl;
    cout << "DM: " << output[8].before << endl;
    cout << "MUX5: " << output[9].before << endl;


 	return 0;
 }

//int main()
//{
//    Latch input1, input2, control, output;
//
//    //Initialize latches
//    input1.before = 0b0000111101; //use this format if you want binary representation
//    input2.before = 0b0110001001;
//    control.before = 3;
//
//    //Create Device
//    Logic device(input1, input2, control, output);
//
//    //send clock to latches
//    input1.receive_clock();input2.receive_clock();control.receive_clock();output.receive_clock();
//    //std::cout << input1.after <<std::endl;
//
//    //propogate data through device
//    device.do_function();
//    device.receive_clock();
//
//    //result should now be output.before 
//    std::cout << output.before << std::endl;
//    std::cout << std::bitset<10>(output.before) << std::endl;
//
//}