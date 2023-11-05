#include "CPU.h"
#include <bits/stdc++.h>
#include <bitset>
#define deb(X) std::cout << #X << " = " << X << "; "
#define deb1(X) std::cout << #X << " = " << std::bitset<30>(X) << std::endl

CPU::CPU(int& dataBus, int& addressBus) : dataBus(dataBus), addressBus(addressBus)
{
    ZF = CF = MF = 0;
}

CPU::~CPU(){}

void CPU::print(){
    std::cout << std::endl;

    std::cout << "**********************""**********************" << std::endl;
    std::cout << "**********************""**********************" << std::endl;
    std::cout << "************\tPC : " << PC.getData() << "\t\t************" << std::endl;
    std::cout << "************\tDR : " << DR.getData() << "\t\t************" << std::endl;
    std::cout << "************\tAR : " << AR.getData() << "\t\t************" << std::endl;
    std::cout << "************\tAC : " << AC.getData() << "\t\t************" << std::endl;
    std::cout << "************\tIR : " << IR.getData() << "\t\t************" << std::endl;
    std::cout << "************\tZF : " << ZF << "\t\t************" << std::endl;
    std::cout << "************\tCF : " << CF << "\t\t************" << std::endl;
    std::cout << "************\tMF : " << MF << "\t\t************" << std::endl;
    std::cout << "**********************""**********************" << std::endl;
    std::cout << "**********************""**********************" << std::endl;
    std::cout << std::endl;
}

void CPU::Run(RAM &ram, bool step_mode)
{
    // Printing Status of ALL Registers And Flags
    if(cu.implicit_address == 0 && step_mode)
    {
        print();
        std::cout << "Press Any key to step forward : ";
        getchar();
    }
    else if(cu.PRINT){
        print();
        // Processor is Halted now
        exit(0);
    }

    // generate signals in cu
    cu.next_state(IR, CF, ZF, MF);

    // propagate signals
    bool pcInc = cu.PCINC;
    bool acInc = cu.INC;
    bool acdec = cu.DEC;
    bool acClr = cu.CLR;
    bool pcOut = cu.ARPC;
    bool arOut = 1;
    bool drOut = cu.WRITE || cu.IRDR || cu.ARDR || cu.ACDR || cu.PCDR;
    bool acOut = cu.DRAC;
    bool pcLoad = cu.PCDR;
    bool arLoad = cu.ARPC || cu.ARDR;
    bool drLoad = cu.DRAC || cu.READ;
    bool acLoad = cu.ACDR || cu.ALU;
    bool irLoad = cu.IRDR;
    int opType = cu.ALU;

//    deb(pcInc);
//    deb(acInc);
//    deb(acClr);
//    deb(pcOut);
//    deb(drOut);
//    deb(acOut);std::cout << std::endl;
//    deb(pcLoad);
//    deb(arLoad);
//    deb(drLoad);
//    deb(acLoad);
//    deb(irLoad);
//    deb(opType);std::cout << std::endl;


    // increment data
    PC.increase(pcInc);
    if(acInc)AC.load(alu.operation(AC.getData(), 1, ZF, CF, 1), acInc);
    if(acdec)AC.load(alu.operation(AC.getData(), -1, ZF, CF, 1), acdec);


    // output data
    PC.output(dataBus, pcOut);
    AR.output(addressBus, arOut);
    DR.output(dataBus, drOut);
    AC.output(dataBus, acOut);
    ram.read(cu.READ, dataBus, addressBus);


    // load data
    ram.write(cu.WRITE, dataBus, addressBus);
    PC.load(dataBus%1024, pcLoad);
    AR.load(dataBus%1024, arLoad);
    DR.load(dataBus%65536, drLoad);
    if(acLoad)AC.load(alu.operation(AC.getData(), dataBus%65536, ZF, CF, opType), acLoad);
    if(acClr)AC.load(alu.operation(0, 0, ZF, CF, 1), acClr); // clear
    IR.load(((dataBus&31744)>>10), irLoad);    // extract opcode from bit(10-15) and store it at bit(1-5)



    // setting mode(direct/indirect) flag
    if(irLoad)MF = (bool)(dataBus&(1<<15));

}
