#ifndef DEVICE_H
#define DEVICE_H

class Device {
public:
//For declaration in .h file, there should be no virtual in front of the function
	virtual void do_function();
    virtual void receive_clock();
};

#endif