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

        for (int i = 80; i < 100; i++)
        {

            Decoder::out[i-80] = &latches[i];
        }

        std::cout << "Decoder is being created" << std::endl;


    } // Initialize the input ports and the latch as necessary
    void receive_clock() {
        for (int i = 0; i < 20; i++)
        {
            Decoder::out[i]->before = Decoder::result[i];
        }

    }
    void do_function()
    {
        /*string string s[9] = { "00000000000000000", "00000000000000000", "00001000000000000", "00000000000000000", 
            "00000000001000000",  "00000000000000000", "00000000000000001", "00110000000000000", "00001100000000000" };*/
        /*
        x0xxxxxxxxxxxxxxx
        xx00xxxxxxxxxxxxx
        xxxx10xxxxxxxxxxx
        xxxxxx xxxxxxxxxx
        xxxxxxx    xxxxxx
        xxxxxxxxxxxxxxxxx
        xxxxxxxxxxxxxxxx1
        xx11xxxxxxxxxxxxx
        xxxx11xxxxxxxxxxx
        */
        Decoder::result[0] = stoull("00000000000000000", 0, 2);//cy 1
        Decoder::result[1] = stoull("00000000000000000", 0, 2);//cy 2
        Decoder::result[2] = stoull("00001000000000000", 0, 2);//cy 3
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
            //cout << "i am here" << endl;
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000001000000", 0, 2);//cy 5
            
            break;


        case 0x1:    //addi rd, L                 //"00001000000000000"
            Decoder::result[3] = stoull("00000010000000000", 0, 2);
            Decoder::result[4] = stoull("00000000001000000", 0, 2);//cy 5
            break;

        case 0x2://sub rd, rs, rt
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000010000000", 0, 2);//cy 5

            break;
        case 0x3://subi rd, L
            Decoder::result[3] = stoull("00000010000000000", 0, 2);
            Decoder::result[4] = stoull("00000000010000000", 0, 2);//cy 5

            break;
        case 0x4://mul rd, rs, rt
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000011000000", 0, 2);//cy 5
                                      //"00000000001000000"
                                      
            break;
        case 0x5://div rd, rs, rt
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000100000000", 0, 2);//cy 5
                                      //"00000000010000000"
            break;
        case 0x6: //and rd, rs, rt
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000110000000", 0, 2);//cy 5

            break;
        case 0x7://or rd, rs, rt
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000111000000", 0, 2);//cy 5

            break;
        case 0x8://xor rd, rs, rt
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000001000000000", 0, 2);//cy 5

            break;
        case 0x9://not rd, rs
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000101000000", 0, 2);//cy 5
            break;

        case 0xa://shftr rd, rs, rt
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000001001000000", 0, 2);//cy 5
            break;

        case 0xb://shftri rd, L
            Decoder::result[3] = stoull("00000010000000000", 0, 2);
            Decoder::result[4] = stoull("00000001001000000", 0, 2);//cy 5
            break;

        case 0xc://shftl rd, rs, rt
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000001010000000", 0, 2);//cy 5
            break;

        case 0xd://shftli rd, L
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

        case 0x1e://out rd, rs
            Decoder::result[0] = stoull("01000000000000000", 0, 2);//cy 1           
            Decoder::result[3] = stoull("00000000000100000", 0, 2);//cy 4
            Decoder::result[4] = stoull("00000000000000000", 0, 2);//cy 5
            Decoder::result[6] = stoull("00000000000000000", 0, 2);//cy 7
            Decoder::result[7] = stoull("00000000000000000", 0, 2);//cy 8
            Decoder::result[8] = stoull("00000000000000000", 0, 2);//cy 9

            break;
        default:
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
int main()
{
    //Latch input1, input2, control, output[20];
    //input1.before = 0;
    //Decoder ssss(input1, 20, output);

    ////input1.receive_clock();
    //cout << input1.after << endl;
    //for (int i = 0; i < 20; i++)
    //{
    //    output[i].receive_clock();
    //}
    //ssss.do_function();
    //ssss.receive_clock();
    return 0;
}