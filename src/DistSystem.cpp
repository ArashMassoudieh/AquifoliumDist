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
    unsigned int i=0;
    vector<vector<bool>> gridonoff;
    while (!file.eof())
    {
        vector<int> nodes = aquiutils::ATOI(aquiutils::getline(file));
        if (nodes.size()>0)
            groups[name].gridblocks.push_back(vector<string>());
        for (unsigned int j=0; j<nodes.size(); j++)
        {
            if (nodes[j]==1)
            {
                string blockname = name + "(" + aquiutils::numbertostring(i) + "$" + aquiutils::numbertostring(j) + ")";
                Block B;
                B.SetType(type);
                B.SetName(blockname);
                System::AddBlock(B);
                System::object(blockname)->SetName(blockname);
                groups[name].gridblocks[i].push_back(blockname);
            }
            else
            {
                groups[name].gridblocks[i].push_back("");
            }
        }
        i++;
    }
    return true;
}

bool DistSystem::SetProperty(const string &groupname, const string &propname, const string &propvalue)
{
    if (groups.count(groupname)==0)
    {
        ErrorHandler().Append("DistSystem","DistSystem","SetProperty","Group '" + groupname +"' was not found!",14011);
        return false;
    }
    for (unsigned int i=0; i<groups[groupname].gridblocks.size(); i++)
    {
        for (unsigned int j=0; j<groups[groupname].gridblocks[i].size(); j++)
        {
            if (groups[groupname].gridblocks[i][j]!="" && block(groups[groupname].gridblocks[i][j])!=nullptr)
                block(groups[groupname].gridblocks[i][j])->SetProperty(propname,propvalue);
        }
    }
    return true;
}

bool DistSystem::SetPropertyHLinks(const string &groupname, const string &propname, const string &propvalue)
{
    if (groups.count(groupname)==0)
    {
        ErrorHandler().Append("DistSystem","DistSystem","SetPropertyHLinks","Group '" + groupname +"' was not found!",14051);
        return false;
    }
    for (unsigned int i=0; i<groups[groupname].gridHlinks.size(); i++)
    {
        for (unsigned int j=0; j<groups[groupname].gridHlinks[i].size(); j++)
        {
            if (groups[groupname].gridHlinks[i][j]!="" && link(groups[groupname].gridHlinks[i][j])!=nullptr)
                link(groups[groupname].gridHlinks[i][j])->SetProperty(propname,propvalue);
        }
    }
    return true;
}
bool DistSystem::SetPropertyVLinks(const string &groupname, const string &propname, const string &propvalue)
{
    if (groups.count(groupname)==0)
    {
        ErrorHandler().Append("DistSystem","DistSystem","SetPropertyVLinks","Group '" + groupname +"' was not found!",14052);
        return false;
    }
    for (unsigned int i=0; i<groups[groupname].gridVlinks.size(); i++)
    {
        for (unsigned int j=0; j<groups[groupname].gridVlinks[i].size(); j++)
        {
            if (groups[groupname].gridVlinks[i][j]!="" && link(groups[groupname].gridVlinks[i][j])!=nullptr)
                link(groups[groupname].gridVlinks[i][j])->SetProperty(propname,propvalue);
        }
    }
    return true;
}


