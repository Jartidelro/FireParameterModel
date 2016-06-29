#include "climate.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <random>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */


//Constructor
Climate::Climate()
{
   //season =1;
}

//Destructor
Climate::~Climate()
{

}

int Climate::rand_int(int from, int to)
{
    /*std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(from, to);
    //std::cout << "Random number!! " << distr(gen) << std::endl;
    return distr(gen);*/

    int help = to-from;
    int i2 = rand() % help;
    i2 += from;
    return i2;
}

void Climate::chooseSeason()
{
    // Choose a season randomly:
    // 1 = early wet
    // 2 = late wet
    // 3 = early dry
    // 4 = late dry

    season = rand_int(1,5);
    std::cout << "Season: " << season << std::endl;

}

int Climate::getSeason()
{
    return season;
}

void Climate::writeSeasonFile()
{
    std::ofstream outfile ("C:/Users/Student/Desktop/Jarro/Master/Programming/Parameter_input/Season.txt"); // uni laptop
    //std::ofstream outfile ("/home/jarro/ownCloud/Master/Programming/Parameter_input/Season.txt");
    outfile << season;
    outfile.close();
}

