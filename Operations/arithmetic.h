#include "../utility.h"
#ifndef ARITH
#define ARITH
void ADD(map <string,int>& registers, string name,vector <bool>&flag) {
    int a = registers["A"];
    a += registers[name];
    checkParityAndFlags(a,flag);      // check flags
    if(a > 255)
    {
        a = a % 256;
    }
    registers["A"] = a;
}
void ADI(map <string,int>&registers,string value ,vector <bool>&flag)
{
    int a = registers["A"];
    a += convert(value); 
    checkParityAndFlags(a,flag);
    if(a > 255)
    {
        a = a % 256;
    }
    registers["A"] = a;
}

void SUB( map <string,int>&registers,string &regist ,vector <bool>&flag)
{
    int a = registers["A"];
    a -= registers[regist];
    checkParityAndFlags(a,flag);
    registers["A"] = a;
}
void SUI(map <string,int>&registers, string value ,vector <bool>& flag)
{
    int a = registers["A"];
    a -= convert(value);
    checkParityAndFlags(a,flag);
    registers["A"]  = a;
}

void INR( map <string,int>&registers,string &location ,vector <bool>&flag)
{
    int temp = registers[location];
    temp++;
    if(temp > 255)
    {
        registers[location] = 0;
    }
    else
    {
        registers[location] = temp;
    }
    checkParityAndFlags(temp,flag);
}

void DCR( map <string,int>&registers, string &locat ,vector <bool>& flag)
{
    int temp = registers[locat];
    temp--;
    checkParityAndFlags(temp,flag);
    registers[locat] = temp;
}

void INX( map <string,int>&registers , string &higherOrder,string& lowerOrder ,vector <bool>& flag)
{
    int temp = registers[lowerOrder];
    temp++;
    checkParityAndFlags(temp,flag);
    if(temp > 255)
    {
        registers[lowerOrder] = 0;
        int temp2 = registers[higherOrder];
        temp2++;
        checkParityAndFlags(temp2,flag);
        registers[higherOrder] = temp2;
    } 
    else
        registers[lowerOrder] = temp;
    
}
void DCX( map <string,int>&registers , string &higherOrder ,string& lowerOrder ,vector <bool>& flag)
{
    int temp = registers[lowerOrder];
    temp--;
    checkParityAndFlags(temp,flag);
    if(temp < 0)
    {
        flag[4] = true;
        flag[0] = true;
        registers[lowerOrder] = 0xff;
        int temp2 = registers[higherOrder];
        temp2--;
        checkParityAndFlags(temp2,flag);
        if(temp2 < 0)
            registers[higherOrder] = 0xff;
        else
            registers[higherOrder] = temp2;
    }    
    else
        registers[lowerOrder] = temp;
}

void DAD(map <string,int>&registers , string &higherOrder,string &lowerOrder,vector <bool>& flag)
{
    int n = registers[lowerOrder];
    int n2 = registers["L"] + n;
    string trim = "";
    if(n2 > 255)
    {
        registers["L"] = n2 % 256;
        int hn = registers["H"];
        int hn2 = registers[higherOrder] + hn + n2/256;
        if(hn2 > 255)
        {
            flag[4] = true;
            hn2 = hn2 % 256;
            registers["H"] = hn2;
        }
        else
        {
            flag[4] = false;
            registers["H"] = hn2;
        }
    }
    else
    {   
        registers["L"] = n2,2;
        int hn = registers["H"];
        int hn2 = registers[higherOrder] + hn ;
        if(hn2 > 255)
        {
            hn2 = hn2%256;
            registers["H"] = hn2;
        }
        else
        {
            flag[4] = false;
            registers["H"] = hn2;
        }
    }
    checkParityAndFlags(n2,flag);
}

#endif