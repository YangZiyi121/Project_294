#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
//please include header file.
#include <cstdarg>
#include <queue>
using namespace std;


class ControlArray : public Device {
public:
	static const int cycles = 1;
	static const int area = 1;
	//static const double power = 0.001;
	ControlArray(Latch input[], Latch& output)
	{
        //Latch temp

        
		for (int i = 0; i < 5; i++)// salman change size to arraysize
		{
		
			ControlArray::in[i].connection = &(input[i]);
			
            cout << ControlArray::in[i].connection->before << endl;
		}

		ControlArray::out = &output;
		
		std::cout << "ControlArray is being created" << std::endl;

		
	} // Initialize the input ports and the latch as necessary
	void receive_clock() {
		ControlArray::out->before = ControlArray::result; 
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
            cout << md[y] << endl;
            y = y + 1;

        }
        ControlArray::result = removedele;

	}

private:
	Port in[20];
    const int arraysize = 20;
	Latch* out;
	long long result;
};

int main()
{
    Latch input[5], input2[5], control, output;
    int balance[5] = { 1000, 2, 3, 17, 50 };
    int talance[5] = { 10, 12, 13, 117, 150 };


    for (int i = 0; i < 5; i++)
    {
        input[i].before = balance[i];
        cout << input[i].before << endl;
    }

    ControlArray(input, output);

    for (int i = 0; i < 5; i++)
    {
        input[i].receive_clock();
       // cout << input[1].after << endl;
    }
    output.receive_clock();

    Device do_function();
    Device receive_clock();

    //

    for (int i = 0; i < 5; i++)
    {
        input[i].before = talance[i];
        cout << input[i].before << endl;
    }

    ControlArray(input, output);

    for (int i = 0; i < 5; i++)
    {
        input[i].receive_clock();
        // cout << input[1].after << endl;
    }
    output.receive_clock();

    Device do_function();
    Device receive_clock();


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