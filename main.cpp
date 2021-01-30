#include <iostream>
#include "System.h"
using namespace std;

int main()
{
    System system;
    system.GetQuanTemplate("/home/arash/Projects/QAquifolium/resources/main_components.json");
    system.ReadSystemSettingsTemplate("/home/arash/Projects/QAquifolium/resources/settings.json");

}
