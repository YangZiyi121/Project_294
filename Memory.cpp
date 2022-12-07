#include <iostream>
#include "Latch.h"
#include "Port.h"
#include "Device.h"
#include <map>

class Memory : public Device{
    public:
        std::map <int64_t, int64_t> storage; // <address, value >
        //Constructer
        Memory(Latch &address, Latch &write_value, Latch &read_value, Latch &r_w){
            //original memory
            //storage.insert(std::pair<int64_t, int64_t>(0x0000000011111111, 0x1111111100000000));
            Memory::address.connection = &address;
            Memory::write_value.connection = &write_value;
            Memory::r_w.connection = &r_w;
            Memory::read_value = &read_value;
            std::cout<< "Memory is initailized"<< std::endl;
        }

        void do_function(){
            if(r_w.connection->after == 0){  //read
                if(storage.count(address.connection->after) > 0){ //the value exits on this address
                    result = storage[address.connection->after];
                }else{      //the value does not exist on this address
                    std::cout << "No value stored for this address"<< std::endl;
                }
            }else{      //write
                storage.insert(std::pair<int64_t, int64_t>(address.connection->after, write_value.connection->after));
                std::cout << "Write: The value "<< std::hex << storage[address.connection->after] << " is inserted on 0x"<< std::hex << address.connection->after <<std::endl;
            }
        }


        //receive clock
        void receive_clock(){
            read_value->before = result;
        }
    private:
        Port address; //address to write
        Port write_value; //input of write
        Port r_w; //read or write (0 for read, 1 for write)
        Latch *read_value; //output of read
        int64_t result;

};


// int main(){
//     Latch address, write_value, read_value, r_w;
//     Memory memory(address, write_value, read_value, r_w);
    
//     /*Write testing*/
//     address.before  = 0x1000;  //64-bit
//     r_w.before = 0x1; //write
//     write_value.before = 0x5000;
//     //send clock to latches
//     address.receive_clock(); r_w.receive_clock(); write_value.receive_clock(); 
//     //propogate data through device
//     memory.do_function();
//     memory.receive_clock();


//     /*Read testing*/

//     /* The address has been stored already*/
//     //initialization
//     address.before  = 0x1000;  //64-bit
//     r_w.before = 0x0; //read
//     //send clock to latches
//     address.receive_clock(); r_w.receive_clock(); 
//     //propagate data through device
//     memory.do_function();
//     memory.receive_clock();
//     //result
//     std::cout << "Read: The value "<< std::hex << read_value.before << " is on 0x "<< std::hex << address.after <<std::endl;


//     /*The address has not stored yet*/
//     address.before  = 0x12345;  //64-bit
//     r_w.before = 0x0; //read
//     //send clock to latches
//     address.receive_clock(); r_w.receive_clock(); 
//     //propagate data through device
//     memory.do_function();
//     memory.receive_clock();
//     //result
//     //std::cout << "Read: The value "<< std::hex << read_value.before << " is on 0x"<< std::hex << address.after <<std::endl;

// } 