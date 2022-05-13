#include "world.h"
#include <iostream>

int main(){
    World world;
    unsigned long long height, width;
    world.selectBiome();
    std::cin>>width>>height;
    world.createWorld(width, height);
    return 0;
}
