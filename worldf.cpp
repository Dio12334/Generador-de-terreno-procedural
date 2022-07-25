#include "worldf.h"
#include "mapfunctions.h"

World::World(): xSide(257), ySide(257), elevation(257,std::vector<double>(257,0)) {}

World::World(World::length x, World::length y): xSide(x), ySide(y), elevation(y, std::vector<double>(x, 0)) {}

void World::setInitialWorldValues(double iniSpr, double iniMin, double iniMax){
    initialSpread = iniSpr;
    initialMinimum = iniMin;
    initialMaximum = iniMax;
}

void World::generateWorld(){
    generateElevationMap(diamondSquare);
}
        
void World::printWorld(){
    //int i = 0, j = 0;
    const int ESPACIO = 2;
    for(auto row: elevation){
        for(auto elem: row){
            //if(elem <= 0 || river[i][j])
            //    std::cout<<" "<<std::setw(ESPACIO);
            if(elem <= 1)
                std::cout<<"."<<std::setw(ESPACIO);
            else if(elem <= 2 )
                std::cout<<"~"<<std::setw(ESPACIO);
            else if(elem <= 4)
                std::cout<<"^"<<std::setw(ESPACIO);
            else if(elem <= 6)
                std::cout<<"n"<<std::setw(ESPACIO);
            else if(elem <= 8)
                std::cout<<"ŋ"<<std::setw(ESPACIO);
            else if(elem > 8)
                std::cout<<"A"<<std::setw(ESPACIO); 
            //j++;
        }
        std::cout<<"\n";
        //i++;
        //j=0;

    }
}

void World::generateElevationMap(void (*generator)(std::vector<std::vector<double>>&, double, double , double , size_t)){
    generator(elevation, initialSpread, initialMinimum, initialMaximum, xSide);
}
