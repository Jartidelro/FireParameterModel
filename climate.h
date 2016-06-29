#ifndef CLIMATE_H
#define CLIMATE_H

class Climate
{
public:
    // Constructor
    Climate();
    // Destructor
    ~Climate();

    void chooseSeason();
    void writeSeasonFile();
    int getSeason();
    int rand_int(int from, int to);

private:
    int season;
};

#endif // CLIMATE_H
