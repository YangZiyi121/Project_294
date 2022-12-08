#include <iostream>
#include <fstream>
#include "Latch.h"
#include "Port.h"
#include "Device.h"
#include "Memory.h"

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
            mem_p = storage + MemoryInst::pc.connection->after; //which address
            std::memcpy(&)
            


        }
        void receive_clock(){

        }

            

    
    private:
       Port pc;
       Latch *op, *rd, *rs, *rt, *l;
       int64_t opResult, rdResult, rsResult, rtResult, lResult;
       unsigned char *mem_p;
};

int main(){
    //Load the instruction memory
    unsigned char *p; //pointer for memory
    p = storage;  //from 0 to 2^3
    int64_t program= 0x0100 0008 4800 4008; //first two instructions of hello.obj
    std::memcpy(p, &program, sizeof(int64_t));




}