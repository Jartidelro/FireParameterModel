#include "landscape.h"
#include "climate.h"
#include "parameters.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <random>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <vector>
#include <sstream>
//#include <conio.h>
#include <cfloat>


/** Create a constructor:****************************/
/* - a constructor is a function that gets called automatically as soon as you create an object
     * - main reason for constructor: give variables an initial value
     * - constructors never return values (return type), they simply initialise the object
     * - the constructor always has the same name as the class it's in */
Landscape::Landscape(const int ijmax){
    num_vegfree = ijmax*ijmax*25/100;
    num_annuals = ijmax*ijmax*25/100;
    num_perennials = ijmax*ijmax*25/100;
    num_shrubs = ijmax*ijmax*25/100;

    aggregation_annuals = 98;
    aggregation_perennials = 98;
    aggregation_shrubs = 98;
    patchNum_annuals = ijmax;
    patchNum_perennials = ijmax;
    patchNum_shrubs = ijmax;



}

/** Destructor**************************************/
Landscape::~Landscape() {}

// random number generator:
int Landscape::rand_int(int from, int to)
{
    /*std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(from, to);
    std::cout << "Random number!! " << distr(gen) << std::endl;
    //return distr(gen);*/

    int help = to-from;
    int i2 = rand() % help;
    i2 += from;
    return i2;
}

float Landscape::rand_float(float from, float to)
{
    std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(from, std::nextafter(to, DBL_MAX));
        return dis(gen);
}

