#ifndef COMPUTER_H
#define COMPUTER_H
#include "RAM.h"
#include "CPU.h"
#include "Assembler.h"
#include "CU.h"

class Computer
{
    public:
        Computer();
        virtual ~Computer();

        void loadProgram(std::string& path);

        void execute();

    private:
        int dataBus, addressBus;
        RAM ram;
        CPU cpu;
        Assembler assembler;
};

#endif // COMPUTER_H
