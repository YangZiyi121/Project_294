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

        // std::cout << "input for decoder: "<<Decoder::in.connection->after << std::endl;
        //these are default cases, they happen with most ALU operations
        Decoder::result[0] = stoull("00000000000000000", 0, 2);//mux1 cycle
        Decoder::result[1] = stoull("00000000000000000", 0, 2);//mux2 mux3 cycle
        Decoder::result[2] = stoull("00000000000000000", 0, 2);//RF cycle
        Decoder::result[3] = stoull("00000000000000000", 0, 2);//io mux4 cycle 
        Decoder::result[4] = stoull("00000000000000000", 0, 2);//alu cycle
        Decoder::result[5] = stoull("00000000000000000", 0, 2);//dm cycle
        Decoder::result[6] = stoull("00000000000000001", 0, 2);//mux5 cycle
        Decoder::result[7] = stoull("00110000000000000", 0, 2);//mux2 mux3 WB cycle
        Decoder::result[8] = stoull("00001100000000000", 0, 2);//RF WB cycle
        Decoder::result[9] =  stoull("00000000000000000", 0, 2);//cy 10
        Decoder::result[10] = stoull("10000000000000000", 0, 2);//cycle to get next istruction
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
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//RF cycle
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000001000000", 0, 2);//cy 5
            
            break;

        case 0x1: //addi
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//RF cycle
            Decoder::result[3] = stoull("00000010000000000", 0, 2);//cy 4
            Decoder::result[4] = stoull("00000000001000000", 0, 2);//cy 5
            break;
        case 0x2://sub rd, rs, rt
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//RF cycle
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000010000000", 0, 2);//cy 5

            break;
        case 0x3://subi rd, L
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//RF cycle
            Decoder::result[3] = stoull("00000010000000000", 0, 2);
            Decoder::result[4] = stoull("00000000010000000", 0, 2);//cy 5

            break;
        case 0x4://mul rd, rs, rt
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//RF cycle
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000011000000", 0, 2);//cy 5
                                      
                                      
            break;
        case 0x5://div rd, rs, rt
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//RF cycle
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000100000000", 0, 2);//cy 5
                                     
            break;
        case 0x6: //and rd, rs, rt
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//RF cycle
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000110000000", 0, 2);//cy 5

            break;
        case 0x7://or rd, rs, rt
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//RF cycle
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000111000000", 0, 2);//cy 5

            break;
        case 0x8://xor rd, rs, rt
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//RF cycle
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000001000000000", 0, 2);//cy 5

            break;
        case 0x9://not rd, rs
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//RF cycle
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000101000000", 0, 2);//cy 5
            break;

        case 0xa://shftr rd, rs, rt
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//RF cycle
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000001001000000", 0, 2);//cy 5
            break;

        case 0xb://shftri rd, L
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//RF cycle
            Decoder::result[3] = stoull("00000010000000000", 0, 2);
            Decoder::result[4] = stoull("00000001001000000", 0, 2);//cy 5
            break;

        case 0xc://shftl rd, rs, rt
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//RF cycle
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000001010000000", 0, 2);//cy 5
            break;

        case 0xd://shftli rd, L
            Decoder::result[2] = stoull("00001000000000000", 0, 2);//RF cycle
            Decoder::result[3] = stoull("00000010000000000", 0, 2);
            Decoder::result[4] = stoull("00000001010000000", 0, 2);//cy 5
            break;

        case 0x15: //mov rd, (rs)(L)
            Decoder::result[0] = stoull("01000000000000000", 0, 2);
            Decoder::result[3] = stoull("00000010000000000", 0, 2);
            Decoder::result[4] = stoull("00000000001000000", 0, 2);//cy 5
            Decoder::result[5] = stoull("00000000000000100", 0, 2);//cy 5
            Decoder::result[6] = stoull("00000000000000010", 0, 2);//cy 5
            break;

        case 0x16://mov rd, rs
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000001011000000", 0, 2);//cy 5
            break;

        case 0x17: //mov rd, L
            Decoder::result[3] = stoull("00000010000000000", 0, 2);
            Decoder::result[4] = stoull("00000001100000000", 0, 2);//cy 5
            break;

        case 0x18: //mov (rd)(L), rs
            Decoder::result[0] = stoull("01000000000000000", 0, 2);
            Decoder::result[2] = stoull("00000000000000000", 0, 2);
            Decoder::result[3] = stoull("00000001100000000", 0, 2);
            Decoder::result[4] = stoull("00000000000001000", 0, 2);//cy 5

            Decoder::result[5] = stoull("00000000000000000", 0, 2);//cy 5
            Decoder::result[6] = stoull("00000000000000000", 0, 2);//cy 5
            Decoder::result[7] = stoull("00000000000000000", 0, 2);//cy 5
            Decoder::result[8] = stoull("00000000000000000", 0, 2);//cy 5
            break;

        case 0x1d: //in rd, rs
            Decoder::result[0] = stoull("01000000000000000", 0, 2);//cy 1           
            Decoder::result[3] = stoull("00000000000010000", 0, 2);//cy 4
            Decoder::result[4] = stoull("00000000000000000", 0, 2);//cy 5
            Decoder::result[5] = stoull("00000000000000000", 0, 2);//cy 5
            Decoder::result[6] = stoull("00000000000000000", 0, 2);//cy 5
            Decoder::result[7] = stoull("00110000000000000", 0, 2);//cy 8
            Decoder::result[8] = stoull("00001100000000000", 0, 2);//cy 9
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
            break;
        case 0x1f:
            std::cout << "" <<std::endl; //if this is not here then any output not with endl will be lost
            std::cout << "halted!" <<std::endl; //if this is not here then any output not with endl will be lost
            exit(0);

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