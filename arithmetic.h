#include <string>
#include "utility.h"

using namespace std;
#ifndef ARITH
#define ARITH
void ADD(map <string,string>& registers, string name,vector <bool>&flag) {
    int a = hexToInt(registers["A"]);
    a += hexToInt(registers[name]);
    if(a > 255)
    {
        flag[4] = true;
        a = a % 256;
    }
    else 
        flag[4] = false;
        registers["A"] = intToHex(a,2);
}
void ADI(map <string,string>&registers,string value ,vector <bool>&flag)
{
    int a = hexToInt(registers["A"]);
    a += hexToInt(value); 
    if(a > 255)
    {
        flag[4] = true;
        a = a % 256;
    }
    else 
        flag[4] = false;
    registers["A"] = intToHex(a,2);
}

void SUB( map <string,string>&registers,string &regist ,vector <bool>&flag)
{
    int a = hexToInt(registers["A"]);
    a -= hexToInt(registers[regist]);
    if(a < 0)
    {
        flag[0] = true;
        flag[4] = true;
        registers["A"] = twoscomplement(a);
    }
    else
    {
        flag[0] = false;
        flag[4] = false;
        registers["A"] = intToHex(a,2);
    }
}
void SUI(map <string,string>&registers, string value ,vector <bool>& flag)
{
    int a = hexToInt(registers["A"]);
    a -= hexToInt(value);
    if(a < 0)
    {
        flag[0] = true;
        flag[4] = true;
        registers["A"]  = twoscomplement(a);
    }
    else
    {
        flag[0] = false;
        flag[4] = false;
        registers["A"]  = intToHex(a,2);
    }
}

void INR( map <string,string>&registers,string &location ,vector <bool>&flag)
{
    int temp = hexToInt(registers[location]);
    temp++;
    if(temp > 255)
    {
        flag[4] = true;
        registers[location] = "00";
    }
    else
    {
        flag[4] = false;
        registers[location] = intToHex(temp,2);
    }
}

void DCR( map <string,string>&registers, string &locat ,vector <bool>& flag)
{
    int temp = hexToInt(registers[locat]);
    temp--;
    if(temp < 0)
    {
        flag[0] = true;
        registers[locat] = twoscomplement(temp);
    }
    else
    {
        flag[0] = false;
        registers[locat] = intToHex(temp,2);
    }
}

void INX( map <string,string>&registers , string &higherOrder,string& lowerOrder ,vector <bool>& flag)
{
    int temp = hexToInt(registers[lowerOrder]);
    temp++;
    if(temp > 255)
    {
        flag[4] = true;
        registers[lowerOrder] = "00";
        int temp2 = hexToInt(registers[higherOrder]);
        temp2++;
        registers[higherOrder] = intToHex(temp2,2);
    } 
    else
        registers[lowerOrder] = intToHex(temp,2);
}
void DCX( map <string,string>&registers , string &higherOrder ,string& lowerOrder ,vector <bool>& flag)
{
    int temp = hexToInt(registers[lowerOrder]);
    temp--;
    if(temp < 0)
    {
        flag[4] = true;
        flag[0] = true;
        registers[lowerOrder] = "FF";
        int temp2 = hexToInt(registers[higherOrder]);
        temp2--;
        if(temp2 < 0)
            registers[higherOrder] = "FF";
        else
            registers[higherOrder] = intToHex(temp2,2);
    }    
    else
        registers[lowerOrder] = intToHex(temp,2);
}

void DAD(map <string,string>&registers , string &higherOrder,string &lowerOrder,vector <bool>& flag)
{
    int n = hexToInt(registers[lowerOrder]);
    int n2 = hexToInt(registers["L"]) + n;
    string trim = "";
    if(n2 > 255)
    {
        trim = intToHex(n2,2);
        cout<<trim<<endl;
        registers["L"] = trim.substr(1);
        int hn = hexToInt(registers["H"]);
        int hn2 = hexToInt(registers[higherOrder]) + hn + 1;
        if(hn2 > 255)
        {
            flag[4] = true;
            trim = intToHex(hn2,2);
            registers["H"] = trim.substr(1);
        }
        else
        {
            flag[4] = false;
            registers["H"] = intToHex(hn2,2);
        }
    }
    else
    {   
        registers["L"] = intToHex(n2,2);
        int hn = hexToInt(registers["H"]);
        int hn2 = hexToInt(registers[higherOrder]) + hn ;
        if(hn2 > 255)
        {
            flag[4] = true;
            trim = intToHex(n2,2);
            registers["H"] = trim.substr(1);
        }
        else
        {
            flag[4] = false;
            registers["H"] = intToHex(hn2,2);
        }
    }
}

#endif