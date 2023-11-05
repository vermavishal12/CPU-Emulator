#ifndef RAM_H
#define RAM_H
#include <vector>
#include <iostream>
#include <bitset>

class RAM
{
    public:
        RAM();
        virtual ~RAM();
        void read(bool signal, int& data, int& address);
        void write(bool signal, int& data, int& address);
        void show();

    private:
        std::vector<int> mem;   //memory
        int size;               //memory size
};

#endif // RAM_H

