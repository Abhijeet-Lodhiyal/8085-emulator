#include <cmath>
#include <string>
#include <vector>
using namespace std;
#ifndef UTIL
#define UTIL
string intToHex(int n, int size)           // convert an integer value to hexadecimal string
{
    string value = "";
    do
    {
        if (n % 16 < 10)
            value += to_string(n % 16);
        else
            value += char(n % 16 + 87);
        n = n / 16;
    } while (n > 0);
    while (value.length() < size)
    {
        value += '0';
    }
    reverse(value.begin(), value.end());
    return value;
}

void checkParityAndFlags(int number, vector<bool> &flag)        // check for even parity and other falgs
{
    int count = 0, num = number;
    while (num > 0)
    {
        if (num % 2 == 1)
        {
            count++;
        }
        num = num / 2;
    }
    if (count % 2 == 0)
    {
        flag[3] = 1;
    }
    else
    {
        flag[3] = 0;
    }
    if (number > 255 || number < 0)
    {
        flag[4] = 1;
        flag[0] = 1;
    }
    else
    {
        flag[0] = 0;
        flag[4] = 0;
    }
    if (number == 0)
    {
        flag[1] = 1;
    }
    else
    {
        flag[1] = 0;
    }
}

int convert(string value)                  // convert string to int
{
    int sum = 0;
    int count = 0;
    for (int i = value.length() - 1; i >= 0; i--)
    {
        if (value[i] == 'a' || value[i] == 'b' || value[i] == 'c' || value[i] == 'd' || value[i] == 'e' || value[i] == 'f')
        {
            sum = sum + (int)pow(16, count) * (value[i] - 87);
        }
        else
        {
            sum = sum + (int)pow(16, count) * (value[i] - 48);
        }
        count++;
    }
    return sum;
}

bool validCode(string &dataValue, int length)               // check if a value is a valid hexadecimal number
{
    if (dataValue.length() > length || dataValue.length() < length)
    {
        return false;
    }
    int f = 0;
    for (int i = 0; i < dataValue.length(); i++)
    {
        if ((dataValue[i] >= 48 && dataValue[i] <= 57) || (dataValue[i] >= 97 && dataValue[i] <= 122))
        {
            continue;
        }
        else
        {
            f = 1;
            break;
        }
    }
    if (f == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void SET(map<int, int> &memory, string locat, string value, set<int> &changed)  // set a memory location to a value
{
    int address = convert(locat);
    memory[address] = convert(value);
    changed.insert(address);
}

int getBYTES(string code)             // get opcode bytes
{
    map<string, int> opcodeBytes;
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
    if (opcodeBytes.find(code) != opcodeBytes.end())
        return opcodeBytes[code];
    else
        return -2;
}

void inputUser(string &start,int &startVal,vector <pair<int,string>>&code)  // get input from user
{
    cout << "Enter starting address " << endl;
        cin >> start;
        if (!validCode(start, 4))
        {
            cout << "Invalid start address" << endl;
            exit(0);
        }
        else
        {
            startVal = convert(start);
        }
        string input;
        cout << "Enter code , ctrl + z to exit" << endl;
        cin.ignore();
        while (true)
        {
            cout << hex << startVal << " : ";
            if (!getline(cin, input))
                break;
            stringstream ss(input);
            string temp = "";
            code.push_back({startVal, input});
            getline(ss, temp, ' ');
            if (getBYTES(temp) == 0 && temp != "")
            {
                cout << "INVALID SYNTAX" << endl;
                exit(0);
            }
            if(getBYTES(temp) != -2)
                startVal = startVal + getBYTES(temp);
            else
                {
                    cout<<"Wrong statement"<<endl;
                    exit(0);
                }
        }
}

void inputFile(string &file,string &start,int &startVal,vector<pair<int,string>>&code)  // get input from file
{
    cout << "Enter file location" << endl;
        cin >> file;
        ifstream fromFile(file);
        if (!fromFile.is_open())
        {
            cout << "File not found" << endl;
            exit(0);
        }
        getline(fromFile,start);
        if (!validCode(start, 4))
        {
            cout << "Invalid start address" << endl;
            exit(0);
        }
        else
        {
            startVal = convert(start);
            cout << startVal << endl;
            cout << hex << startVal << endl;
        }
        string input;
        while (getline(fromFile, input))
        {
            stringstream ss(input);
            string temp = "";
            code.push_back({startVal, input});
            getline(ss, temp, ' ');
            if (getBYTES(temp) == 0 && temp != "")
            {
                cout << "INVALID SYNTAX" << endl;
                exit(0);
            }
            if(getBYTES(temp) != -2)
                startVal = startVal + getBYTES(temp);
            else
                {
                    cout<<"Wrong statement"<<endl;
                    exit(0);
                }
        }
}

void printMemory(map <string,int>&registersVal,map <int,int>&memory ,vector<bool>&flagReg,set <int>& changed)           // print memory
{
    cout<<"Value of registers"<<endl;
    for (auto i : registersVal)
    {
        cout << i.first << " " << hex << setw(2) << i.second << endl;
    }
    cout<<"Value of flags"<<endl;
    cout << flagReg[0] << " " << flagReg[1] << " " << flagReg[2] << " " << flagReg[3] << " " << flagReg[4] << " " << endl;
    cout<<"Value of memory changed"<<endl;
    for(auto i : changed)
    {
        cout<<"AT " << hex << i <<" , value is "<< memory[i]<<" "<<endl;
    }
}


void debugExecution(string &command,map <string,int>&registers,int &step,vector <int>&breakpoints ,map <int,int>&memory,vector <pair <int,string>>&code,int line = 0)
{
    cout << "Debugger mode on , type h or help to show all commands" << endl;
        while (true)
        {
            getline(cin, command);
            stringstream sc(command); // to read and split input into different parts
            string dbcode = "";
            getline(sc, dbcode, ' ');
            if (dbcode == "p" || dbcode == "print")
            {
                getline(sc, dbcode, ' ');
                if (registers.find(dbcode) != registers.end()) // if value is a register
                {
                    cout << "Value at " << dbcode << " : " << registers[dbcode] << endl;
                }
                else if (validCode(dbcode, 4))
                {
                    cout << "Value at memory location : " << memory[convert(dbcode)] << endl;
                }
            }
            else if (dbcode == "e" || dbcode == "exit") // exit debugger mode
            {
                breakpoints.clear();
                step = 0;
                break;
            }
            else if (dbcode == "step" || dbcode == "s") // run step by step
            {
                step = 1;
                break;
            }
            else if (dbcode == "run" || dbcode == "r") // run the program upto breakpoint
            {
                break;
            }
            else if (dbcode == "help" || dbcode == "h") // show commands
            {
                cout << "type e to exit debug mode and continue the regular execution of the program" << endl;
                cout << "type p or print along with register name or memory location to print value of a register or memory location " << endl;
                cout << "type s or step to run the code step by step " << endl;
                cout << "type r or run till end of code or breakpoint " << endl;
                cout << "type b or break along with line number to set a break point on the given line " << endl;
            }
            else if (dbcode == "b" || dbcode == "break") // set breakpoint
            {
                getline(sc, dbcode, ' ');
                int t = stoi(dbcode);
                if (t > code.size() || t <= line)
                        {
                            cout << "Invalid line range , currently at line "<< line + 1 << endl;
                            continue;
                        }
                breakpoints.push_back(t - 1);
            }
        }
}

#endif