bool DistSystem::SetPropertyGrid(const string &groupname, const string &propname, const string &propvaluematrixfilename)
{
    ifstream file(propvaluematrixfilename);
    if (!file.good())
    {
        ErrorHandler().Append("DistSystem","DistSystem","CreateGrid","File '" + propvaluematrixfilename +"' was not found!",14012);
        return false;
    }
    if (groups.count(groupname)==0)
    {
        ErrorHandler().Append("DistSystem","DistSystem","SetProperty","Group '" + groupname +"' was not found!",14013);
        return false;
    }
    for (unsigned int i=0; i<groups[groupname].gridblocks.size(); i++)
    {

        if (file.eof())
        {
            ErrorHandler().Append("DistSystem","DistSystem","SetPropertyGrid","File '" + propvaluematrixfilename +"' is not consistent with the grid!",14014);
            return false;
        }
        vector<string> nodevalues = aquiutils::getline(file);
        if (nodevalues.size()<groups[groupname].gridblocks[i].size())
        {
            ErrorHandler().Append("DistSystem","DistSystem","SetPropertyGrid","File '" + propvaluematrixfilename +"' is not consistent with the grid!",14015);
            return false;
        }
        for (unsigned int j=0; j<groups[groupname].gridblocks[i].size(); j++)
        {
            if (groups[groupname].gridblocks[i][j]!="" && block(groups[groupname].gridblocks[i][j])!=nullptr)
                block(groups[groupname].gridblocks[i][j])->SetProperty(propname,nodevalues[j]);
        }
    }
    return true;
}

bool DistSystem::SetGeometry(const string &groupname, double x_0, double y_0, double dx, double dy, double width, double height)
{
    if (groups.count(groupname)==0)
    {
        ErrorHandler().Append("DistSystem","DistSystem","SetProperty","Group '" + groupname +"' was not found!",14016);
        return false;
    }
    for (unsigned int i=0; i<groups[groupname].gridblocks.size(); i++)
    {
        for (unsigned int j=0; j<groups[groupname].gridblocks[i].size(); j++)
        {
            if (groups[groupname].gridblocks[i][j]!="" && block(groups[groupname].gridblocks[i][j])!=nullptr)
            {
                block(groups[groupname].gridblocks[i][j])->SetProperty("x",aquiutils::numbertostring(i*dx+0.5*dx+x_0));
                block(groups[groupname].gridblocks[i][j])->SetProperty("y",aquiutils::numbertostring(j*dy+0.5*dy+y_0));
                block(groups[groupname].gridblocks[i][j])->SetProperty("_width",aquiutils::numbertostring(width));
                block(groups[groupname].gridblocks[i][j])->SetProperty("_height",aquiutils::numbertostring(height));
            }
        }
    }
    return true;
}

bool DistSystem::CreateGridLinks(const string &groupname, const string &type)
{
    if (groups.count(groupname)==0)
    {
        ErrorHandler().Append("DistSystem","DistSystem","SetProperty","Group '" + groupname +"' was not found!",14017);
        return false;
    }
    for (unsigned int i=0; i<groups[groupname].gridblocks.size()-1; i++)
    {
        groups[groupname].gridHlinks.push_back(vector<string>());
        for (unsigned int j=0; j<groups[groupname].gridblocks[i].size(); j++)
        {
            if (groups[groupname].gridblocks[i][j]!="" && block(groups[groupname].gridblocks[i][j])!=nullptr && groups[groupname].gridblocks[i+1][j]!="" && block(groups[groupname].gridblocks[i+1][j])!=nullptr)
            {
                Link _link;
                _link.SetQuantities(GetMetaModel(),type);
                _link.SetType(type);
                string linkname = groups[groupname].gridblocks[i][j] + "-" + groups[groupname].gridblocks[i+1][j];
                _link.SetName(linkname);
                AddLink(_link, groups[groupname].gridblocks[i][j], groups[groupname].gridblocks[i+1][j]);

                object(linkname)->SetName(linkname);

                AddAllConstituentRelateProperties(link(linkname));
                SetVariableParents();
                groups[groupname].gridHlinks[i].push_back(linkname);
            }
            else
            {
                groups[groupname].gridHlinks[i].push_back("");
            }
        }
    }

    for (unsigned int i=0; i<groups[groupname].gridblocks.size(); i++)
    {
        groups[groupname].gridVlinks.push_back(vector<string>());
        for (unsigned int j=0; j<groups[groupname].gridblocks[i].size()-1; j++)
        {
            if (groups[groupname].gridblocks[i][j]!="" && block(groups[groupname].gridblocks[i][j])!=nullptr && groups[groupname].gridblocks[i][j+1]!="" && block(groups[groupname].gridblocks[i][j+1])!=nullptr)
            {
                Link _link;
                _link.SetQuantities(GetMetaModel(),type);
                _link.SetType(type);
                string linkname = groups[groupname].gridblocks[i][j] + "-" + groups[groupname].gridblocks[i][j+1];
                _link.SetName(linkname);
                AddLink(_link, groups[groupname].gridblocks[i][j], groups[groupname].gridblocks[i][j+1]);

                object(linkname)->SetName(linkname);

                AddAllConstituentRelateProperties(link(linkname));
                SetVariableParents();
                groups[groupname].gridVlinks[i].push_back(linkname);
            }
            else
            {
                groups[groupname].gridVlinks[i].push_back("");
            }
        }
    }
    return true;
}

