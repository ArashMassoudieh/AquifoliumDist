#include <iostream>
#include "DistSystem.h"
#include "Script.h"
using namespace std;

int main()
{
    DistSystem system;
    system.GetQuanTemplate("/home/arash/Projects/QAquifolium/resources/main_components.json");
    system.AppendQuanTemplate("/home/arash/Projects/QAquifolium/resources/unsaturated_soil.json");
    //system.ReadSystemSettingsTemplate("/home/arash/Projects/QAquifolium/resources/settings.json");

    system.clear();
    system.CreateGrid("overlandflow","Catchment","/home/arash/Projects/AqDistFiles/Sligo_500.txt");
    system.SavetoScriptFile("/home/arash/Projects/AqDistFiles/testout.scr");
    //system.Solve();
}
