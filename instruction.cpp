#include <iostream>
#include <stdio.h>
class Instruction {
public:
    Instruction(unsigned instr){
    opcode = instr >> 27;
    reg_d  = instr >> 22 & 0x1f;
    reg_s  = instr >> 17 & 0x1f;
    reg_t  = instr >> 12 & 0x1f;
    literal = instr & 0xfff;

    std::cout << "Got op code " << opcode << std::endl;
    std::cout << "Got reg_d code " << reg_d << std::endl;
    std::cout << "Got reg_s code " << reg_s << std::endl;
    std::cout << "Got reg_t code " << reg_t << std::endl;
    std::cout << "Got literal code " << literal << std::endl;
};

private:
    unsigned opcode;
    unsigned reg_d;
    unsigned reg_s;
    unsigned reg_t;
    unsigned literal;
    int label;
};


int main()
{
    unsigned buffer;
    FILE *ptr;
    ptr = fopen("tests/hello.obj","rb");  // r for read, b for binary
    fread((char *) &buffer,sizeof(unsigned),1,ptr);
    /*
    for(int i = 0; i<10; i++)
    printf("%u", buffer[i]);
    */
    printf("%x\n", buffer);
    Instruction i(buffer);

    fread((char *) &buffer,sizeof(unsigned),1,ptr);
    printf("%x\n", buffer);
    Instruction i1(buffer);
    
}