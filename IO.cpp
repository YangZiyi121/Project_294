#include <iostream>
#include <stdio.h>
#include "Latch.h"
#include "Port.h"
#include "Device.h"
#include <string>

class IO: public Device{
    public:
        IO(Latch &rs, Latch &rd, Latch &control, Latch &output){
            IO::rs.connection = &rs;
            IO::rd.connection = &rd;
            IO::control.connection = &control;
            IO::output = &output;
            std::cout<< "IO is initialized"<< std::endl;
        }

        void do_function(){
            //std::cout << "control in IO" << control.connection->after << std::endl;
            if(control.connection->after == 1){
                //std::cout << "in input" << std::endl;
                switch (rs.connection -> after){
                    case 0: std::cout << "Type in integer for input: ";  scanf("%d", &result_int); result = result_int; break;
                    case 1: std::cout << "Type in char for input: "; scanf("%c", &result_char); result = result_char; break;
                }
            }
            else if (control.connection->after == 2){
                result = 0; //for default setting of outputing
                switch (rd.connection -> after){
                    case 0: std::cout << int(rs.connection->after) << std::endl;; break;
                    case 1: std::cout << char(rs.connection->after); break;
                }

            }
            else
            {
                result = 0;
            }


        }

        void receive_clock(){
            output->before = result;
            
        }


    private:
        Port rs;
        Port rd;  
        Port control; //0 for in and 1 for out
        Latch *output;  //in only
        char placeHolder;
        char result_char; //for accepting char type
        int result_int; // for accepting int type
        long long result;

};

// int main(){
//     Latch rs, rd, control, output;
//     IO device (rs, rd, control, output);

//     //Output character test
//     rs.before = 'h';
//     rd.before = 1; //for char
//     control.before = 2; //for output
//     //send clks to latches
//     rs.receive_clock(); rd.receive_clock(); control.receive_clock(); output.receive_clock();
//     //propagate data to device
//     device.do_function();
//     device.receive_clock();


//     //Output integer test
//     rs.before = 5000;
//     rd.before = 0;
//     control.before = 2;
//     //send clks to latches
//     rs.receive_clock(); rd.receive_clock(); control.receive_clock(); output.receive_clock();
//     //propagate data to device
//     device.do_function();
//     device.receive_clock();


//     //Input character test
//     rs.before = 1;
//     control.before = 1;
//     //send clks to latches
//     rs.receive_clock(); rd.receive_clock(); control.receive_clock(); output.receive_clock();
//     //propagate data to device
//     device.do_function();
//     device.receive_clock();
//     std::cout << "Out char " << char(output.before) << std::endl;



//     //Input integer test
//     rs.before = 0;
//     control.before = 1;
//     //send clks to latches
//     rs.receive_clock(); rd.receive_clock(); control.receive_clock(); output.receive_clock();
//     //propagate data to device
//     device.do_function();
//     device.receive_clock();
    // std::cout  << "Out integer "<< output.before << std::endl;


// }