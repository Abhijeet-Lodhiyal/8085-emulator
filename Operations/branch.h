#ifndef BRANCH
#define BRANCH
int JMP( vector <pair<int,string>>& code , string location )
{
    int address = convert(location);
    for (int i = 0; i < code.size(); i++)
    {
        if(code[i].first == address)
            return i-1;
    }
    return -1;
}

int  JC(vector <pair<int,string>>& code , string location,vector <bool>&flag)
{
    int address = convert(location);
    if(flag[0] == true)
    {
        for (int i = 0; i < code.size(); i++)
        {
        if(code[i].first == address)
            return i-1;
        }
        return -1;
    }
    return 0;
}
int  JNC(vector <pair<int,string>>& code , string location,vector <bool>&flag)
{
    int address = convert(location);
    if(flag[0] == false)
    {
        for (int i = 0; i < code.size(); i++)
        {
        if(code[i].first == address)
            return i-1;
        }
        return -1;
    }
    return 0;
}
int  JZ(vector <pair<int,string>>& code , string location,vector <bool>&flag)
{
    int address = convert(location);
    if(flag[1] == true)
    {
        for (int i = 0; i < code.size(); i++)
        {
        if(code[i].first == address)
            return i-1;
        }
        return -1;
    }
    return 0;
}
int  JNZ(vector <pair<int,string>>& code , string location,vector <bool>&flag)
{
    int address = convert(location);
    if(flag[1] == false)
    {
        for (int i = 0; i < code.size(); i++)
        {
        if(code[i].first == address)
        {
            return i-1;
        }
        }
        return -1;
    }
    return 0;
}
#endif