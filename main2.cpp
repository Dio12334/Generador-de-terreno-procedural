#include "worldf.h"

int main(){

    World world;
    world.setInitialWorldValues(5.5, 5.0, 6.0);
    world.generateWorld();
    world.printWorld();

    return 0;
}
