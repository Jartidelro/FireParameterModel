#ifndef LANDSCAPE_H
#define LANDSCAPE_H
#include "climate.h"
#include "parameters.h"
#include "vegetation.h"
#include <vector>


class Landscape
{
public:
    // Constructor
    Landscape(const int ijmax);
    // Destructor
    ~Landscape();


    // Initialise the vegetation object array:

    int rand_int(int from, int to);
    float rand_float(float from, float to);
    void initialise(const int ijmax);
    void landArrayDelete(const int ijmax);
    void distributeVegParameters(const int ijmax, Parameters *vegParameters);
    void vegGridDelete(const int ijmax);
    void writeLandArrayFile(const int ijmax);
    void writeParameterFiles(const int ijmax);




    // Dynamic arrays:
    // I want to be able to let the user decide what the grid size of the model is going to be, meaning that I cant use static arrays
    // as in that case the array size has to be defined beforhand

//    int landArray[ijmax][ijmax];


    // These have to be public so output.cpp can access them...
    int num_vegfree; // set the values up in the constructor!
    int num_annuals;
    int num_perennials;
    int num_shrubs;

    int** landArray;

    float grassCoverMIN;
    float grassCoverMAX;
    float shrubCoverMIN;
    float shrubCoverMAX;

    std::vector<float>rhoPParameterGridGrass;
    std::vector<float>hParameterGridGrass;
    std::vector<float>sigmaParameterGridGrass;
    std::vector<float>MfParameterGridGrass;
    std::vector<float>MxParameterGridGrass;
    std::vector<float>seParameterGridGrass;
    std::vector<float>woParameterGridGrass;
    std::vector<float>sTParameterGridGrass;
    std::vector<float>deltaParameterGridGrass;
    std::vector<float>grassCoverGrid;

    std::vector<float>rhoPParameterGridShrubs;
    std::vector<float>hParameterGridShrubs_stem;
    std::vector<float>hParameterGridShrubs_branch;
    std::vector<float>sigmaParameterGridShrubs_stem;
    std::vector<float>sigmaParameterGridShrubs_branch;
    std::vector<float>MfParameterGridShrubs_stem;
    std::vector<float>MfParameterGridShrubs_branch;
    std::vector<float>MxParameterGridShrubs;
    std::vector<float>seParameterGridShrubs;
    std::vector<float>woParameterGridShrubs;
    std::vector<float>sTParameterGridShrubs;
    std::vector<float>deltaParameterGridShrubs;
    std::vector<float>shrubCoverGrid;

    std::vector<float>woParameterGrid;
    std::vector<float>deltaParameterGrid;
    std::vector<float>hParameterGrid;
    std::vector<float>sTParameterGrid;
    std::vector<float>seParameterGrid;
    std::vector<float>MxParameterGrid;

    std::vector<float>shrubStemBiomassGrid;
    std::vector<float>shrubBranchyBiomassGrid;
    float shrubCrownVolumeMIN;
    float shrubCrownVolumeMAX;
    std::vector<float>shrubCrownVolumeGrid;
    std::vector<float>shrubCircumferenceGrid;

 private:

    float aggregation_annuals;
    float aggregation_perennials;
    float aggregation_shrubs;
    int patchNum_annuals;
    int patchNum_perennials;
    int patchNum_shrubs;

    double fuel_moisture;
    double biomass;

};

#endif // LANDSCAPE_H
