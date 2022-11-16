long long Latch::receive_clock() { 
    after = before; 
    return after;
}