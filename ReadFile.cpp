#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "Memory.h"


/**This method loads all instructions to the memory**/
// 1: hello.obj
// 2: logic.obj
// 3: fact6.obj
const void readfile(int file_num){
    char file_name [30];
    switch (file_num)
    {
        case 1: strcpy(file_name, "tests/hello.obj"); break;
        case 2: strcpy(file_name, "tests/logic.obj"); break;
        case 3: strcpy(file_name, "tests/fact6.obj"); break;
        default: strcpy(file_name, "tests/hello.obj");
    }

    /*Load the instruction from the file to the storage*/
    //Open files
    FILE *fp;
    std::cout << "Loading file: " << file_name << std::endl;
    fp = fopen(file_name, "rb");  // r for read, b for binary

    unsigned * ptrStorage; //pointer to memory
    unsigned buffer;
    ptrStorage = storage;

    /*Load all instructions to the memory*/
    for (int i = 0; i < 25; i++) {
        fread((char *) &buffer, sizeof(unsigned), 1, fp);
        //printf("%x\n", buffer);
        std::memcpy(ptrStorage, &buffer, sizeof(unsigned));
        ptrStorage = ptrStorage + 1; //move to the next position
    }

}