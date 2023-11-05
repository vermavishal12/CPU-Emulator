#include "Computer.h"
#include <bits/stdc++.h>
#include <unistd.h>
#define deb(X) std::cout << #X << " = " << X << "; "

Computer::Computer() : cpu(dataBus, addressBus)
{
    dataBus = addressBus = 0;
}

Computer::~Computer(){}

void Computer::loadProgram(std::string& path)
{
//    assembler.help();std::cout << std::endl;
    assembler.assemble(ram, path);
}

void Computer::execute()
{
//    ram.show();
    bool step_mode = 0;
    while(true){
        std::cout << "Wanna Run in Stepping Mode (1:YES, 0:NO) : " << std::endl;
        std::string s; std::cin >> s;
        if(s == "1"){
            step_mode = 1;
            break;
        }
        else if(s == "0"){
            step_mode = 0;
            break;
        }
    }
    unsigned del = 100000;

    int counter = 0;
    while(true){
        cpu.Run(ram, step_mode);

        if(counter++  > 10000)break;
    }
}
