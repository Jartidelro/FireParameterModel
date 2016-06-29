#include "vegetation.h"
#include "parameters.h"
#include <iostream>


Vegetation::Vegetation()
{}

void Vegetation::writeplantParameterLists()
{
    for (int i=0; i<=12; i++)
    {
        grassParameterList[i] = parameters -> grassParametersV[i];
    }

}

