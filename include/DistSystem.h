#ifndef DISTSYSTEM_
#define DISTSYSTEM_

#include <System.h>
#include <map>

struct GridData
{
    vector<vector<Block*>> gridblocks;
    vector<vector<Link*>> gridHlinks;
    vector<vector<Link*>> gridVlinks;
    vector<vector<Link*>> gridtogridlinks;
};

class DistSystem : public System
{
    public:
        DistSystem();
        virtual ~DistSystem();
        DistSystem(const DistSystem& other);
        DistSystem& operator=(const DistSystem& other);
        GridData* group(string s);
        bool CreateGrid(const string &name, const string &type, const string &matrixfile);
        bool SetProperty(const string &groupname, const string &propname, const string &propvalue);
        bool SetPropertyGrid(const string &groupname, const string &propname, const string &propvaluematrixfilename);
    protected:
        map<string,GridData> groups;
    private:
};

#endif // DISTSYSTEM_
