#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "Memory.h"
#include <cstring>

/**This method loads all instructions to the memory**/
// 1: hello.obj
// 2: logic.obj
// 3: fact6.obj
extern unsigned storage[SIZE];

const void readfile(int file_num){
    char file_name [30];  //holding the file name

    /*This part loaded different files for different testbenches*/
    switch (file_num)
    {
        case 1: std::cout << "case 1" << std::endl; strcpy(file_name, "tests/hello.obj"); break;
        case 2: strcpy(file_name, "tests/logic.obj"); break;
        case 3: strcpy(file_name, "tests/fact6.obj"); break;
        case 4: strcpy(file_name, "tests/arithmetic.obj"); break;
        default: strcpy(file_name, "tests/hello.obj");
    }

    /*Load the instruction from the file to the storage*/
    //Open files
    FILE *fp;
    std::cout << "Loading file: " << file_name << std::endl;
    fp = fopen(file_name, "rb");  // r for read, b for binary


    /*Load all instructions to the memory*/
    unsigned buffer;
    for (int i = 0; i < 25; i++) {
        fread((char *) &buffer, sizeof(unsigned), 1, fp);
        //printf("%x\n", buffer);
        std::memcpy(&storage[i], &buffer, sizeof(unsigned));
    }

}

/*Testing*/
// int main (){
//     readfile (argc);
//     Latch pc, op, rd, rs, rt, l;
//     MemoryInst device (pc, op, rd, rs, rt, l);

//     //Initilization
//     pc.before= int64_t(storage[0]);

//     //send clks to latches
//     pc.receive_clock(); op.receive_clock(); rd.receive_clock(); rs.receive_clock(); l.receive_clock();

//     //propagate data to device
//     device.do_function();
//     device.receive_clock();

//     //result should now be output.before 
//     std::cout << "This is the result of latches" <<std::endl;
//     printf("%x\n", op.before);
//     printf("%x\n", rd.before);
//     printf("%x\n", rs.before);
//     printf("%x\n", rt.before);
//     printf("%x\n", l.before);

// }
