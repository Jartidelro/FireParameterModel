#ifndef VEGETATION_H
#define VEGETATION_H

#include "parameters.h"


class Vegetation
{
public:
    Vegetation();

    void writeplantParameterLists();

    float shrubParameterList[13];
    float grassParameterList[13];
    Parameters* parameters;
};


#endif // VEGETATION_H
