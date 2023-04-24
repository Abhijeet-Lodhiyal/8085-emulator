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

void STA(map <int , int>&memory,map <string,int>&registers,string loca,set <int>&changed)
{
    int address = convert(loca);
    memory[address] = registers["A"];
    changed.insert(address);
}

void LDA(map <int , int>&memory,map <string,int>&registers,string loca,set <int>&changed)
{
    int address = convert(loca);
    changed.insert(address);
    registers["A"] = memory[address];
}

void LXI(map <string,int>&registers,string &higherOrder,string &lowerOrder,string value)
{
    string s = "";
    s = value.substr(0,2);
    registers[higherOrder] = convert(s);           // assigning the value to lower order register
    s = "";
    s = value.substr(2,2);
    registers[lowerOrder] = convert(s);       // assigning the value to higher order register
}

void LHLD(map <int,int> &memory,map <string,int>&registers,string value,set <int> &changed)
{
    int address = convert(value);
    changed.insert(address);
    registers["L"] =  memory[address];
    address++;
    registers["H"] = memory[address];
}

void SHLD(map <int,int> &memory,map <string,int>&registers,string value,set <int> &changed)
{
    int address = convert(value);
    changed.insert(address);
    memory[address] = registers["L"] ;
    address++;
    memory[address] = registers["H"] ;
}
void XCHG(map <string,int> &registers)
{
    int temp = registers["H"];
    registers["H"] = registers["D"];
    registers["D"] = temp;
    temp = registers["L"];
    registers["L"] = registers["E"];
    registers["E"] = temp;
}

void LDAX(map <int,int>&memory,map <string,int> &registers, string& rp1,string& rp2,set <int>&changed)
{
    string address = intToHex(registers[rp1],2)  + intToHex(registers[rp2],2);
    int address1 = convert(address);
    changed.insert(address1);
    registers["A"] = memory[convert(address)];
}
void STAX(map <int,int>&memory ,map <string,int> &registers ,string& rp1,string& rp2,set <int>&changed)
{
    string address = intToHex(registers[rp1],2)  + intToHex(registers[rp2],2);   // fetch address of memory
    int address1 = convert(address);
    changed.insert(address1);
    memory[address1] = registers["A"];
}

#endif