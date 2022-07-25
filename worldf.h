#ifndef WORLDF_H
#define WORLDF_H

#include <vector>

class World{
    public:
        typedef size_t length;
        World();
        World(length x, length y);
        void setInitialWorldValues(double iniSpr, double iniMin, double iniMax);
        void generateWorld();
        void printWorld();

    private:
        
        length xSide, ySide;
        std::vector<std::vector<double>> elevation;
        double initialSpread, initialMinimum, initialMaximum;
        
        void generateElevationMap(void (*generator)(std::vector<std::vector<double>>&, double , double,  double, size_t));
};

#endif

