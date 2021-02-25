#ifndef DISTSYSTEM_
#define DISTSYSTEM_

#include <System.h>
#include <map>

struct GridData
{
    vector<vector<string>> gridblocks;
    vector<vector<string>> gridHlinks;
    vector<vector<string>> gridVlinks;
    vector<vector<string>> gridtogridlinks;
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
        bool SetPropertyHLinks(const string &groupname, const string &propname, const string &propvalue);
        bool SetPropertyVLinks(const string &groupname, const string &propname, const string &propvalue);
        bool SetPropertyGrid(const string &groupname, const string &propname, const string &propvaluematrixfilename);
        bool SetGeometry(const string &groupname, double x_0, double y_0, double dx, double dy, double width=200, double height=200);
        bool CreateGridLinks(const string &groupname, const string &type);
        bool SetPropertyGridVlinks(const string &groupname, const string &propname, const string &propvaluematrixfilename);
        bool SetPropertyGridHlinks(const string &groupname, const string &propname, const string &propvaluematrixfilename);

protected:
        map<string,GridData> groups;
    private:
};

#endif // DISTSYSTEM_
