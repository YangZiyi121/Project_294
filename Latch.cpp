#include <iostream>
using namespace std;
class Latch
{
    public:
        long long before;
        long long after;
        long long receive_clock() { 
            after = before; 
            return after;
        };
};
