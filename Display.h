#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <iostream>
#include "world.h"

class Display{

    public:

        Display();
        bool initialize(double dim);
        void runLoop();
        void shutdown();

    private:

        void processInputs();
        void updateDisplay();
        void generateOutput(); 
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;
        int screenSize;
		World mundo;
		std::size_t ticksCount;

};


int random(int low, int high);

#endif

