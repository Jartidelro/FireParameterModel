#include "parameters.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Parameters::Parameters()
{
}

int Parameters::get_gridSize()
{
    std::cin >> xymax;
    return xymax;
}

float Parameters::get_cellSize()
{
    std::cin >> cellSize;
    return cellSize;
}


void Parameters::vegparamFile_input()
{
    std::string load;

    std::string directory = "C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/"; // Uni laptop
    std::cout << "The directory is: " << directory << std::endl;
    std::cout << "Input filename:" << std::endl;
    std::string input;
    std::cin >> input;
    std::string paramFile2 = directory + input;

    std::ifstream paramFile(paramFile2);

    if (!paramFile.is_open())
    {
        std::cerr << "Failed to open parameter file!\n";
    }

    std::string INMfGrassMIN = "Fuel_moisture_content(g*g-1)_MIN_grass:\t";
    std::string INMfGrassMAX = "Fuel_moisture_content(g*g-1)_MAX_grass:\t";
    std::string INsigmaGrassMIN = "SAV_ratio(cm-1)_MIN_grass:\t";
    std::string INsigmaGrassMAX = "SAV_ratio(cm-1)_MAX_grass:\t";
    std::string INwoGrassMIN = "Ovendry_fuel_load(kg*m-2)_MIN_grass:\t";
    std::string INwoGrassMAX = "Ovendry_fuel_load(kg*m-2)_MAX_grass:\t";
    std::string INdeltaGrasssMIN = "Fuel_depth(m)_MIN_grass:\t";
    std::string INdeltaGrassMAX = "Fuel_depth(m)_MAX_grass:\t";
    std::string INhGrass = "Biomass_energy_content(kJ*kg-1)_grass:\t";
    std::string INrhoPGrass = "Fuel_particle_density(kg*m-3)_grass:\t";
    std::string INMxGrass = "Fuel_extinction_moisture_grass:\t";
    std::string INsTGrass = "Total_mineral_content_grass:\t";
    std::string INseGrass = "Effective_mineral_content_grass:\t";

    std::string INMfStemMIN = "Fuel_moisture_content(g*g-1)_MIN_Stem:\t";
    std::string INMfStemMAX = "Fuel_moisture_content(g*g-1)_MAX_Stem:\t";
    std::string INsigmaStemMIN = "SAV_ratio(cm-1)_MIN_Stem:\t";
    std::string INsigmaStemMAX = "SAV_ratio(cm-1)_MAX_Stem:\t";
    std::string INdeltaShrubsMIN = "Fuel_depth(m)_MIN_shrubs:\t";
    std::string INdeltaShrubsMAX = "Fuel_depth(m)_MAX_shrubs:\t";
    std::string INhStem = "Biomass_energy_content(kJ*kg-1)_Stem:\t";
    std::string INrhoPShrubs = "Fuel_particle_density(kg*m-3):\t";
    std::string INMxShrubs = "Fuel_extinction_moisture_shrubs:\t";
    std::string INsTShrubs = "Total_mineral_content_shrubs:\t";
    std::string INseShrubs = "Effective_mineral_content_shrubs:\t";
    std::string INwoShrubsMIN = "Ovendry_fuel_load(kg*m-2)_MIN_shrubs:\t";
    std::string INwoShrubsMAX = "Ovendry_fuel_load(kg*m-2)_MAX_shrubs:\t";
    std::string INMfBranchMIN = "Fuel_moisture_content(g*g-1)_MIN_Branch:\t";
    std::string INMfBranchMAX = "Fuel_moisture_content(g*g-1)_MAX_Branch:\t";
    std::string INsigmaBranchMIN = "SAV_ratio(cm-1)_MIN_Branch:\t";
    std::string INsigmaBranchMAX = "SAV_ratio(cm-1)_MAX_Branch:\t";
    std::string INCVMIN = "Shrub_crown_volume(m3)_MIN:\t";
    std::string INCVMAX = "Shrub_crown_volume(m3)_MAX:\t";


    std::string foundIt;
    int fsize = 1000;

    if (foundIt.find(INMfGrassMIN) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> MfGrassMIN;
    }

    if (foundIt.find(INMfGrassMAX) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> MfGrassMAX;
    }

    if (foundIt.find(INsigmaGrassMIN) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> sigmaGrassMIN;
    }

    if (foundIt.find(INsigmaGrassMAX) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> sigmaGrassMAX;
    }

    if (foundIt.find(INwoGrassMIN) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> woGrassMIN;
    }

    if (foundIt.find(INwoGrassMAX) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> woGrassMAX;
    }

    if (foundIt.find(INdeltaGrasssMIN) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> deltaGrassMIN;
    }

    if (foundIt.find(INdeltaGrassMAX) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> deltaGrassMAX;
    }

    if (foundIt.find(INhGrass) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> hGrass;
    }

    if (foundIt.find(INrhoPGrass) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> rhoPGrass;
    }

    if (foundIt.find(INMxGrass) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> MxGrass;
    }

    if (foundIt.find(INsTGrass) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> sTGrass;
    }

    if (foundIt.find(INseGrass) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> seGrass;
    }




    if (foundIt.find(INMfStemMIN) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> MfStemMIN;
    }
    if (foundIt.find(INMfStemMAX) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> MfStemMAX;
    }
    if (foundIt.find(INsigmaStemMIN) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> sigmaStemMIN;
    }
    if (foundIt.find(INsigmaStemMAX) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> sigmaStemMAX;
    }
    if (foundIt.find(INdeltaShrubsMIN) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> deltaShrubsMIN;
    }
    if (foundIt.find(INdeltaShrubsMAX) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> deltaShrubsMAX;
    }
    if (foundIt.find(INhStem) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> hStem;
    }
    if (foundIt.find(INrhoPShrubs) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> rhoPShrubs;
    }
    if (foundIt.find(INMxShrubs) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> MxShrubs;
    }
    if (foundIt.find(INsTShrubs) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> sTShrubs;
    }
    if (foundIt.find(INseShrubs) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> seShrubs;
    }
    if (foundIt.find(INwoShrubsMIN) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> woShrubsMIN;
    }
    if (foundIt.find(INwoShrubsMAX) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> woShrubsMAX;
    }
    if (foundIt.find(INMfBranchMIN) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> MfBranchMIN;
    }
    if (foundIt.find(INMfBranchMAX) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> MfBranchMAX;
    }
    if (foundIt.find(INsigmaBranchMIN) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> sigmaBranchMIN;
    }
    if (foundIt.find(INsigmaBranchMAX) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> sigmaBranchMAX;
    }
    if (foundIt.find(INhBranch) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> hBranch;
    }
    if (foundIt.find(INCVMIN) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> CVMIN;
    }
    if (foundIt.find(INCVMAX) == std::string::npos)
    {
        paramFile.ignore(fsize,'\t');
        paramFile >> CVMAX;
    }

}

void Parameters::writeGridSizeFile()
{
    std::ofstream outfile ("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/GridSize.txt"); // uni laptop
    //std::ofstream outfile ("/home/jarro/ownCloud/Master/Programming/Parameter_input/GridSize.txt"); // home laptop
    outfile << xymax;
    outfile.close();
}

void Parameters::writeCellSizeFile()
{
    std::ofstream outfile ("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/CellSize.txt"); // uni laptop
    //std::ofstream outfile ("/home/jarro/ownCloud/Master/Programming/Parameter_input/GridSize.txt"); // home laptop
    outfile << cellSize;
    outfile.close();
}



