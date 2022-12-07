#include <iostream>
#include <fstream>
#include "Latch.h"
#include "Device.h"
#include "Port.h"
#include "Memory.cpp"



int main()
{
    //Loading
    Latch &address, &write_value, &read_value, &r_w;
    //file reading
    fstream myfile;
    myfile.open("/tests/hello.obj");
    int64_t value;
    myfile >> hex >> value;
    std::cout << value;






    address.after = 0x0000000000000000;   //starting address of instruction
    r_w.after = 0x1;




    Memory memory(address, write_value, read_value, r_w);





}