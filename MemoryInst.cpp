#include <iostream>
#include <fstream>
#include <stdio.h>
#include "Latch.h"
#include "Port.h"
#include "Device.h"
#include "Memory.h"
#include "instruction.cpp"
#include "Readfile.cpp"

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
    readfile(1); //load the hello.obj
    /*Testing*/
    Latch pc, op, rd, rs, rt, l;
    MemoryInst device (pc, op, rd, rs, rt, l);

    //Initilization
    unsigned * ptrStorage; //pointer to memory
    ptrStorage = storage;
    pc.before= reinterpret_cast<long long>(ptrStorage);

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