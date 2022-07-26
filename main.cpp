#include "world.h"
#include <iostream>
#include "Display.h"


int main(){
	Display display;
	double dim = 513;
	if(display.initialize(dim))
		display.runLoop();
	display.shutdown();
    /* World world;*/
    /* unsigned long long height, width; */
    /* world.selectBiome(); */
    /* std::cin>>width>>height; */
    /* world.createWorld(width, height); */
    return 0;
}
