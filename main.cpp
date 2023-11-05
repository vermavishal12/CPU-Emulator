#include "Computer.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    Computer computer;
    string path;
//    if(argv[0] == ""){
        cout << "enter program path : ";
        cin >> path;
//    }
//    if(path == "")cout << "not entered any field, taking default path as input.txt" << endl;
//    if(path == "")path = "input.txt";

    computer.loadProgram(path);
    computer.execute();

    return 0;
}
