#include "Display.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <algorithm>

Display::Display(): isRunning(false), window(nullptr), renderer(nullptr), ticksCount(0){}

bool Display::initialize(double dim){

    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if(sdlResult != 0){
        SDL_Log("No se pudo inicializar SDL: %s", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("WorldGen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dim, dim,0);
    if(!window){
        SDL_Log("Falla en la creación de la ventana: %s", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    isRunning = true;
    
    screenSize = dim;
	mundo.selectBiome();
	mundo.createWorld(screenSize, screenSize);
    return true;
}

void Display::runLoop(){
    while(isRunning){
        // std::cout<<"input\n";
        processInputs();
        // std::cout<<"diplay\n";
        updateDisplay();
         //std::cout<<"out\n";s
        generateOutput();
    }
}

void Display::shutdown(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Display::processInputs(){
    SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				isRunning = false;
				break;
		}
	}
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_ESCAPE])
        isRunning = false; 
	else if(state[SDL_SCANCODE_A]){
		mundo.selectBiome();
		mundo.createWorld(screenSize, screenSize);				
	}
}

void Display::updateDisplay(){
	
	while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

	ticksCount = SDL_GetTicks();
}

void Display::generateOutput(){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
	mundo.draw(renderer);
	SDL_RenderPresent(renderer);
}
