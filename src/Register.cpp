#include "Register.h"
#include <iostream>
Register::Register()
{
    data = 0;
}

Register::~Register(){}

void Register::increase(bool signal)
{
    if(signal) data++;
}

void Register::load(int dataBus, bool signal)
{
    if(signal) data = dataBus;
}

void Register::output(int& dataBus, bool signal)
{
    if(signal) dataBus = data;
}

int Register::getData()
{
    return data;
}
