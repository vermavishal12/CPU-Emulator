#ifndef CU_H
#define CU_H
#include <bitset>
#include <string>
#include <vector>
#include "Register.h"

class CU
{
    private:
        std::vector<int> ROM;

    public:
        bool select_mapped_address;   // address got from IR mapping
        int implicit_address;         // address got from ROM
        // signals
        bool READ, WRITE, ARPC, DRM, PCINC, IRDR, ARDR, ACDR, MDR, DRAC, INC, DEC, CLR, PCDR;
        int ALU;
        // signal for Printing status
        bool PRINT;

        // methods
        CU();
        virtual ~CU();

        void next_state(Register& reg, bool CF, bool ZF, bool MF);
        int instruction_map(Register& reg, bool CF, bool ZF, bool MF);

};

#endif // CU_H
