#include "DistSystem.h"

DistSystem::DistSystem()
{
    //ctor
}

DistSystem::~DistSystem()
{
    //dtor
}

DistSystem::DistSystem(const DistSystem& other) : System(other)
{

}

DistSystem& DistSystem::operator=(const DistSystem& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    System::operator=(rhs);
    return *this;
}

vector<Object*> DistSystem::group(string s)
{
    if (groups.count(s)==0)
        return vector<Object*>();
    else
        return groups[s];

}

bool DistSystem::CreateGrid(const string &name, const string &type, const string &matrixfile)
{
    ofstream file(matrixfile);
    if (!matrixfile.good())
    {
        return false;
    }
    int i=0;
    vector<vector<bool>> gridonoff;
    while (!matrixfile.eof())
    {
        vector<int> nodes = ATOI(getline(matrixfile));
        for (int j=0; j<nodes.size(); j++)
        {
            if (nodes[j]==1)
            {
                string blockname = name + "(" + numbertostring(i) + "," + numbertostring(j) + ")";
                Block B;
                B.SetType(type);
                B.SetName(blockname);
                System::AddBlock(B);
                system.object(name)->SetName(name);
                System::object(blockname).SetName(blockname);
            }
        }
    }
}
