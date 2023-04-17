#include <map>
#include <vector>
#include <string>
#include <sstream>
#include "execute.h"
using namespace std;
int main()
{
    int startVal = 0;
    map <int,int> memory2;
    map<string, string> memory;
    for (int i = 0; i <= 65535; i++)
    {
        string memName = "";
        int j = i;
        memName = intToHex(j, 4);
        memory.insert({memName, "00"});
        memory2.insert({i,0});
    }
    map<string, string> registers = {{"A", "00"}, {"B", "03"}, {"C", "40"}, {"D", "FA"}, {"E", "04"}, {"H", "0A"}, {"L", "FE"}};
    map<string, int> registersVal = {{"A", 0}, {"B", 0}, {"C", 0}, {"D", 0}, {"E", 0}, {"H", 0}, {"L", 0}};
    vector<bool> flagReg(5, false);
    vector<pair<int, string>> code;
    string start;
    cout << "Enter starting address" << endl;
    cin >> start;
    if(!validCode(start,4))
    {
        cout<<"Invalid start address"<<endl;
        exit(0);
    }
    else
    {
        startVal = convert(start);
        cout<<startVal<<endl;
        cout<<hex<<startVal<<endl;
    }
    string input;
    cout << "Enter code" << endl;
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
        if(getBYTES(temp) == 0 && temp != "")
        {
            cout<<"INVALID SYNTAX"<<endl;
            exit(0);
        }
        startVal = startVal + getBYTES(temp);
    }
    cout<<"Your code"<<endl;
    for (auto i : code)
    {
        cout << i.first << " : " << i.second << endl;
    }
    // execute(memory, registers, flagReg, code);
    for (auto i : registers)
    {
        cout << i.first << " " << i.second << endl;
    }
    cout << flagReg[0] << " " << flagReg[1] << " " << flagReg[2] << " " << flagReg[3] << " " << flagReg[4] << " " << endl;
    return 0;
}
