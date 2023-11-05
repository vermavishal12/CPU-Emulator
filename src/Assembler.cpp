#include "Assembler.h"
#define deb(X) std::cout << #X << " = " << X << "; "

Assembler::Assembler()
{
    opcode["LDAC"] = 1;
    opcode["STAC"] = 2;
    opcode["ADD"] = 3;
    opcode["SUB"] = 4;
    opcode["AND"] = 5;
    opcode["OR"] = 6;
    opcode["XOR"] = 7;
    opcode["JC"] = 8;
    opcode["JNC"] = 9;
    opcode["JMP"] = 10;
    opcode["JZ"] = 11;
    opcode["JNZ"] = 12;
    opcode["INAC"] = 13;
    opcode["DECAC"] = 14;
    opcode["NOT"] = 15;
    opcode["CLAC"] = 16;
    opcode["SHL"] = 17;
    opcode["SHR"] = 18;
    opcode["CIL"] = 19;
    opcode["CIR"] = 20;
    opcode["ASL"] = 21;
    opcode["ASR"] = 22;
    opcode["HLT"] = 23;
    opcode["NOP"] = 23;

}

Assembler::~Assembler(){}

int Assembler::convertToInstruction(int mode, int opcode, int operand)
{
    int instruction=0;
    // here we will stitch the various parts of instruction into one word
    instruction = (mode<<15) + (opcode << 10) + (operand);

    return instruction;
}

std::string Assembler::format(std::string s)
{
    std::string res;
    bool continuous_space = 1;
    for(char x : s){
        if(x == '\t' || x == ' '){
            if(continuous_space == 0){
                res += ' ';
                continuous_space = 1;
            }
        }
        else if(x == '/' || x == ';'){
            break;
        }
        else{
            res += x;
            continuous_space = 0;
        }
    }
    return res;
}

void Assembler::assemble(RAM& ram, std::string& path){
    //check input code file
    std::ifstream fin(path.c_str());
    std::ifstream fin2(path.c_str());

    if(!fin){
        std::cout << path << ", No such directory exist" << std::endl;
        exit(0);
    }

    //convert input code file to machine code and store it in ram
    std::string s;

    std::cout << "Starting Assembling the Code\n" << std::endl;
    int start = 0;

    // first go to identify variables
    while(std::getline(fin, s)){
        s = format(s);
        if(s == "")continue;

//        std::cout << start << " : " <<  s << std::endl;
        std::stringstream sin(s);

        std::string token, op;
        std::getline(sin, token, ' ');
        std::getline(sin, op, ' ');

        if(isVar(token, op)){
            user_var[token] = start;
        }
        else if(isLoopVar(token, op)){
            loop_var[token] = start;
        }
        start++;
    }

    // second go to assemble the code
    start = 0;
    while(std::getline(fin2, s)){
        std::cout << s << std::endl;
        s = format(s);
        if(s == "")continue;

        std::stringstream sin(s);
        int data;

        std::string token;
        std::getline(sin, token, ' ');

        // it's a Loop indicator like -> label : MVLD y
        if(isLoopVar(token)){
            std::getline(sin, token, ' '); // taking away ":"
            if(token != ":"){
                std::cout << "Syntax error in line : " << s << std::endl << "missing ':' character" << std::endl;
                exit(0);
            }
            std::getline(sin, token, ' ');
        }
        // it's a keyword like -> MVAC x
        if(isKeyword(token)){
            std::string operand;
            std::getline(sin, operand, ' ');
            transform(token.begin(), token.end(), token.begin(), ::toupper);

            if(token == "NOP" || token == "INAC" || token == "DECAC" || token == "NOT" || token == "CLAC" || token == "SHL" || token == "SHR" || token == "CIL" || token == "CIR" || token == "ASL" || token == "ASR" || token == "HLT"){
                data = convertToInstruction(0, opcode[token], 0);
            }
            else if(isVar(operand)){
                std::string mode;
                std::getline(sin, mode, ' ');

                transform(mode.begin(), mode.end(), mode.begin(), ::toupper);

                if(mode == ""){
                    // direct mode
                    data = convertToInstruction(0, opcode[token], user_var[operand]);
                }
                else if(mode == "I"){
                    // indirect mode
                    data = convertToInstruction(1, opcode[token], user_var[operand]);
                }
                else{
                    std::cout << "Syntax error in line : " << s << std::endl << "unexpected mode identifier" << std::endl;
                    exit(0);
                }
            }
            else if(isLoopVar(operand)){
                std::string mode;
                std::getline(sin, mode, ' ');

                transform(token.begin(), token.end(), token.begin(), ::toupper);
                transform(mode.begin(), mode.end(), mode.begin(), ::toupper);

                if(mode == ""){
                    // direct mode
                    data = convertToInstruction(0, opcode[token], loop_var[operand]);
                }
                else if(mode == "I"){
                    // indirect mode
                    data = convertToInstruction(1, opcode[token], loop_var[operand]);
                }
                else{
                    std::cout << "Syntax error in line : " << s << std::endl << "unexpected mode identifier" << std::endl;
                    exit(0);
                }
            }
            else{
                std::cout << "Syntax error in line : " << s << std::endl << "unknown variable" << std::endl;
                exit(0);
            }
        }
        // it's a variable allocation like -> x = 50
        else if(isVar(token)){
            std::string op, value;
            std::getline(sin, op, ' ');
            std::getline(sin, value, ' ');
            if(op != "="){
                std::cout << "Syntax error in line : " << s << std::endl << "missing '=' character" << std::endl;
                exit(0);
            }
            else if(!isNo(value)){
                std::cout << "Syntax error in line : " << s << std::endl << "A integer is expected" << std::endl;
                exit(0);
            }

            data = stoi(value);
        }
        else if(isNo(token)){
            std::string op, value;
            std::getline(sin, op, ' ');
            std::getline(sin, value, ' ');
            if(op != "=" && op != ":"){
                std::cout << "Syntax error in line : " << s << std::endl << "expected '=' or ':' character" << std::endl;
                exit(0);
            }
            else if(!isNo(value)){
                std::cout << "Syntax error in line : " << s << std::endl << "A integer is expected" << std::endl;
                exit(0);
            }

            data = stoi(value);
            int address = stoi(token);
            ram.write(1, data, address);
            continue;
        }
        // it's random thing which means syntax error
        else{
            std::cout << "Syntax error in line : " << s << std::endl << "unexpected token" << std::endl;
            exit(0);
        }

        ram.write(1, data, start);
        start++;
    }

    std::cout << "\nAssembling Done" << std::endl;

}

