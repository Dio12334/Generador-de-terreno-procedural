#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <SDL2/SDL.h>
#include "vectors.h"
#include <glm/glm.hpp>

class World{
    public:
        World();
        void selectBiome();
        void createWorld(unsigned long long width=513, unsigned long long height=513);
        void printHeightMap();
		void draw(SDL_Renderer* renderer);
        ~World();
    private:
        // Maps
        std::vector<std::vector<float>> elevation;
        std::vector<std::vector<int>> temperature;
        std::vector<std::vector<short>> resources;
        std::vector<std::vector<float>> atmospheric_pressure;
        std::vector<std::vector<bool>> river;

        // Related variables
        unsigned long long side;
        float maxElevation, minElevation;
        int maxTemperature, minTemperature, biomeTemperature;
        float iniMax, iniMin, iniSpread;
        float percentageOfLandNeeded, percentageOfWaterNeeded;

        // General functions
        void getInformationOfWorld();
        void getMinMaxElevation();
        void saveWorld();
        void loadWorld();
 
        // Elevation related functions
        void getLandPercentage(float& land, unsigned long long width, unsigned long long height);
        void expandElevationMap(unsigned long long width, unsigned long long height);
        void adjustElevationMapSize(unsigned long long width, unsigned long long height);
        void yElevationExpansion();
        void xElevationExpansion();
        glm::vec3 surfaceNormal(int i, int j);
        void Erode();

        // Temperature related functions
        void createTemperatureMap();

        // Resources related functions
        void resourcesGeneration();
        void printResources();

        // atmospheric_pressure related functions
        void createAPMap();

        //river related map
        void createRiverMap();
};

struct Particle{
/*  Vector2 pos;
  Vector2 speed;
  float volume = 1.0f;
  float sediment = 0.0f;

  Particle(Vector2 pos){
    this->pos.x = pos.x;
    this->pos.y = pos.y;
  }*/
 Particle(glm::vec2 _pos){ pos = _pos; }

  glm::vec2 pos;
  glm::vec2 speed = glm::vec2(0.0);

  float volume = 1.0;   //This will vary in time
  float sediment = 0.0; //Fraction of Volume that is Sediment!
};

#endif