// Landscape functions:
void Landscape::initialise(const int ijmax)
{


    // A dynamic 2D array is basically an array of pointers to arrays. You should initialize it using a loop, like this:
    // (from: http://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new)
    landArray = new int*[ijmax];
    for(int i=0; i<ijmax; i++)
    {
        landArray[i] = new int[ijmax];
    }


    int ipos, jpos;

    /** initialise the plant-type landscape: **/

    for (int i = 0; i < ijmax; i++)
    {
        for (int j = 0; j < ijmax; j++)
        {
            landArray [i][j] = 0;
        }
    }

    /**std::cout << "landArray initialised to 0. press to continue." << "\n";
    getch();**/

    // Set a few random positions on grid to 4 (no vegetation):

    for (int i = 0; i < num_vegfree; i++)
    {

        ipos = rand_int(0,ijmax);
        jpos = rand_int(0,ijmax);

        if (landArray[ipos][jpos] == 0)
        {
            landArray[ipos][jpos] = 4;
        }
        else
        {
            while (landArray[ipos][jpos] != 0)
            {
                ipos = rand_int(0,ijmax);
                jpos = rand_int(0,ijmax);
            }
            landArray[ipos][jpos] = 4;
        }
    }


    /** First set cluster-patches for all vegtypes:*********************/

    // annuals:
    for (int i = 0; i < patchNum_annuals; i++)
    {
        ipos = rand_int(0,ijmax);
        jpos = rand_int(0,ijmax);

        if (landArray[ipos][jpos] == 0)
        {
            landArray[ipos][jpos] = 5;
        }
        else
        {
            while (landArray[ipos][jpos] != 0)
            {
                ipos = rand_int(0,ijmax);
                jpos = rand_int(0,ijmax);
            }
            landArray[ipos][jpos] = 5;
        }
    }


    /** Cluster randomly some% of the annuals around cluster-patches: ******************/

    int i_annuals = 0;
    while (i_annuals < (num_annuals - patchNum_annuals))
    {
        // std::cout << "i_annuals" << i_annuals << std::endl;
        ipos = rand_int(0,ijmax);
        jpos = rand_int(0,ijmax);
        int aggregate = rand_int(0,100);

        if (landArray[ipos][jpos] == 0)
        {
            if ((jpos-1) >= 0 && landArray[ipos][jpos-1] == 5)
            {
                landArray[ipos][jpos] = 5;
                i_annuals++;
                continue; // continue jumps back to the beginning of the loop
            }
            if ((ipos+1) < ijmax && (jpos-1) >= 0 && landArray[ipos+1][jpos-1] == 5)
            {
                landArray[ipos][jpos] = 5;
                i_annuals++;
                continue;
            }
            if ((ipos+1) < ijmax && landArray[ipos+1][jpos] == 5)
            {
                landArray[ipos][jpos] = 5;
                i_annuals++;
                continue;
            }
            if ((ipos+1) < ijmax && (jpos+1) < ijmax && landArray[ipos+1][jpos+1] == 5)
            {
                landArray[ipos][jpos] = 5;
                i_annuals++;
                continue;
            }
            if ((jpos+1) < ijmax && landArray[ipos][jpos+1] == 5)
            {
                landArray[ipos][jpos] = 5;
                i_annuals++;
                continue;
            }
            if ((ipos-1) >= 0 && (jpos+1) < ijmax && landArray[ipos-1][jpos+1] == 5)
            {
                landArray[ipos][jpos] = 5;
                i_annuals++;
                continue;
            }
            if ((ipos-1) >= 0 && landArray[ipos-1][jpos] == 5)
            {
                landArray[ipos][jpos] = 5;
                i_annuals++;
                continue;
            }
            if ((ipos-1) >= 0 && (jpos-1) >= 0 && landArray[ipos-1][jpos-1] == 5)
            {
                landArray[ipos][jpos] = 5;
                i_annuals++;
                continue;
            }
        }

        if (landArray[ipos][jpos] == 0)
        {
            if (aggregate > aggregation_annuals)
            {
                landArray[ipos][jpos] = 5;
                i_annuals++;
                continue;
            }
        }
    }

    /**std::cout << "annuals distributed. press to continue." << "\n";
    getch();**/

    /** Set and cluster randomly some% of the cells to 6 (perennials): **************************/

    for (int i = 0; i < patchNum_perennials; i++)
    {
        ipos = rand_int(0,ijmax);
        jpos = rand_int(0,ijmax);

        if (landArray[ipos][jpos] == 0)
        {
            landArray[ipos][jpos] = 6;
        }
        else
        {
            while (landArray[ipos][jpos] != 0)
            {
                ipos = rand_int(0,ijmax);
                jpos = rand_int(0,ijmax);
            }
            landArray[ipos][jpos] = 6;
        }
    }

    /**std::cout << "cluster-patches perennials initialised. press to continue." << "\n";
    getch();**/

    int i_perennials = 0;
    while (i_perennials < (num_perennials - patchNum_perennials))
    {
        // std::cout << "i_perennials" << i_perennials << std::endl;
        ipos = rand_int(0,ijmax);
        jpos = rand_int(0,ijmax);
        int aggregate = rand_int(0,100);

        if (landArray[ipos][jpos] == 0)
        {
            if ((jpos-1) >= 0 && landArray[ipos][jpos-1] == 6)
            {
                landArray[ipos][jpos] = 6;
                i_perennials++;
                continue; // continue jumps back to the beginning of the loop
            }
            if ((ipos+1) < ijmax && (jpos-1) >= 0 && landArray[ipos+1][jpos-1] == 6)
            {
                landArray[ipos][jpos] = 6;
                i_perennials++;
                continue;
            }
            if ((ipos+1) < ijmax && landArray[ipos+1][jpos] == 6)
            {
                landArray[ipos][jpos] = 6;
                i_perennials++;
                continue;
            }
            if ((ipos+1) < ijmax && (jpos+1) < ijmax && landArray[ipos+1][jpos+1] == 6)
            {
                landArray[ipos][jpos] = 6;
                i_perennials++;
                continue;
            }
            if ((jpos+1) < ijmax && landArray[ipos][jpos+1] == 6)
            {
                landArray[ipos][jpos] = 6;
                i_perennials++;
                continue;
            }
            if ((ipos-1) >= 0 && (jpos+1) < ijmax && landArray[ipos-1][jpos+1] == 6)
            {
                landArray[ipos][jpos] = 6;
                i_perennials++;
                continue;
            }
            if ((ipos-1) >= 0 && landArray[ipos-1][jpos] == 6)
            {
                landArray[ipos][jpos] = 6;
                i_perennials++;
                continue;
            }
            if ((ipos-1) >= 0 && (jpos-1) >= 0 && landArray[ipos-1][jpos-1] == 6)
            {
                landArray[ipos][jpos] = 6;
                i_perennials++;
                continue;
            }
        }

        if (landArray[ipos][jpos] == 0)
        {
            if (aggregate > aggregation_perennials)
            {
                landArray[ipos][jpos] = 6;
                i_perennials++;
                continue;
            }
        }
    }

    /**std::cout << "perennials distributed. press to continue." << "\n";
    getch();**/

    /** Set and cluster randomly some% of the cells to 7 (shrubs): ***********************************/

    for (int i = 0; i < patchNum_shrubs; i++)
    {
        ipos = rand_int(0,ijmax);
        jpos = rand_int(0,ijmax);

        if (landArray[ipos][jpos] == 0)
        {
            landArray[ipos][jpos] = 7;
        }
        else
        {
            while (landArray[ipos][jpos] != 0)
            {
                ipos = rand_int(0,ijmax);
                jpos = rand_int(0,ijmax);
            }
            landArray[ipos][jpos] = 7;
        }
    }

    /**std::cout << "cluster-patches shrubs initialised. press to continue." << "\n";
    getch();**/

    int i_shrubs = 0;
    while (i_shrubs < (num_shrubs-patchNum_shrubs))
    {
        // std::cout << "i_shrubs" << i_shrubs << std::endl;
        ipos = rand_int(0,ijmax);
        jpos = rand_int(0,ijmax);
        int aggregate = rand_int(0,100);

        if (landArray[ipos][jpos] == 0)
        {
            if ((jpos-1) >= 0 && landArray[ipos][jpos-1] == 7)
            {
                landArray[ipos][jpos] = 7;
                i_shrubs++;
                continue; // continue jumps back to the beginning of the loop
            }
            if ((ipos+1) < ijmax && (jpos-1) >= 0 && landArray[ipos+1][jpos-1] == 7)
            {
                landArray[ipos][jpos] = 7;
                i_shrubs++;
                continue;
            }
            if ((ipos+1) < ijmax && landArray[ipos+1][jpos] == 7)
            {
                landArray[ipos][jpos] = 7;
                i_shrubs++;
                continue;
            }
            if ((ipos+1) < ijmax && (jpos+1) < ijmax && landArray[ipos+1][jpos+1] == 7)
            {
                landArray[ipos][jpos] = 7;
                i_shrubs++;
                continue;
            }
            if ((jpos+1) < ijmax && landArray[ipos][jpos+1] == 7)
            {
                landArray[ipos][jpos] = 7;
                i_shrubs++;
                continue;
            }
            if ((ipos-1) >= 0 && (jpos+1) < ijmax && landArray[ipos-1][jpos+1] == 7)
            {
                landArray[ipos][jpos] = 7;
                i_shrubs++;
                continue;
            }
            if ((ipos-1) >= 0 && landArray[ipos-1][jpos] == 7)
            {
                landArray[ipos][jpos] = 7;
                i_shrubs++;
                continue;
            }
            if ((ipos-1) >= 0 && (jpos-1) >= 0 && landArray[ipos-1][jpos-1] == 7)
            {
                landArray[ipos][jpos] = 7;
                i_shrubs++;
                continue;
            }
        }



        if (landArray[ipos][jpos] == 0)
        {

            if (aggregate > aggregation_shrubs)
            {
                landArray[ipos][jpos] = 7;
                i_shrubs++;
                continue;
            }
        }
    }

    /**std::cout << "shrubs distributed. press to continue." << "\n";
    getch();**/
//    std::cout << "landArray:" << std::endl;
//    for (int i = 0; i < ijmax; i++)
//    {
//        for (int j = 0; j < ijmax; j++)
//        {
//            std::cout << landArray[i][j] << ' ';
//        }
//        std::cout << "\n";
//    };
//    std::cout << "\n";

}

