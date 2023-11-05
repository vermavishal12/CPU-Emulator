#ifndef CPU_H
#define CPU_H
#include "Register.h"
#include "ALU.h"
#include "CU.h"
#include "RAM.h"

class CPU
{
    public:
        CPU(int& dataBus, int& addressBus);
        virtual ~CPU();
        void Run(RAM &ram, bool step_mode);
        void print();

    private:
        // it's register set
        Register PC, DR, AR, AC, IR; // add more registers

        // it's flags
        bool ZF, CF, MF;

        // it's ALU
        ALU alu;

        // it's CU
        CU cu;

        // it's bus
        int &dataBus, &addressBus;
};

#endif // CPU_H
