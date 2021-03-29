#include <iostream>
#include "ossie/ossieSupport.h"

#include "CustomSource.h"
int main(int argc, char* argv[])
{
    CustomSource_i* CustomSource_servant;
    Component::start_component(CustomSource_servant, argc, argv);
    return 0;
}

