#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <vector>


class Parameters
{

public:
    Parameters();

    int get_gridSize();
    float get_cellSize();

    void vegparamFile_input();


    void writeGridSizeFile();
    void writeCellSizeFile();

    int xymax;
    float cellSize;

    float MfGrassMIN;
    float MfGrassMAX;
    float sigmaGrassMIN;
    float sigmaGrassMAX;
    float woGrassMIN;
    float woGrassMAX;
    float deltaGrassMIN;
    float deltaGrassMAX;
    float hGrass;
    float rhoPGrass;
    float MxGrass;
    float sTGrass;
    float seGrass;


    float MfStemMIN;
    float MfStemMAX;
    float sigmaStemMIN;
    float sigmaStemMAX;
    float deltaShrubsMIN;
    float deltaShrubsMAX;
    float hStem;
    float rhoPShrubs;
    float MxShrubs;
    float sTShrubs;
    float seShrubs;
    float woShrubsMIN;
    float woShrubsMAX;
    float MfBranchMIN;
    float MfBranchMAX;
    float sigmaBranchMIN;
    float sigmaBranchMAX;
    float hBranch;
    float CVMIN;
    float CVMAX;


    float grassParameters[13];
    float shrubParameters[13];

    float rhoP; // fuel particle density
    float h; // fuel heat content
    float sigma; // sav ratio
    float Mf; // Fuel moisture content
    float Mx; // fuel moisture of extinction
    float se; // fuel effective mineral content
    float wo; // ovendry fuel loading
    float sT; // fuel total mineral content
    float delta; // fuel depth

};

#endif // PARAMETERS_H
