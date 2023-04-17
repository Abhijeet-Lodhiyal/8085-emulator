#include <string>
#include <iostream>
#include <map>
#include"utility.h"
using namespace std;
#ifndef LOAD
#define LOAD

void MOV(map <string,int>&registers ,string destination , string source)
{
    registers[destination] = registers[source];
}
void MVI(map <string,int>&registers ,string &destination , string value )
{
    registers[destination] = convert(value);
}

void STA(map <int , int>&memory,map <string,int>&registers,string loca)
{
    int address = convert(loca);
    memory[address] = registers["A"];
}

void LDA(map <int , int>&memory,map <string,int>&registers,string loca)
{
    int address = convert(loca);
    registers["A"] = memory[address];
}

void LXI(map <string,int>&registers,string &higherOrder,string &lowerOrder,string value)
{
    string s = "";
    s = value.substr(0,2);
    registers[higherOrder] = stoi(s);
    s = "";
    s = value.substr(2,2);
    registers[lowerOrder] = stoi(s);
}

void LHLD(map <int,int> &memory,map <string,int>&registers,string value)
{
    int address = convert(value);
    registers["H"] =  memory[address];
    address++;
    registers["L"] = memory[address];
}
void SHLD(map <string,string> &memory,map <string,string>&registers,string value)
{
    memory[value] = registers["H"] ;
    int incValue = hexToInt(value) + 1;
    string nextVal = intToHex(incValue,4);
    memory[nextVal] = registers["L"] ;
}
void XCHG(map <string,string> &registers)
{
    string temp = registers["H"];
    registers["H"] = registers["D"];
    registers["D"] = temp;
    temp = registers["L"];
    registers["L"] = registers["E"];
    registers["E"] = temp;
}

void LDAX(map <string,string>&memory,map <string,string> &registers, string& rp1,string& rp2)
{
    registers["A"] = memory[registers[rp1]+registers[rp2]];
}
void STAX(map <string,string>&memory ,map <string,string> &registers ,string& rp1,string& rp2)
{
    memory[registers[rp1]+registers[rp2]] = registers["A"];
}

#endif