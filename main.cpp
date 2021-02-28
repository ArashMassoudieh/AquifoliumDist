#include <iostream>
#include "DistSystem.h"
#include "Script.h"
using namespace std;

int main()
{
    DistSystem system;
    system.GetQuanTemplate("/home/arash/Projects/QAquifolium/resources/main_components.json");
    system.AppendQuanTemplate("/home/arash/Projects/QAquifolium/resources/rainfall_runoff.json");
    system.ReadSystemSettingsTemplate("/home/arash/Projects/QAquifolium/resources/settings.json");

    system.clear();
    system.CreateGrid("overlandflow","catchment-distributed","/home/arash/Projects/AqDistFiles/Sligo_500.txt");

    Source precip;
    precip.SetQuantities(system.GetMetaModel(),"Precipitation");
    precip.SetType("Precipitation");
    precip.SetName("rain");
    system.AddSource(precip);
    system.object("rain")->SetName("rain");
    system.object("rain")->SetProperty("timeseries","/home/arash/Projects/AqDistFiles/rain.txt");
    system.SetProperty("overlandflow","area","250000");
    system.SetProperty("overlandflow","ManningCoeff","0.02");
    system.SetProperty("overlandflow","Precipitation","rain");
    system.SetGeometry("overlandflow",0,0,500,500,200,200);
    system.SetPropertyGrid("overlandflow","elevation","/home/arash/Projects/AqDistFiles/Topo_500.txt");
    system.CreateGridLinks("overlandflow","distributed_catchment_link");
    system.SetPropertyHLinks("overlandflow","Width","500");
    system.SetPropertyHLinks("overlandflow","Length","500");
    system.SetPropertyVLinks("overlandflow","Width","500");
    system.SetPropertyVLinks("overlandflow","Length","500");
    system.SetSystemSettingsObjectProperties("simulation_start_time","0");
    system.SetSystemSettingsObjectProperties("simulation_end_time","10");
    system.SetSystemSettingsObjectProperties("write_solution_details","yes");
    system.SetSystemSettingsObjectProperties("silent","0");
    system.SavetoScriptFile("/home/arash/Projects/AqDistFiles/testout.scr");
    system.GetErrorHandler()->Write("/home/arash/Projects/AqDistFiles/errors.txt");
    system.SetSystemSettings();

    system.Solve(true);
    system.GetOutputs().writetofile(string("/home/arash/Projects/AqDistFiles/outputs.txt"));

    //system.Solve();
}
