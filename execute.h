#include "loadAndStore.h"
#include "arithmetic.h"
#include "logical.h"
#include "utility.h"
#include "branch.h"
using namespace std;

void execute(map<int, int> &memory, map<string, int> &registers, vector<bool> &flagReg, vector<pair<int, string>> &code, set<int> &changed, int debugger = 0)
{
    int step = 0;            // to run step by step
    vector<int> breakpoints; // to set breakpoints
    string command;
    if (debugger == 1) // if debugger mode is on
    {
        debugExecution(command,registers,step,breakpoints,memory,code);
    }
    for (int i = 0; i < code.size(); i++)
    {
        string instructions = code[i].second; // read an instruction
        stringstream ss(instructions);
        string opcode;
        if (find(breakpoints.begin(), breakpoints.end(), i) != breakpoints.end()) // check if breakpoint is set at that instruction
        {
            int i;
            cout << "At step " << instructions << " " << endl;
            if (debugger == 1)                                // if debugger mode is on
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
                        if (t > code.size() || t <= i)
                        {
                            cout << "Invalid line range , currently at line "<< i + 1 << endl;
                            continue;
                        }
                        breakpoints.push_back(t - 1);
                    }
                }
            }
        }
        else if (step == 1) // run in steps
        {
            int i;
            cout << "At step " << instructions << " " << endl;
            if (debugger == 1)                                // if debugger mode is on
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
                        if (t > code.size() || t <= i)
                        {
                            cout << "Invalid line range , currently at line "<< i + 1 << endl;
                            continue;
                        }
                        breakpoints.push_back(t - 1);
                    }
                }
            }
        }
        getline(ss, opcode, ' '); // for opcode
        if (opcode == "ADD")
        {
            getline(ss, opcode, ' '); // for values after opcode
            if (registers.find(opcode) != registers.end())
                ADD(registers, opcode, flagReg);
            else if (opcode == "M")
            {
                registers["A"] += memory[convert(intToHex(registers["H"], 2) + intToHex(registers["L"], 2))]; // get register values , convert to string , append , convert to int to get memory address and then add to a
            }
            else
            {
                cout << "Invalid location at location " << endl;
                exit(0);
            }
        }
        else if (opcode == "ADI")
        {
            getline(ss, opcode, ' ');
            if (!validCode(opcode, 2)) // check if data is of valid range
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
            else if (opcode == "M")
            {
                registers["A"] -= memory[convert(intToHex(registers["H"], 2) + intToHex(registers["L"], 2))]; // get register values , convert to string , append , convert to int to get memory address and then add to a
            }
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
                if (opcode == "B") // find valid register pairs
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
                    MOV(registers, opcode, temp);
                }
                else if (temp == "M")
                {
                    registers[opcode] = memory[convert(intToHex(registers["H"], 2) + intToHex(registers["L"], 2))]; // get register values , convert to string , append , convert to int to get memory address
                }
                else
                {
                    cout << "Wrong input" << endl;
                    exit(0);
                }
            }
            else if (opcode == "M")
            {
                string temp = "";
                getline(ss, temp, ',');
                if (registers.find(temp) != registers.end())
                {
                    memory[convert(intToHex(registers["H"], 2) + intToHex(registers["L"], 2))] = registers[opcode]; // get register values , convert to string , append , convert to int to get memory address
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
        else if (opcode == "LDA")
        {
            getline(ss, opcode, ' ');
            if (validCode(opcode, 4))
            {
                LDA(memory, registers, opcode, changed);
            }

            else
            {
                cout << "Invalid data" << endl;
                exit(0);
            }
        }
        else if (opcode == "STA")
        {
            getline(ss, opcode, ' ');
            if (validCode(opcode, 4))
            {
                STA(memory, registers, opcode, changed);
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
                    LXI(registers, opcode, nextReg, data);
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
        else if (opcode == "LHLD")
        {
            getline(ss, opcode, ' ');
            if (validCode(opcode, 4))
            {
                LHLD(memory, registers, opcode, changed);
            }
            else
            {
                cout << "Invalid data" << endl;
                exit(0);
            }
        }
        else if (opcode == "SHLD")
        {
            getline(ss, opcode, ' ');
            if (validCode(opcode, 4))
            {
                SHLD(memory, registers, opcode, changed);
            }
            else
            {
                cout << "Invalid data" << endl;
                exit(0);
            }
        }
        else if (opcode == "SET")
        {
            getline(ss, opcode, ' ');
            if (validCode(opcode, 4))
            {
                string temp = "";
                getline(ss, temp, ' ');
                if (validCode(temp, 2))
                {
                    SET(memory, opcode, temp, changed);
                }
                else
                {
                    cout << "No Valid data" << endl;
                    exit(0);
                }
            }
            else
            {
                cout << "No Valid address" << endl;
                exit(0);
            }
        }
        else if (opcode == "XCHG")
        {
            XCHG(registers);
        }
        else if (opcode == "LDAX")
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
                LDAX(memory, registers, opcode, nextReg, changed);
            }
        }
        else if (opcode == "STAX")
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
                STAX(memory, registers, opcode, nextReg, changed);
            }
        }
        else if (opcode == "CMA")
        {
            CMA(registers);
        }
        else if (opcode == "CMP")
        {
            getline(ss, opcode, ' ');
            if (registers.find(opcode) != registers.end())
            {
                CMP(registers, opcode, flagReg);
            }
            else
            {
                cout << "INVALID REGISTER" << endl;
                exit(0);
            }
        }
        else if (opcode == "JMP")
        {
            getline(ss, opcode, ' ');
            if (validCode(opcode, 4))
            {
                i = JMP(code, opcode);
                if (i == -1)
                {
                    cout << "You cannot jump there" << endl;
                    exit(0);
                }
            }
        }
        else if (opcode == "JC")
        {
            getline(ss, opcode, ' ');
            if (validCode(opcode, 4))
            {
                int v = JC(code, opcode, flagReg);
                if (v != 0)
                {
                    if (v != -1)
                        i = v;
                    else
                    {
                        cout << "You cannot jump there" << endl;
                        exit(0);
                    }
                }
            }
        }
        else if (opcode == "JNC")
        {
            getline(ss, opcode, ' ');
            if (validCode(opcode, 4))
            {
                int v = JNC(code, opcode, flagReg);
                if (v != 0)
                {
                    if (v != -1)
                        i = v;
                    else
                    {
                        cout << "You cannot jump there" << endl;
                        exit(0);
                    }
                }
            }
        }
        else if (opcode == "JZ")
        {
            getline(ss, opcode, ' ');
            if (validCode(opcode, 4))
            {
                int v = JZ(code, opcode, flagReg);
                if (v != 0)
                {
                    if (v != -1)
                        i = v;
                    else
                    {
                        cout << "You cannot jump there" << endl;
                        exit(0);
                    }
                }
            }
        }
        else if (opcode == "JNZ")
        {
            getline(ss, opcode, ' ');
            if (validCode(opcode, 4))
            {
                int v = JNZ(code, opcode, flagReg);
                if (v != 0)
                {
                    if (v != -1)
                    {
                        i = v;
                        cout << i << endl;
                    }
                    else
                    {
                        cout << "You cannot jump there" << endl;
                        exit(0);
                    }
                }
            }
        }
    }
}