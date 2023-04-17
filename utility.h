#include <string>
#include <algorithm>
#include <cmath>
using namespace std;
#ifndef UTIL
#define UTIL
string intToHex(int n , int size)
{
    string value = "";
    do
    {
        if (n % 16 < 10)
            value += to_string(n % 16);
        else
            value += char(n % 16 + 55);
        n = n / 16;
    }while (n > 0);
    while (value.length() < size)
    {
        value += '0';
    }
    reverse(value.begin(), value.end());
    return value;
}

int hexToInt(string n)
{
    int sum = 0;
    int power = 0;
    for(int i=n.length()-1;i>=0;i--)
    {
        if(n[i] >=65 && n[i] <=70  )
            sum += (n[i]-55)*(int)pow(16,power);
        else
            sum += (n[i]-48)*(int)pow(16,power);
        power++;
    }
    return sum;
}

bool validCode(string &dataValue,int length)
{
    if(dataValue.length() > length || dataValue.length() < length)
    {
        return false;
    }
    int f = 0;
    for(int i=0;i<dataValue.length();i++)
    {
        if((dataValue[i] >= 48 && dataValue[i] <= 57) || (dataValue[i] >= 65 && dataValue[i] <= 70))
        {
            continue;
        }
        else 
        {
            f = 1;
            break;
        }
    }
    if(f == 0)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

string twoscomplement(int n)
{
    int val = 255 - abs(n) + 1;
    return intToHex(val,2);
}


void SET(map <string,string>&memory , string location , string value)
{
    memory[location] = value;
}

int getBYTES(string code)
{
    map <string,int> opcodeBytes;
	opcodeBytes["SET"] = 3;
    opcodeBytes["ADD"] = 1;
	opcodeBytes["ADI"] = 2;
	opcodeBytes["SUB"] = 1;
	opcodeBytes["SUI"] = 2;
    opcodeBytes["INR"] = 1;
	opcodeBytes["DCR"] = 1;
	opcodeBytes["INX"] = 1;
	opcodeBytes["DCX"] = 1;
	opcodeBytes["DAD"] = 1;
    opcodeBytes["LDA"] = 3;
	opcodeBytes["MOV"] = 1;
    opcodeBytes["MVI"] = 2;
	opcodeBytes["LHLD"] = 3;
	opcodeBytes["SHLD"] = 3;
	opcodeBytes["LXI"] = 3;
	opcodeBytes["STA"] = 3;
	opcodeBytes["STAX"] = 1;
	opcodeBytes["XCHG"] = 1;
	opcodeBytes["CMA"] = 1;
	opcodeBytes["CMP"] = 1;
	opcodeBytes["JMP"] = 3;
	opcodeBytes["JC"] = 3;
	opcodeBytes["JNC"] = 3;
	opcodeBytes["JZ"] = 3;
	opcodeBytes["JNZ"] = 3;
	opcodeBytes["HLT"] = 1;
    if(opcodeBytes.find(code) != opcodeBytes.end())
        return opcodeBytes[code];
    else 
        return 0;
}

int convert(string value)
{
    int sum = 0;
    int count = 0;
    for(int i=value.length()-1;i>=0;i--)
    {
        if(value[i] == 'a' || value[i] == 'b' || value[i] == 'c' || value[i] == 'd' || value[i] == 'e' || value[i] == 'f' )
        {
            sum += pow(16,count)*(value[i]-87);
        }
        else
        {
            sum += pow(16,count)*(value[i]-48);
        }
        count++;
    }
    return sum;
}

#endif