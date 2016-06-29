#include <QCoreApplication>
#include <iostream>
#include <fstream>
#include <ctime>
//#include <conio.h>

#include "landscape.h"
#include "parameters.h"
#include "vegetation.h"
#include "output.h"
#include "climate.h"



int main()
{
    srand(time(0));
    //const int ijmax = 10; // This is not dynamical anymore! But otherwise I'll have to use dynamic arrays...

    Parameters* parameters = new Parameters();

    // Initialise the grid size:
    std::cout << "Enter the grid size (number of cells on one axis): " << std::endl;
    parameters -> get_gridSize();
    const int ijmax = parameters -> xymax;
    std::cout << "The grid size is " << ijmax << " by " << ijmax << " cells." << std::endl;
    parameters -> writeGridSizeFile();

    // Initialise the cell size (in m):
    std::cout << "Enter the cell size [m]: " << std::endl;
    parameters -> get_cellSize();
    std::cout << "The cell size is " << parameters->cellSize << " m" << std::endl;
    parameters -> writeGridSizeFile();
    parameters -> writeCellSizeFile();

    Climate* climate = new Climate();

    parameters -> vegparamFile_input();
    std::cout << "Press ENTER to continue." << std::endl;
    std::cin.get();

    //std::cout << "FuelmoistMIN: " << parameters -> fuelMoistContGrassMIN << std::endl;

    climate -> chooseSeason();
    climate -> writeSeasonFile();


    // The Landscape and Fire pointers have to be declared after ijmax was initialised:
    Landscape* landscape = new Landscape(ijmax);

    landscape -> initialise(ijmax);
    landscape -> distributeVegParameters(ijmax,parameters);

    landscape -> writeLandArrayFile(ijmax);
    landscape->writeParameterFiles(ijmax);


    landscape -> landArrayDelete(ijmax);

    return 0;
}

