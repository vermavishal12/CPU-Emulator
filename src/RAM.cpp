#include "RAM.h"
#define deb(X) std::cout << #X << " = " << X << "; "

RAM::RAM()
{
    int n = 1024; // change it
    size = n;
    mem.resize(n);
}

RAM::~RAM()
{
    //dtor
}

void RAM::read(bool signal, int& data, int& address)
{
    if(signal)data = mem[address];
}

void RAM::write(bool signal, int& data, int& address)
{
    if(signal)mem[address] = data;
}

void RAM::show()
{
    std::cout << "Showing Contents of RAM for first 20 cells" << std::endl;
    for(int i=0;i<20;i++){
        std::cout << "Location " << i << "\t: " << std::bitset<16>(mem[i]) << std::endl;
    }
    std::cout << "END" << std::endl;
}
