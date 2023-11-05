#ifndef ALU_H
#define ALU_H
#include "Register.h"

class ALU
{
    public:
        ALU();
        virtual ~ALU();
        // operation is multi bit value here
        int operation(int operand1, int operand2, bool& ZF, bool& CF, int signal);

};

#endif // ALU_H
