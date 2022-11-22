#include <iostream>
#include "Latch.h"
#include "Port.h"
#include <map>

class Memory{
    public:
        std::map <int64_t, int64_t> storage; // <address, value >
        //Constructer
        Memory(void){
            storage.insert(std::pair<int64_t, int64_t>(0x0000000011111111, 0x1111111100000000));
            std::cout<< "Memory is initailized"<< std::endl;
            std::cout << std::hex << storage[0x0000000011111111] << std::endl;
        }
        //Write
        void write_to_memory (Latch &address, Latch &value, Latch &r_w){
            Memory::address.connection = &address;
            Memory::write_value.connection = &value;
            Memory::r_w.connection = &r_w;
        }

        //Read
        void read_from_memory (Latch &address, Latch &read_value, Latch &r_w){
            Memory::address.connection = &address;
            Memory::r_w.connection = &r_w;
            Memory::read_value = &read_value;
        }

        //receive clock
        void receive_clock(){
            if(r_w.connection->after == 0){  //read
                if(storage.count(address.connection->after) > 0){
                    read_value->before = storage[address.connection->after];
                    //return storage[address.connection->after];
                    //std::cout << "Read: The value "<< std::hex << read_value->before << " is on 0x "<< std::hex << address.connection->after <<std::endl;
                    
                }else{
                    std::cout << "No value stored for this address"<< std::endl;
                }
            }else{     //write
                storage.insert(std::pair<int64_t, int64_t>(address.connection->after, write_value.connection->after));
                std::cout << "Write: The value "<< std::hex << storage[address.connection->after] << " is inserted on 0x"<< std::hex << address.connection->after <<std::endl;
            }
            //return null;
        }
    private:
        Port address; //address to write
        Port write_value; //input of write
        Port r_w; //read or write (0 for read, 1 for write)
        Latch *read_value; //output of read

};


int main(){
    Memory memory;
    Latch address_w, address_r, write_value, r_w, read_value;
    
    /*Write testing*/
    address_w.before  = 0x1000;  //64-bit
    r_w.before = 0x1; //write
    write_value.before = 0x5000;

    memory.write_to_memory(address_w, write_value, r_w);

    //send clock
    address_w.receive_clock(); r_w.receive_clock(); write_value.receive_clock(); memory.receive_clock();


    /*Read testing*/
    /* The value wrote*/

    //initialization
    address_r.before  = 0x1000;  //64-bit
    r_w.before = 0x0; //read
    
    memory.read_from_memory(address_r, read_value, r_w);
    
    //send clock
    address_r.receive_clock(); r_w.receive_clock(); memory.receive_clock();

    //result
    std::cout << "Read: The value "<< std::hex << read_value.before << " is on 0x "<< std::hex << address_r.after <<std::endl;

    /*The value already existed*/
    address_r.before  = 0x0000000011111111;  //64-bit
    r_w.before = 0x0; //read
    
    memory.read_from_memory(address_r, read_value, r_w);
    
    //send clock
    address_r.receive_clock(); r_w.receive_clock(); memory.receive_clock();

    //result
    std::cout << "Read: The value "<< std::hex << read_value.before << " is on 0x "<< std::hex << address_r.after <<std::endl;


} 