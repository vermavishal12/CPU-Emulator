#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include "RAM.h"
#include <bits/stdc++.h>


class Assembler
{
    public:
        Assembler();
        virtual ~Assembler();
        void assemble(RAM& ram, std::string& path);
        int convertToInstruction(int mode, int opcode, int operand);
        bool isNo(std::string token);
        bool isKeyword(std::string token);
        bool isVar(std::string token, std::string op);
        bool isVar(std::string token);
        bool isLoopVar(std::string token, std::string op);
        bool isLoopVar(std::string token);
        void help();
        std::string format(std::string s);
    private:
        // have lookup tables here for reserved keywords
        std::map<std::string, int> opcode, user_var, loop_var;
};

#endif // ASSEMBLER_H
