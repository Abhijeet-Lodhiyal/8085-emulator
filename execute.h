#include <map>
#include <vector>
#include <string>
#include "loadAndStore.h"
#include "arithmetic.h"
#include "logical.h"
#include "utility.h"
#include "branch.h"
using namespace std;

void execute(map<string, string> &memory, map<string, string> &registers, vector<bool> &flagReg, vector<pair<string,string>> &code)
{
    for (int i = 0 ; i < code.size();i++)
    {
        string instructions = code[i].second;
        stringstream ss(instructions);
        string opcode;
        getline(ss, opcode, ' '); // for opcode
        if (opcode == "ADD")
        {
            getline(ss, opcode, ' '); // for values after opcode
            if (registers.find(opcode) != registers.end())
                ADD(registers, opcode, flagReg);
            else
            {
                cout << "Invalid location at location " << endl;
                exit(0);
            }
        }
        else if (opcode == "ADI")
        {
            getline(ss, opcode, ' ');
            if (!validCode(opcode, 2))
            {
                cout << "Data is not valid" << endl;
                exit(0);
            }
            ADI(registers, opcode, flagReg);
        }
        else if (opcode == "SUB")
        {
            getline(ss, opcode, ' ');
            if (registers.find(opcode) != registers.end())
                SUB(registers, opcode, flagReg);
            else
            {
                cout << "Invalid location at location " << endl;
                exit(0);
            }
        }
        else if (opcode == "SUI")
        {
            getline(ss, opcode, ' ');
            if (!validCode(opcode, 2))
            {
                cout << "Data is not valid" << endl;
                exit(0);
            }
            SUI(registers, opcode, flagReg);
        }
        else if (opcode == "INR")
        {
            getline(ss, opcode, ' ');
            if (registers.find(opcode) != registers.end())
            {
                INR(registers, opcode, flagReg);
            }
            else
            {
                cout << "Invalid register" << endl;
                exit(0);
            }
        }
        else if (opcode == "DCR")
        {
            getline(ss, opcode, ' ');
            if (registers.find(opcode) != registers.end())
            {
                DCR(registers, opcode, flagReg);
            }
            else
            {
                cout << "Invalid register" << endl;
                exit(0);
            }
        }
        else if (opcode == "INX")
        {
            getline(ss, opcode, ' ');
            string nextReg = "";
            if (registers.find(opcode) != registers.end())
            {
                if (opcode == "B")
                    nextReg = "C";
                else if (opcode == "D")
                    nextReg = "E";
                else if (opcode == "H")
                    nextReg = "L";
                else
                {
                    cout << "Invalid register" << endl;
                    exit(0);
                }
                INX(registers, opcode, nextReg, flagReg);
            }
        }
        else if (opcode == "DCX")
        {
            getline(ss, opcode, ' ');
            string nextReg = "";
            if (registers.find(opcode) != registers.end())
            {
                if (opcode == "B")
                    nextReg = "C";
                else if (opcode == "D")
                    nextReg = "E";
                else if (opcode == "H")
                    nextReg = "L";
                else
                {
                    cout << "Invalid register" << endl;
                    exit(0);
                }
                DCX(registers, opcode, nextReg, flagReg);
            }
        }
        else if (opcode == "DAD")
        {
            getline(ss, opcode, ' ');
            string nextReg = "";
            if (registers.find(opcode) != registers.end())
            {
                if (opcode == "B")
                    nextReg = "C";
                else if (opcode == "D")
                    nextReg = "E";
                else if (opcode == "H")
                    nextReg = "L";
                else
                {
                    cout << "Invalid register" << endl;
                    exit(0);
                }
                DAD(registers, opcode, nextReg, flagReg);
            }
        }
        else if (opcode == "MOV")
        {
            getline(ss, opcode, ',');
            if (registers.find(opcode) != registers.end())
            {
                string temp = "";
                getline(ss, temp, ',');
                if (registers.find(temp) != registers.end())
                {
                    cout << "called" << endl;
                    MOV(registers, opcode, temp);
                }
                else
                {
                    exit(0);
                    cout << "Wrong input" << endl;
                }
            }
            else
            {
                cout << "Wrong input" << endl;
                exit(0);
            }
        }
        else if (opcode == "MVI")
        {
            getline(ss, opcode, ' ');
            if (registers.find(opcode) != registers.end())
            {
                string temp = "";
                getline(ss, temp, ' ');
                if (validCode(temp, 2))
                {
                    cout << "called" << endl;
                    MVI(registers, opcode, temp);
                }
                else
                {
                    cout << "Wrong input" << endl;
                    exit(0);
                }
            }
            else
            {
                cout << "Wrong input" << endl;
                exit(0);
            }
        }
        else if (opcode == "STA")
        {
            getline(ss, opcode, ' ');
            if (validCode(opcode, 4))
            {
                STA(memory, registers, opcode);
                cout << memory[opcode] << endl;
            }
            else
            {
                cout << "Invalid data" << endl;
                exit(0);
            }
        }
        else if (opcode == "LXI")
        {
            getline(ss, opcode, ' ');
            string nextReg = "";
            if (registers.find(opcode) != registers.end())
            {
                if (opcode == "B")
                    nextReg = "C";
                else if (opcode == "D")
                    nextReg = "E";
                else if (opcode == "H")
                    nextReg = "L";
                else
                {
                    cout << "Invalid register" << endl;
                    exit(0);
                }
                string data = "";
                getline(ss, data, ' ');
                if (validCode(data, 4))
                {
                    LXI(registers,opcode,nextReg,data);
                }
                else
                {
                    cout << "Invalid data" << endl;
                    exit(0);
                }
            }
            else
            {
                cout << "Invalid data" << endl;
                exit(0);
            }
        }
        else if(opcode == "LHLD")
        {
            getline(ss, opcode, ' ');
            if(validCode(opcode,4))
            {
                LHLD(memory,registers,opcode);
            }
            else
            {
                cout<<"Invalid data"<<endl;
                exit(0);
            }
        }
        else if(opcode == "SET")
        {
            getline(ss,opcode,' ');
            if(validCode(opcode,4))
            {
                string temp = "";
                getline(ss,temp,' ');
                if(validCode(temp,2))
                {
                    SET(memory,opcode,temp);
                }
                else
                {
                cout<<"No Valid data"<<endl;
                exit(0);
                }
            }
            else
            {
                cout<<"No Valid address"<<endl;
                exit(0);
            }
        }
        else if(opcode == "XCHG")
        {
            XCHG(registers);        
        }
        else if(opcode == "LDAX")
        {
            getline(ss, opcode, ' ');
            string nextReg = "";
            if (registers.find(opcode) != registers.end())
            {
                if (opcode == "B")
                    nextReg = "C";
                else if (opcode == "D")
                    nextReg = "E";
                else if (opcode == "H")
                    nextReg = "L";
                else
                {
                    cout << "Invalid register" << endl;
                    exit(0);
                }
                LDAX(memory,registers,opcode, nextReg);
            }
        }
        else if(opcode == "STAX")
        {
            getline(ss, opcode, ' ');
            string nextReg = "";
            if (registers.find(opcode) != registers.end())
            {
                if (opcode == "B")
                    nextReg = "C";
                else if (opcode == "D")
                    nextReg = "E";
                else if (opcode == "H")
                    nextReg = "L";
                else
                {
                    cout << "Invalid register" << endl;
                    exit(0);
                }
                STAX(memory,registers,opcode, nextReg);
            }
        }
        else if(opcode == "CMA")
        {
            CMA(registers);
        }
        else if(opcode == "CMP")
        {
            getline(ss, opcode, ' ');
            if (registers.find(opcode) != registers.end())
            {
                CMP(registers,opcode,flagReg);
            }
            else
            {
                cout<<"INVALID REGISTER"<<endl;
                exit(0);
            }
        }
        else if(opcode == "JMP")
        {
            getline(ss,opcode,' ');
            if(validCode(opcode,4))
            {
                i = JMP(code,opcode);
                if(i == -1)
                {
                    cout<<"You cannot jump there"<<endl;
                    exit(0);
                }
            }   
        }
        else if(opcode == "JC")
        {
            getline(ss,opcode,' ');
            if(validCode(opcode,4))
            {
                int v = JC(code,opcode,flagReg);
                if(v != 0)
                {
                    if(v != -1)
                        i = v;
                    else
                    {
                        cout<<"You cannot jump there"<<endl;
                        exit(0);
                    } 
                }
            }   
        }
        else if(opcode == "JNC")
        {
            getline(ss,opcode,' ');
            if(validCode(opcode,4))
            {
                int v = JNC(code,opcode,flagReg);
                if(v != 0)
                {
                    if(v != -1)
                        i = v;
                    else
                    {
                        cout<<"You cannot jump there"<<endl;
                        exit(0);
                    } 
                }
            }   
        }
        else if(opcode == "JZ")
        {
            getline(ss,opcode,' ');
            if(validCode(opcode,4))
            {
                int v = JZ(code,opcode,flagReg);
                if(v != 0)
                {
                    if(v != -1)
                        i = v;
                    else
                    {
                        cout<<"You cannot jump there"<<endl;
                        exit(0);
                    } 
                }
            }   
        }
        else if(opcode == "JNZ")
        {
            getline(ss,opcode,' ');
            if(validCode(opcode,4))
            {
                int v = JNZ(code,opcode,flagReg);
                if(v != 0)
                {
                    if(v != -1)
                        i = v;
                    else
                    {
                        cout<<"You cannot jump there"<<endl;
                        exit(0);
                    } 
                }
            }   
        }
    }
}