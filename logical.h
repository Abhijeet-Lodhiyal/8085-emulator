#ifndef LOGICAL
#define LOGICAL
void CMA(map <string,int>&registers)
{
        registers["A"]  = 255 - registers["A"] ;
}

void CMP(map <string,int>&registers,string &value,vector <bool>&flag)
{
    int val = registers["A"];
    int val2 = registers[value];
    if(val - val2 < 0)
    {
        flag[0] = 1;
        flag[4] = 1;
    }
    else
    {
        flag[0] = 0;
        flag[4] = 0;
    }
}

#endif