void Landscape::distributeVegParameters(const int ijmax, Parameters* vegParameters)
{
    int count = 0;

    for (int i=0; i<ijmax; i++)
    {
        for (int j=0; j<ijmax; j++)
        {
            //std::cout << "Inside vegGrid[" << i << "][" << j << "]" << std::endl;
                if (landArray[i][j] == 5 || landArray[i][j] == 6)
                {
                    grassCoverMIN = 0.5;
                    grassCoverMAX = 1;
                    shrubCoverMIN = 0;
                    shrubCoverMAX = 0.5;

                    grassCoverGrid.push_back(grassCoverMIN + static_cast <float> (rand() / (static_cast <float> (RAND_MAX/(grassCoverMAX - grassCoverMIN)))));
                    woParameterGridGrass.push_back(grassCoverGrid[count] * (vegParameters->woGrassMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->woGrassMAX - vegParameters->woGrassMIN)))));
                    deltaParameterGridGrass.push_back((vegParameters->deltaGrassMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->deltaGrassMAX - vegParameters->deltaGrassMIN)))));
                    sigmaParameterGridGrass.push_back((vegParameters->sigmaGrassMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->sigmaGrassMAX - vegParameters->sigmaGrassMIN)))));
                    hParameterGridGrass.push_back(vegParameters ->hGrass);
                    rhoPParameterGridGrass.push_back(vegParameters ->rhoPGrass);
                    MfParameterGridGrass.push_back(vegParameters->MfGrassMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->MfGrassMAX - vegParameters->MfGrassMIN))));
                    sTParameterGridGrass.push_back(vegParameters->sTGrass);
                    MxParameterGridGrass.push_back(vegParameters->MxGrass);
                    seParameterGridGrass.push_back(vegParameters->seGrass);

                    shrubCoverGrid.push_back(shrubCoverMIN + static_cast <float> (rand() / (static_cast <float> (RAND_MAX/(shrubCoverMAX - shrubCoverMIN)))));
                    woParameterGridShrubs.push_back(shrubCoverGrid[count] * (vegParameters->woShrubsMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->woShrubsMAX - vegParameters->woShrubsMIN)))));
                    deltaParameterGridShrubs.push_back((vegParameters->deltaShrubsMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->deltaShrubsMAX - vegParameters->deltaShrubsMIN)))));
                    sigmaParameterGridShrubs_branch.push_back((vegParameters->sigmaBranchMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->sigmaBranchMAX - vegParameters->sigmaBranchMIN)))));
                    sigmaParameterGridShrubs_stem.push_back((vegParameters->sigmaStemMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->sigmaStemMAX - vegParameters->sigmaStemMIN)))));
                    hParameterGridShrubs_branch.push_back(vegParameters->hBranch);
                    hParameterGridShrubs_stem.push_back(vegParameters->hStem);
                    rhoPParameterGridShrubs.push_back(vegParameters->rhoPShrubs);
                    MfParameterGridShrubs_branch.push_back(vegParameters->MfBranchMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->MfBranchMAX - vegParameters->MfBranchMIN))));
                    MfParameterGridShrubs_stem.push_back(vegParameters->MfStemMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->MfStemMAX - vegParameters->MfStemMIN))));
                    sTParameterGridShrubs.push_back(vegParameters->sTShrubs);
                    seParameterGridShrubs.push_back(vegParameters->seShrubs);
                    MxParameterGridShrubs.push_back(vegParameters->MxShrubs);


                }

                else if (landArray[i][j] == 7)
                {
                    grassCoverMIN = 0;
                    grassCoverMAX = 0.5;
                    shrubCoverMIN = 0.5;
                    shrubCoverMAX = 1;

                    grassCoverGrid.push_back(grassCoverMIN + static_cast <float> (rand() / (static_cast <float> (RAND_MAX/(grassCoverMAX - grassCoverMIN)))));
                    woParameterGridGrass.push_back(grassCoverGrid[count] * (vegParameters->woGrassMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->woGrassMAX - vegParameters->woGrassMIN)))));
                    deltaParameterGridGrass.push_back((vegParameters->deltaGrassMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->deltaGrassMAX - vegParameters->deltaGrassMIN)))));
                    sigmaParameterGridGrass.push_back((vegParameters->sigmaGrassMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->sigmaGrassMAX - vegParameters->sigmaGrassMIN)))));
                    hParameterGridGrass.push_back(vegParameters ->hGrass);
                    rhoPParameterGridGrass.push_back(vegParameters ->rhoPGrass);
                    MfParameterGridGrass.push_back(vegParameters->MfGrassMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->MfGrassMAX - vegParameters->MfGrassMIN))));
                    sTParameterGridGrass.push_back(vegParameters->sTGrass);
                    MxParameterGridGrass.push_back(vegParameters->MxGrass);
                    seParameterGridGrass.push_back(vegParameters->seGrass);

                    shrubCoverGrid.push_back(shrubCoverMIN + static_cast <float> (rand() / (static_cast <float> (RAND_MAX/(shrubCoverMAX - shrubCoverMIN)))));
                    woParameterGridShrubs.push_back(shrubCoverGrid[count] * (vegParameters->woShrubsMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->woShrubsMAX - vegParameters->woShrubsMIN)))));
                    deltaParameterGridShrubs.push_back((vegParameters->deltaShrubsMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->deltaShrubsMAX - vegParameters->deltaShrubsMIN)))));
                    sigmaParameterGridShrubs_branch.push_back((vegParameters->sigmaBranchMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->sigmaBranchMAX - vegParameters->sigmaBranchMIN)))));
                    sigmaParameterGridShrubs_stem.push_back((vegParameters->sigmaStemMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->sigmaStemMAX - vegParameters->sigmaStemMIN)))));
                    hParameterGridShrubs_branch.push_back(vegParameters->hBranch);
                    hParameterGridShrubs_stem.push_back(vegParameters->hStem);
                    rhoPParameterGridShrubs.push_back(vegParameters->rhoPShrubs);
                    MfParameterGridShrubs_branch.push_back(vegParameters->MfBranchMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->MfBranchMAX - vegParameters->MfBranchMIN))));
                    MfParameterGridShrubs_stem.push_back(vegParameters->MfStemMIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(vegParameters->MfStemMAX - vegParameters->MfStemMIN))));
                    sTParameterGridShrubs.push_back(vegParameters->sTShrubs);
                    seParameterGridShrubs.push_back(vegParameters->seShrubs);
                    MxParameterGridShrubs.push_back(vegParameters->MxShrubs);
                }

                else if (landArray[i][j] == 4)
                {
                    woParameterGridShrubs.push_back(0);
                    woParameterGridGrass.push_back(0);
                    deltaParameterGridShrubs.push_back(0);
                    deltaParameterGridGrass.push_back(0);
                    sigmaParameterGridShrubs_branch.push_back(0);
                    sigmaParameterGridShrubs_stem.push_back(0);
                    sigmaParameterGridGrass.push_back(0);
                    hParameterGridShrubs_branch.push_back(0);
                    hParameterGridShrubs_stem.push_back(0);
                    hParameterGridGrass.push_back(0);
                    rhoPParameterGridShrubs.push_back(0);
                    rhoPParameterGridGrass.push_back(0);
                    MfParameterGridShrubs_branch.push_back(0);
                    MfParameterGridShrubs_stem.push_back(0);
                    MfParameterGridGrass.push_back(0);
                    sTParameterGridShrubs.push_back(0);
                    sTParameterGridGrass.push_back(0);
                    seParameterGridShrubs.push_back(0);
                    seParameterGridGrass.push_back(0);
                    MxParameterGridShrubs.push_back(0);
                    MxParameterGridGrass.push_back(0);
                    grassCoverGrid.push_back(0);
                    shrubCoverGrid.push_back(0);
                }

                count++;

        }
    }

    // calculate biomass for different shrub size-classes using allometric equation from Hasen-Yusuf et al. (2013):

    count = 0;

    for (int i=0; i<ijmax; i++)
    {
        for (int j=0; j<ijmax; j++)
        {
            shrubCrownVolumeGrid.push_back(shrubCrownVolumeMIN + static_cast <float> (rand() / (static_cast <float> (RAND_MAX/(shrubCrownVolumeMAX - shrubCrownVolumeMIN)))));

            if (woParameterGridShrubs[counter] != 0)
            {
                shrubCircumferenceGrid.push_back(exp((log(woParameterGridShrubs[counter]) + 2.777 - 0.7503 * log(shrubCrownVolumeGrid[counter])) / 0.963));
            }
            else
            {
                shrubCircumferenceGrid.push_back(0);
            }


            shrubBranchyBiomassGrid.push_back(exp(-3.1639 + 0.9991 * log(shrubCircumferenceGrid[counter]) + 0.7625 * log(shrubCrownVolumeGrid[counter])));
            shrubStemBiomassGrid.push_back(exp(-3.596 + 0.7085 * log(shrubCircumferenceGrid[counter]) + 0.7463 * log(shrubCrownVolumeGrid[counter])));

            count++;

        }
    }


    //std::cout << "It worked till output! Press ENTER." << std::endl;
    //getch();
