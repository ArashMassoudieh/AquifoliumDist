#include <iostream>
#include "DistSystem.h"
#include "Script.h"
using namespace std;

int main()
{
    DistSystem system;
    //system.GetQuanTemplate("/home/arash/Projects/QAquifolium/resources/main_components.json");
    //system.ReadSystemSettingsTemplate("/home/arash/Projects/QAquifolium/resources/settings.json");
    Script scr("/home/arash/Dropbox/Aquifolium/infiltration_test.scr",&system);
    system.clear();
    system.CreateFromScript(scr);
    system.Solve();
}
