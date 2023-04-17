#include <map>
#include <string>
#include <vector>
using namespace std;
#ifndef BRANCH
#define BRANCH
int JMP( vector <pair<string,string>>& code , string location )
{
    for (int i = 0; i < code.size(); i++)
    {
        if(code[i].first == location)
            return i;
    }
    return -1;
    
}
int  JC(vector <pair<string,string>>& code , string location,vector <bool>&flag)
{
    if(flag[0] == true)
    {
        for (int i = 0; i < code.size(); i++)
        {
        if(code[i].first == location)
            return i;
        }
        return -1;
    }
    return 0;
}
int  JNC(vector <pair<string,string>>& code , string location,vector <bool>&flag)
{
    if(flag[0] == false)
    {
        for (int i = 0; i < code.size(); i++)
        {
        if(code[i].first == location)
            return i;
        }
        return -1;
    }
    return 0;
}
int  JZ(vector <pair<string,string>>& code , string location,vector <bool>&flag)
{
    if(flag[1] == true)
    {
        for (int i = 0; i < code.size(); i++)
        {
        if(code[i].first == location)
            return i;
        }
        return -1;
    }
    return 0;
}
int  JNZ(vector <pair<string,string>>& code , string location,vector <bool>&flag)
{
    if(flag[1] == false)
    {
        for (int i = 0; i < code.size(); i++)
        {
        if(code[i].first == location)
            return i;
        }
        return -1;
    }
    return 0;
}
#endif