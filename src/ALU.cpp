#include "ALU.h"
#define deb(X) std::cout << #X << " = " << X << "; "
#include <bits/stdc++.h>
using namespace std;

ALU::ALU(){}

ALU::~ALU(){}

int ALU::operation(int operand1, int operand2, bool& ZF, bool& CF, int signal = 0)
{
    int data = operand2;
    int bitsize = 16;

    switch(signal){
    case 0: // load data directly
        break;
    case 1: // add
            data = operand1 + operand2;
            CF = (data >= (1<<bitsize));
        break;
    case 2: // sub
            data = operand1 - operand2;
            CF = (data < 0);
        break;
    case 3: // and
            data = operand1 & operand2;
        break;
    case 4: // xor
            data = operand1 ^ operand2;
        break;
    case 5: // not
            data = ~operand1;
        break;
    case 6: // or
            data = operand1 | operand2;
        break;
    case 7: // shift right
            data = operand1 >> 1;
        break;
    case 8: // shift left
            data = operand1 << 1;
        break;
    case 9: // circular shift right
            data = (operand1 & 1) << (bitsize - 1);
            data += operand1 >> 1;
        break;
    case 10: // circular shift left
            data = operand1 << 1;
            data += (bool)(operand1 & (1 << bitsize));
        break;
    case 11: // arithmetic shift right
            data = operand1 >> 1;
        break;
    case 12: // arithmetic shift left
            data = operand1 << 1;
        break;
    case 13: // empty
        break;
    case 14: // empty
        break;
    case 15: // empty
        break;
    default:
        break;
    }

    data %= (1 << bitsize);
    ZF = (data == 0);
    return data;
}
