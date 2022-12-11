#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
#include <string> 

using namespace std;

class Decoder : public Device {
public:
    Decoder(Latch& input, int size, Latch output[])
    {
       

        Decoder::in.connection = &input;

        for (int i = 0; i < size; i++)
        {

            Decoder::out[i] = &output[i];
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


        case 0x1:                     //"00001000000000000"
            Decoder::result[3] = stoull("00000010000000000", 0, 2);
            Decoder::result[4] = stoull("00000000001000000", 0, 2);//cy 5
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
                                      //"00000000001000000"
                                      
            break;
        case 0x5:
            Decoder::result[3] = stoull("00000000000000000", 0, 2);
            Decoder::result[4] = stoull("00000000100000000", 0, 2);//cy 5
                                      //"00000000010000000"
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
            cout << "INVALID INPUT";
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
    Latch input1, input2, control, output[20];
    input1.before = 0;
    Decoder ssss(input1, 20, output);

    //input1.receive_clock();
    cout << input1.after << endl;
    for (int i = 0; i < 20; i++)
    {
        output[i].receive_clock();
    }
    ssss.do_function();
    ssss.receive_clock();
}