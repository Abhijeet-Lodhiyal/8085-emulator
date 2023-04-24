#include <map>
#include <vector>
#include <iomanip>
#include <set>
#include <string>
#include <sstream>
#include <iostream>
#include "execute.h"


using namespace std;
int main()
{

    // Memory initialization
    string start, file;
    int startVal = 0, choice = -1,getChoice = -1;
    map<int, int> memory;
    set <int> changed;
    for (int i = 0; i <= 65535; i++)
    {
        memory.insert({i, 0});
    }
    map<string, int> registersVal = {{"A", 00}, {"B", 00}, {"C", 00}, {"D", 00}, {"E", 00}, {"H", 00}, {"L", 00}};
    vector<bool> flagReg(5, false);
    vector<pair<int, string>> code;


    // User input
    cout << "Enter 1 to type program , enter 2 to open program from file location , enter 3 to open debugger mode" << endl;
    cin >> choice;
    if (choice == 1 )
    {
        inputUser(start,startVal,code);
    }
    else if (choice == 2)
    {
        inputFile(file,start,startVal,code);
    }
    else if(choice == 3)
    {
        cout<<"Enter 1 to type program , 2 to enter location"<<endl;
        cin>>getChoice;
        if(getChoice == 1)
        {
            cin.ignore();
            inputUser(start,startVal,code);
        }
        else
        {
            cin.ignore();
            inputFile(file,start,startVal,code);
        }
    }


    // To display the code about to be executed
    cout << "Your code" << endl;
    for (auto i : code)
    {
        cout << i.first << " : " << i.second << endl;
    }

    // Execution 
    if(choice == 3)
    {
        cin.ignore();                   // To clear value from buffer
        cin.clear();                    // To clear EOF clear after ctrl + z
        execute(memory, registersVal, flagReg, code,changed,1);
    }
    else
    {
        cin.ignore();
        cin.clear();
        execute(memory, registersVal, flagReg, code,changed);
    }

    // Printing memory
    printMemory(registersVal,memory,flagReg,changed);
    return 0;
}