bool Assembler::isNo(std::string token)
{
    int idx = 0;
    for(char x : token){
        if(idx++ == 0 && (x < '0' || x > '9') && (x == '-' || x == '+')) continue;
        if(x < '0' || x > '9')return false;
    }
    return true;
}

bool Assembler::isKeyword(std::string token)
{
    transform(token.begin(), token.end(), token.begin(), ::toupper);
    return opcode.find(token) != opcode.end();
}

bool Assembler::isVar(std::string token, std::string op)
{
    if(isNo(token)) return false;
    if(isKeyword(token)) return false;

    if(op == "=") return true;
    // it is Loop identifier
    return false;
}

bool Assembler::isVar(std::string token)
{
    return user_var.find(token) != user_var.end();
}

bool Assembler::isLoopVar(std::string token, std::string op)
{
    if(isNo(token)) return false;
    if(isKeyword(token)) return false;

    if(op == "=") return false;
    // it is Loop identifier
    if(op == ":") return true;
}

bool Assembler::isLoopVar(std::string token)
{
    return loop_var.find(token) != loop_var.end();
}

void Assembler::help()
{
    std::string text = "\nYou are welcome in Kochikame Group's Assembly Guide \n\nCommands we provide are as follows : \n\n\tNOP \tstands for no operation\n\nData Transfer Instructions :-)\n\n\tLDAC \tloads data into AC\n\tSTAC \tstore data of AC to memory\n\nALU instructions :-)\n\n\tINAC \tincrement AC data\n\tDECAC \tdecrement AC data\n\tADD \tit adds data provided with AC and stores the result back to AC\n\tSUB \tit subtract data provided from AC and stores the result back to AC\n\tAND, OR,XOR \tworks similarly\n\tNOT \t\tnegates data provided\n\tSHL,SHR \tare left,right shifts\n\tCIL,CIR \tare left and right circular shifts\n\tASL,ASR \tare arithmetic shifts\n\tHLT \t\tmakes processor halt\n\nConditional instructions :-)\n\n\tJZ \tit transfer control to specified address if zero flag is set\n\tJNZ \tit transfer control to specified address if zero flag is not set\n\tJC \tit transfer control to specified address if carry flag is set\n\tJNC \tit transfer control to specified address if carry flag is not set\n\tJMP \tit transfer control to specified address unconditionally\nAll data transfer instructions can be in direct mode and indirect mode as well";
    std::cout << text << std::endl;
    return;
}


