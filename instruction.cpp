#include <iostream>
#include <stdio.h>
static unsigned opcode;
static unsigned reg_d;
static unsigned reg_s;
static unsigned reg_t_code;
static unsigned literal;

/*This const function takes an unsigned instruction, decode it and give the decoded results*/
const void instruction_decoder(unsigned instr){
    opcode = instr >> 27;
    reg_d  = instr >> 22 & 0x1f;
    reg_s  = instr >> 17 & 0x1f;
    reg_t_code  = instr >> 12 & 0x1f;
    literal = instr & 0xfff;

    // std::cout << "Got op code " << opcode << std::endl;
    // std::cout << "Got reg_d code " << reg_d << std::endl;
    // std::cout << "Got reg_s code " << reg_s << std::endl;
    // std::cout << "Got reg_t code " << reg_t_code << std::endl;
    // std::cout << "Got literal code " << literal << std::endl;
};

// int main()
// {
//     unsigned buffer;
//     FILE *ptr;
//     ptr = fopen("tests/hello.obj","rb");  // r for read, b for binary
//     fread((char *) &buffer,sizeof(unsigned),1,ptr);
 
//     printf("%x\n", buffer);
//     instruction_decoder(buffer);

//     fread((char *) &buffer,sizeof(unsigned),1,ptr);
//     printf("%x\n", buffer);
//     instruction_decoder(buffer);
    
// }