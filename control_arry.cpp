#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
//please include header file.
#include <cstdarg>
#include <queue>

class ControlArray : public Device {
public:
	static const int cycles = 1;
	static const int area = 1;
	static const double power = 0.001;
	ControlArray(Latch& input[], int size, Latch& output)
	{
        arraysize = size;

		for (int i = 0; i < arraysize; i++)
		{
		/*please change data type of before and after in latch or create new latch for this function*/
			ControlArray::in[i].connection = &input[i];
		}

		ControlArray::out = &output;
		
		std::cout << "ControlArray is being created" << std::endl;

		
	} // Initialize the input ports and the latch as necessary
	void receive_clock() {
		ControlArray::out->before = ControlArray::result; 
	}
	void do_function()
	{

        static int ik = 2;
        static int md[20] = { 0 };
        int t = 0;
        size = arraysize;

        queue< int> q;
        


        for (int i = 0; i < size; i++) {
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
    int arraysize;
	Latch* out;
	long long result;
};