#include <iostream>
#include "Latch.h"
#include "Port.h"
#include "Device.h"
#include "Memory.h"
#include <limits>

extern unsigned storage[SIZE];

//assume only use the last 16 bits for address
class MemoryData : public Device{
    public:
        //Constructer
        MemoryData (Latch &address, Latch &write_value, Latch &read_value, Latch &r_w){
            MemoryData::address.connection = &address;
            MemoryData::write_value.connection = &write_value;
            MemoryData::r_w.connection = &r_w;
            MemoryData::read_value = &read_value;
            std::cout<< "Memory Data is initailized"<< std::endl;
        }

        void do_function(){
            if(r_w.connection->after == 0){  //read
                std::cout << "Offset address is" << address.connection->after << std::endl;
                std::cout << "storage" << &storage << std::endl;
                std::memcpy(&result, &(storage[address.connection->after]), sizeof(int64_t));
                //result = static_cast <long long> (storage[address.connection->after]);

            }else{      //write
                result = std::numeric_limits<int64_t>::max(); //infinite impedance
                std::memcpy(&(storage[address.connection->after]), &write_value.connection->after, sizeof(int64_t));
                std::cout << "Write: The value "<< std::hex << write_value.connection->after << " is inserted on 0x"<< std::hex << address.connection->after <<std::endl;
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
        long long result;
};


int main(){

    
    Latch address, write_value, read_value, r_w;
    MemoryData memory(address, write_value, read_value, r_w);
    
    /*Write testing*/
    address.before  = 0x0000;  //16-bit
    r_w.before = 0x1; //write
    write_value.before = 0x5000;
    //send clock to latches
    address.receive_clock(); r_w.receive_clock(); write_value.receive_clock(); 
    //propogate data through device
    memory.do_function();
    memory.receive_clock();


    /*Read testing*/

    /* The address has been stored already*/
    //initialization
    address.before  = 0;  //64-bit
    r_w.before = 0; //read
    //send clock to latches
    address.receive_clock(); r_w.receive_clock(); 
    //propagate data through device
    memory.do_function();
    memory.receive_clock();
    //result
    std::cout << "Read: The value "<< std::hex << read_value.before << " is on 0x"<< std::hex << address.after <<std::endl;


} 