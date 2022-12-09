#include <iostream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"


class Decoder : public Device {
public:
    Decoder(Latch& input, int size, Latch& output[])
    {
        arraysize = size;

        Decoder::in.connection = &input;

        for (int i = 0; i < arraysize; i++)
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

        switch (Decoder::in.connection->after)
        {
        case 0b00001:
            Decoder::result[0] = instrcution1;
            Decoder::result[1] = instruction2;
            break;


        case 0b00010:
            Decoder::result[0] = instrcution1;
            Decoder::result[1] = instruction2;
            break;

        case 3:
            
            break;
        default:
            cout << "INVALID INPUT";
            break;
    }

private:
    Port in;
    int arraysize;//keep size less than or euql to 20
    Latch* out[20];
    long long result[20];
};