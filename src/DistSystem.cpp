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

GridData* DistSystem::group(string s)
{
    if (groups.count(s)==0)
        return nullptr;
    else
        return &groups[s];

}

bool DistSystem::CreateGrid(const string &name, const string &type, const string &matrixfile)
{
    if (groups.count(name)==1)
    {
        ErrorHandler().Append("DistSystem","DistSystem","CreateGrid","Group '" + name +"' already exists!",14001);
        return false;
    }
    ifstream file(matrixfile);
    if (!file.good())
    {
        ErrorHandler().Append("DistSystem","DistSystem","CreateGrid","File '" + matrixfile +"' was not found!",14002);
        return false;
    }
    int i=0;
    vector<vector<bool>> gridonoff;
    while (!file.eof())
    {
        vector<int> nodes = aquiutils::ATOI(aquiutils::getline(file));
        groups[name].gridblocks.push_back(vector<Block*>());
        for (int j=0; j<nodes.size(); j++)
        {
            if (nodes[j]==1)
            {
                string blockname = name + "(" + aquiutils::numbertostring(i) + "," + aquiutils::numbertostring(j) + ")";
                Block B;
                B.SetType(type);
                B.SetName(blockname);
                System::AddBlock(B);
                System::object(blockname)->SetName(blockname);
                groups[name].gridblocks[i].push_back(System::block(blockname));
            }
            else
            {
                groups[name].gridblocks[i].push_back(nullptr);
            }
        }
        i++;
    }
}

bool DistSystem::SetProperty(const string &groupname, const string &propname, const string &propvalue)
{
    if (groups.count(groupname)==0)
    {
        ErrorHandler().Append("DistSystem","DistSystem","SetProperty","Group '" + groupname +"' was not found!",14011);
        return false;
    }
    for (int i=0; i<groups[groupname].gridblocks.size(); i++)
    {
        for (int j=0; j<groups[groupname].gridblocks[i].size(); j++)
        {
            if (groups[groupname].gridblocks[i][j]!=nullptr)
                groups[groupname].gridblocks[i][j]->SetProperty(propname,propvalue);
        }
    }
    return true;
}
bool DistSystem::SetPropertyGrid(const string &groupname, const string &propname, const string &propvaluematrixfilename)
{

}

