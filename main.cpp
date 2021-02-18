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
    system.SetProperty("overlandflow","area","250000");
    system.SetProperty("overlandflow","ManningCoeff","0.02");
    system.SetGeometry("overlandflow",0,0,500,500,200,200);
    system.SetPropertyGrid("overlandflow","elevation","/home/arash/Projects/AqDistFiles/Topo_500.txt");
    system.CreateGridLinks("overlandflow","Catchment_link");
    system.SavetoScriptFile("/home/arash/Projects/AqDistFiles/testout.scr");
    system.GetErrorHandler()->Write("/home/arash/Projects/AqDistFiles/errors.txt");
    //system.Solve();
}