bool DistSystem::SetPropertyGridHlinks(const string &groupname, const string &propname, const string &propvaluematrixfilename)
{
    ifstream file(propvaluematrixfilename);
    if (!file.good())
    {
        ErrorHandler().Append("DistSystem","DistSystem","SetPropertyGridHLinkd","File '" + propvaluematrixfilename +"' was not found!",14018);
        return false;
    }
    if (groups.count(groupname)==0)
    {
        ErrorHandler().Append("DistSystem","DistSystem","SetPropertyGridHLinkd","Group '" + groupname +"' was not found!",14019);
        return false;
    }
    for (unsigned int i=0; i<groups[groupname].gridHlinks.size(); i++)
    {

        if (file.eof())
        {
            ErrorHandler().Append("DistSystem","DistSystem","SetPropertyGridHLinkd","File '" + propvaluematrixfilename +"' is not consistent with the grid!",14020);
            return false;
        }
        vector<string> nodevalues = aquiutils::getline(file);
        if (nodevalues.size()<groups[groupname].gridHlinks[i].size())
        {
            ErrorHandler().Append("DistSystem","DistSystem","SetPropertyGridHLinks","File '" + propvaluematrixfilename +"' is not consistent with the grid!",14021);
            return false;
        }
        for (unsigned int j=0; j<groups[groupname].gridHlinks[i].size(); j++)
        {
            if (groups[groupname].gridHlinks[i][j]!="" && link(groups[groupname].gridHlinks[i][j])!=nullptr)
                link(groups[groupname].gridHlinks[i][j])->SetProperty(propname,nodevalues[j]);
        }
    }
    return true;
}

bool DistSystem::SetPropertyGridVlinks(const string &groupname, const string &propname, const string &propvaluematrixfilename)
{
    ifstream file(propvaluematrixfilename);
    if (!file.good())
    {
        ErrorHandler().Append("DistSystem","DistSystem","SetPropertyGridVlinks","File '" + propvaluematrixfilename +"' was not found!",14022);
        return false;
    }
    if (groups.count(groupname)==0)
    {
        ErrorHandler().Append("DistSystem","DistSystem","SetPropertyGridVlinks","Group '" + groupname +"' was not found!",14023);
        return false;
    }
    for (unsigned int i=0; i<groups[groupname].gridHlinks.size(); i++)
    {

        if (file.eof())
        {
            ErrorHandler().Append("DistSystem","DistSystem","SetPropertyGridVlinks","File '" + propvaluematrixfilename +"' is not consistent with the grid!",14024);
            return false;
        }
        vector<string> nodevalues = aquiutils::getline(file);
        if (nodevalues.size()<groups[groupname].gridVlinks[i].size())
        {
            ErrorHandler().Append("DistSystem","DistSystem","SetPropertyGridVlinks","File '" + propvaluematrixfilename +"' is not consistent with the grid!",14025);
            return false;
        }
        for (unsigned int j=0; j<groups[groupname].gridVlinks[i].size(); j++)
        {
            if (groups[groupname].gridVlinks[i][j]!="" && link(groups[groupname].gridVlinks[i][j])!=nullptr)
                link(groups[groupname].gridVlinks[i][j])->SetProperty(propname,nodevalues[j]);
        }
    }
    return true;
}