//    int ch = std::cin.get();

//    for (std::vector<float>::const_iterator i = woParameterGrid.begin(); i != woParameterGrid.end(); ++i)
//        std::cout << *i << ' ';
}

void Landscape::landArrayDelete(const int ijmax)
{
    for (int i=0; i<ijmax; i++)
    {
        delete[] landArray[i];
    }
    delete[] landArray;
}

void Landscape::writeLandArrayFile(const int ijmax)
{
    std::ofstream outfile ("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/landArray.txt");
    for (int i = 0; i < ijmax; i++)
    {
        for (int j = 0; j < ijmax; j++)
        {
            outfile << landArray[i][j] << ' ';
        }
        outfile << "\n";
    };
    outfile << "\n";
    outfile.close();

}


void Landscape::writeParameterFiles(const int ijmax)
{

    // Uni laptop:
    std::ofstream woParameterFileShrubs("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/woParameterFileShrubs.txt");
    std::ofstream deltaParameterFileShrubs("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/deltaParameterFileShrubs.txt");
    std::ofstream sigmaParameterFileShrubs_branch("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/sigmaParameterFileShrubs_branch.txt");
    std::ofstream sigmaParameterFileShrubs_stem("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/sigmaParameterFileShrubs_stem.txt");
    std::ofstream hParameterFileShrubs_branch("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/hParameterFileShrubs_branch.txt");
    std::ofstream hParameterFileShrubs_stem("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/hParameterFileShrubs_stem.txt");
    std::ofstream rhoPParameterFileShrubs("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/rhoPParameterFileShrubs.txt");
    std::ofstream MfParameterFileShrubs_branch("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/MfParameterFileShrubs_branch.txt");
    std::ofstream MfParameterFileShrubs_stem("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/MfParameterFileShrubs_stem.txt");
    std::ofstream sTParameterFileShrubs("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/sTParameterFileShrubs.txt");
    std::ofstream seParameterFileShrubs("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/seParameterFileShrubs.txt");
    std::ofstream MxParameterFileShrubs("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/MxParameterFileShrubs.txt");
    std::ofstream shrubCoverFile("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/shrubCoverFile.txt");
    std::ofstream CVFile("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/CVFile.txt");
    std::ofstream circumferenceFile("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/circumferenceFile.txt");
    std::ofstream stemBiomassFile("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/stemBiomassFile.txt");
    std::ofstream branchBiomassFile("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/branchBiomassFile.txt");




    std::ofstream woParameterFileGrass("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/woParameterFileGrass.txt");
    std::ofstream deltaParameterFileGrass("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/deltaParameterFileGrass.txt");
    std::ofstream sigmaParameterFileGrass("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/sigmaParameterFileGrass.txt");
    std::ofstream hParameterFileGrass("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/hParameterFileGrass.txt");
    std::ofstream rhoPParameterFileGrass("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/rhoPParameterFileGrass.txt");
    std::ofstream MfParameterFileGrass("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/MfParameterFileGrass.txt");
    std::ofstream sTParameterFileGrass("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/sTParameterFileGrass.txt");
    std::ofstream seParameterFileGrass("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/seParameterFileGrass.txt");
    std::ofstream MxParameterFileGrass("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/MxParameterFileGrass.txt");
    std::ofstream grassCoverFile("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/grassCoverFile.txt");


    int count = 0;

    for (int i=0; i<ijmax; i++)
    {
        for (int j=0; j<ijmax; j++)
        {
            woParameterFileGrass << "[" << i << "]" << "[" << j << "]:" << woParameterGridGrass[count] << "\n";
            deltaParameterFileGrass << "[" << i << "]" << "[" << j << "]:" << deltaParameterGridGrass[count] << "\n";
            sigmaParameterFileGrass << "[" << i << "]" << "[" << j << "]:" << sigmaParameterGridGrass[count] << "\n";
            hParameterFileGrass << "[" << i << "]" << "[" << j << "]:" << hParameterGridGrass[count] << "\n";
            rhoPParameterFileGrass << "[" << i << "]" << "[" << j << "]:" << rhoPParameterGridGrass[count] << "\n";
            MfParameterFileGrass << "[" << i << "]" << "[" << j << "]:" << MfParameterGridGrass[count] << "\n";
            sTParameterFileGrass << "[" << i << "]" << "[" << j << "]:" << sTParameterGridGrass[count] << "\n";
            seParameterFileGrass << "[" << i << "]" << "[" << j << "]:" << seParameterGridGrass[count] << "\n";
            MxParameterFileGrass << "[" << i << "]" << "[" << j << "]:" << MxParameterGridGrass[count] << "\n";
            grassCoverFile << "[" << i << "]" << "[" << j << "]:" << "\t" << grassCoverGrid[count] << "\n";

            woParameterFileShrubs << "[" << i << "]" << "[" << j << "]:" << woParameterGridShrubs[count] << "\n";
            deltaParameterFileShrubs << "[" << i << "]" << "[" << j << "]:" << deltaParameterGridShrubs[count] << "\n";
            sigmaParameterFileShrubs_branch << "[" << i << "]" << "[" << j << "]:" << sigmaParameterGridShrubs_branch[count] << "\n";
            sigmaParameterFileShrubs_stem << "[" << i << "]" << "[" << j << "]:" << sigmaParameterGridShrubs_stem[count] << "\n";
            hParameterFileShrubs_branch << "[" << i << "]" << "[" << j << "]:" << hParameterGridShrubs_branch[count] << "\n";
            hParameterFileShrubs_stem << "[" << i << "]" << "[" << j << "]:" << hParameterGridShrubs_stem[count] << "\n";
            rhoPParameterFileShrubs << "[" << i << "]" << "[" << j << "]:" << rhoPParameterGridShrubs[count] << "\n";
            MfParameterFileShrubs_branch << "[" << i << "]" << "[" << j << "]:" << MfParameterGridShrubs_branch[count] << "\n";
            MfParameterFileShrubs_stem << "[" << i << "]" << "[" << j << "]:" << MfParameterGridShrubs_stem[count] << "\n";
            sTParameterFileShrubs << "[" << i << "]" << "[" << j << "]:" << sTParameterGridShrubs[count] << "\n";
            seParameterFileShrubs << "[" << i << "]" << "[" << j << "]:" << seParameterGridShrubs[count] << "\n";
            MxParameterFileShrubs << "[" << i << "]" << "[" << j << "]:" << MxParameterGridShrubs[count] << "\n";
            shrubCoverFile << "[" << i << "]" << "[" << j << "]:" << "\t" << shrubCoverGrid[count] << "\n";
            CVFile << "[" << i << "]" << "[" << j << "]:" << "\t" << shrubCrownVolumeGrid[count] << "\n";
            circumferenceFile << "[" << i << "]" << "[" << j << "]:" << "\t" << shrubCircumferenceGrid[count] << "\n";
            stemBiomassFile << "[" << i << "]" << "[" << j << "]:" << "\t" << shrubStemBiomassGrid[count] << "\n";
            branchBiomassFile << "[" << i << "]" << "[" << j << "]:" << "\t" << shrubBranchyBiomassGrid[count] << "\n";


            count++;
        }
    }
    woParameterFileGrass.close();
    deltaParameterFileGrass.close();
    sigmaParameterFileGrass.close();
    hParameterFileGrass.close();
    rhoPParameterFileGrass.close();
    MfParameterFileGrass.close();
    sTParameterFileGrass.close();
    seParameterFileGrass.close();
    MxParameterFileGrass.close();
    grassCoverFile.close();


    woParameterFileShrubs.close();
    deltaParameterFileShrubs.close();
    sigmaParameterFileShrubs_branch.close();
    sigmaParameterFileShrubs_stem.close();
    hParameterFileShrubs_branch.close();
    hParameterFileShrubs_stem.close();
    rhoPParameterFileShrubs.close();
    MfParameterFileShrubs_branch.close();
    MfParameterFileShrubs_stem.close();
    sTParameterFileShrubs.close();
    seParameterFileShrubs.close();
    MxParameterFileShrubs.close();
    shrubCoverFile.close();
    CVFile.close();
    circumferenceFile.close();
    stemBiomassFile.close();
    branchBiomassFile.close();
}
