#ifndef LATCH_H
#define LATCH_H

class Latch
{
    public:
        long long before;
        long long after;
        long long receive_clock();
};

#endif