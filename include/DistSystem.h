#ifndef DISTSYSTEM_
#define DISTSYSTEM_

#include <System.h>
#include <map>


class DistSystem : public System
{
    public:
        DistSystem();
        virtual ~DistSystem();
        DistSystem(const DistSystem& other);
        DistSystem& operator=(const DistSystem& other);
        vector<Object*> group(string s);
        bool CreateGrid(const string &name, const string &type, const string &matrixfile);
    protected:
        map<string,vector<Object*>> groups;
    private:
};

#endif // DISTSYSTEM_
