#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Latch.h"
#include "Port.h"
#include "Device.h"
#include "Memory.h"
#include "Instruction.cpp"

class MemoryInst : public Device{
    public:
        MemoryInst(Latch &pc, Latch &op, Latch &rd, Latch &rs, Latch &rt, Latch &l){
            MemoryInst::pc.connection = &pc;
            MemoryInst::op = &op;
            MemoryInst::rd = &rd;
            MemoryInst::rs = &rs;
            MemoryInst::rt = &rt;
            MemoryInst::l = &l;
            std::cout<< "Memory Instruction is initailized"<< std::endl;
        }

        void do_function(){
            std::memcpy(&instruction, reinterpret_cast<unsigned int *>(pc.connection->before), sizeof(unsigned));
            instruction_decoder(instruction);
            opResult = opcode;
            rdResult = reg_d;
            rsResult = reg_s;
            rtResult = reg_t_code;
            lResult = literal;
        }
        void receive_clock(){
            op->before = opResult;
            rd->before = rdResult;
            rs->before = rsResult;
            rt->before = rtResult;
            l ->before = lResult;
        }

            

    
    private:
       Port pc;
       Latch *op, *rd, *rs, *rt, *l;
       unsigned opResult, rdResult, rsResult, rtResult, lResult;
       unsigned instruction;
};

int main(){
    /*Load the instruction from the file to the storage*/
    //Open files
    FILE *fp;
    char ch;
    fp = fopen("tests/hello.obj","rb");  // r for read, b for binary
    unsigned * ptrStorage; //pointer to memory
    unsigned buffer;
    ptrStorage = storage;

  
    /*Load all instructions to the memory*/
    for (int i = 0; i < 25; i++) 
   {
        fread((char *) &buffer, sizeof(unsigned), 1, fp);
        //printf("%x\n", buffer);
        std::memcpy(ptrStorage, &buffer, sizeof(unsigned));
        ptrStorage = ptrStorage + 1; //move to the next position
    }

    // //validate
    // printf("%x\n", storage[0]);
    // printf("%x\n", storage[1]);

    /*Testing*/
    Latch pc, op, rd, rs, rt, l;
    MemoryInst device (pc, op, rd, rs, rt, l);

    //Initilization
    ptrStorage = storage;
    pc.before= reinterpret_cast<long long>(ptrStorage + 1);

    //send clks to latches
    pc.receive_clock(); op.receive_clock(); rd.receive_clock(); rs.receive_clock(); l.receive_clock();

    //propagate data to device
    device.do_function();
    device.receive_clock();

    //result should now be output.before 
    std::cout << "This is the result of latches" <<std::endl;
    printf("%x\n", op.before);
    printf("%x\n", rd.before);
    printf("%x\n", rs.before);
    printf("%x\n", rt.before);
    printf("%x\n", l.before);
    
}