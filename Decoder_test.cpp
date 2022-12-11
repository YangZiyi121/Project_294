#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
#include <string> 



using namespace std;

class Decoder : public Device {
public:
    Decoder(Latch& input, Latch latches[])
    {
       

        Decoder::in.connection = &input;

        for (int i = input_start; i < input_end; i++) // from start of inputs to control to end
		{
			Decoder::out[i-input_start] = &(latches[i]);
		}

        std::cout << "Decoder is being created" << std::endl;


    } // Initialize the input ports and the latch as necessary
    void receive_clock() {
        for (int i = 0; i < arraysize; i++)
        {
            Decoder::out[i]->before = Decoder::result[i];
        }
    }
    void do_function()
    {
        //these are default cases, they happen with most ALU operations
        Decoder::result[0] = stoull("00000000000000000", 0, 2);//cy 1
        Decoder::result[1] = stoull("00000000000000000", 0, 2);//cy 2
        Decoder::result[2] = stoull("00000000000000000", 0, 2);//cy 3
        Decoder::result[3] = stoull("00000000000000000", 0, 2);//cy 4
        Decoder::result[4] = stoull("00000000001000000", 0, 2);//cy 5
        Decoder::result[5] = stoull("00000000000000000", 0, 2);//cy 6
        Decoder::result[6] = stoull("00000000000000001", 0, 2);//cy 7
        Decoder::result[7] = stoull("00110000000000000", 0, 2);//cy 8
        Decoder::result[8] = stoull("00001100000000000", 0, 2);//cy 9
        Decoder::result[9] =  stoull("00000000000000000", 0, 2);//cy 10
        Decoder::result[10] = stoull("00000000000000000", 0, 2);
        Decoder::result[11] = stoull("00000000000000000", 0, 2);
        Decoder::result[12] = stoull("00000000000000000", 0, 2);
        Decoder::result[13] = stoull("00000000000000000", 0, 2);
        Decoder::result[14] = stoull("00000000000000000", 0, 2);
        Decoder::result[15] = stoull("00000000000000000", 0, 2);
        Decoder::result[16] = stoull("00000000000000000", 0, 2);
        Decoder::result[17] = stoull("00000000000000000", 0, 2);
        Decoder::result[18] = stoull("00000000000000000", 0, 2);
        Decoder::result[19] = stoull("00000000000000000", 0, 2);

        switch (Decoder::in.connection->after)
        {
        case 0x0://add rd, rs, rt // to have number or opcode in integer number....
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000001000000", 0, 2);//cy 5
            
            break;

        case 0x1: //addi                   
            Decoder::result[2] = stoull("00000000000000000", 0, 2);//cy 3
            Decoder::result[3] = stoull("00000010000000000", 0, 2);//cy 4
            break;
        case 0x2:
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000010000000", 0, 2);//cy 5
            break;

        case 0x3:
            Decoder::result[3] = stoull("00000010000000000", 0, 2);
            Decoder::result[4] = stoull("00000000010000000", 0, 2);//cy 5
            break;

        case 0x4:
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000011000000", 0, 2);//cy 5                   
            break;

        case 0x5:
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000100000000", 0, 2);//cy 5

            break;
        case 0x6:
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000110000000", 0, 2);//cy 5
            break;
        case 0x7:
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000111000000", 0, 2);//cy 5
            break;

        case 0x8:
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000001000000000", 0, 2);//cy 5
            break;

        case 0x9:
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000101000000", 0, 2);//cy 5
            break;

        case 0x1e:
            Decoder::result[0] = stoull("01000000000000000", 0, 2);//cy 1
            Decoder::result[1] = stoull("00000000000000000", 0, 2);//cy 2
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//cy 3
            Decoder::result[3] = stoull("00000000000100000", 0, 2);//cy 4
            Decoder::result[4] = stoull("00000000000000000", 0, 2);//cy 5
            Decoder::result[5] = stoull("00000000000000000", 0, 2);//cy 6
            Decoder::result[6] = stoull("00000000000000000", 0, 2);//cy 7
            Decoder::result[7] = stoull("00000000000000000", 0, 2);//cy 8
            Decoder::result[8] = stoull("00000000000000000", 0, 2);//cy 9
            Decoder::result[9] = stoull("00000000000000000", 0, 2);//cy 10
            Decoder::result[10] = stoull("00000000000000000", 0, 2);
            Decoder::result[11] = stoull("00000000000000000", 0, 2);
            Decoder::result[12] = stoull("00000000000000000", 0, 2);
            Decoder::result[13] = stoull("00000000000000000", 0, 2);
            Decoder::result[14] = stoull("00000000000000000", 0, 2);
            Decoder::result[15] = stoull("00000000000000000", 0, 2);
            Decoder::result[16] = stoull("00000000000000000", 0, 2);
            Decoder::result[17] = stoull("00000000000000000", 0, 2);
            Decoder::result[18] = stoull("00000000000000000", 0, 2);
            Decoder::result[19] = stoull("00000000000000000", 0, 2);

            break;
        default:
            // send all zeros on these
            Decoder::result[0] = stoull("00000000000000000", 0, 2);//cy 1
            Decoder::result[1] = stoull("00000000000000000", 0, 2);//cy 2
            Decoder::result[2] = stoull("00000000000000000", 0, 2);//cy 3
            Decoder::result[3] = stoull("00000000000000000", 0, 2);//cy 4
            Decoder::result[4] = stoull("00000000000000000", 0, 2);//cy 5
            Decoder::result[5] = stoull("00000000000000000", 0, 2);//cy 6
            Decoder::result[6] = stoull("00000000000000000", 0, 2);//cy 7
            Decoder::result[7] = stoull("00000000000000000", 0, 2);//cy 8
            Decoder::result[8] = stoull("00000000000000000", 0, 2);//cy 9
            Decoder::result[9] = stoull("00000000000000000", 0, 2);//cy 10
            Decoder::result[10] = stoull("00000000000000000", 0, 2);
            Decoder::result[11] = stoull("00000000000000000", 0, 2);
            Decoder::result[12] = stoull("00000000000000000", 0, 2);
            Decoder::result[13] = stoull("00000000000000000", 0, 2);
            Decoder::result[14] = stoull("00000000000000000", 0, 2);
            Decoder::result[15] = stoull("00000000000000000", 0, 2);
            Decoder::result[16] = stoull("00000000000000000", 0, 2);
            Decoder::result[17] = stoull("00000000000000000", 0, 2);
            Decoder::result[18] = stoull("00000000000000000", 0, 2);
            Decoder::result[19] = stoull("00000000000000000", 0, 2);
            break;
        }
    }

private:
    Port in;
    const int arraysize = 20;//keep size less than or euql to 20
    Latch* out[20];
    long long result[20];
};
// int main()
// {
//     Latch input1, input2, control, output[20];
//     input1.before = 0;
//     Decoder ssss(input1, 20, output);

//     //input1.receive_clock();
//     cout << input1.after << endl;
//     for (int i = 0; i < 20; i++)
//     {
//         output[i].receive_clock();
//     }
//     ssss.do_function();
//     ssss.receive_clock();
// }