#include "world.h"
#include "functions.h"
#include <cmath>
#include <fstream>
#include <utility>
#include "mapfunctions.h"

//" public {{{1
//" selectBiome() {{{2
void World::selectBiome(){
    int i;
    std::cout<<"Select Biome: "<<std::endl
            <<"1) Ocean"<<std::endl
            <<"2) Mountains"<<std::endl
            <<"3) Desert"<<std::endl
            <<"4) Tundra"<<std::endl
            <<"5) Flooded Grassland"<<std::endl
            <<"6) Grassland"<<std::endl
            <<"7) Coastal Desert"<<std::endl
            <<"8) Continent"<<std::endl
            <<"9) Extreme "<<std::endl;
    std::cin>>i;
    switch (i) {
        case 1:
            iniMax = 0.5;
            iniMin = -10.0;
            iniSpread = 1;
            percentageOfLandNeeded = 0;
            percentageOfWaterNeeded = 80;
            biomeTemperature = 0.0;
            break;
        case 2:
            iniMax = 6.0;
            iniMin = 5.0;
            iniSpread = 5.5;
            percentageOfLandNeeded = 80;
            percentageOfWaterNeeded = 0;
            biomeTemperature = -3.0;
            break;
        case 3:
            iniMax = 1.0;
            iniMin = 0.0;
            iniSpread = 0.5;
            percentageOfLandNeeded = 90;
            percentageOfWaterNeeded = 0;
            biomeTemperature = 15.0;
            break;
        case 4:
            iniMax = 2.0;
            iniMin = 0;
            iniSpread = 0.5;
            percentageOfLandNeeded = 80;
            percentageOfWaterNeeded = 0;
            biomeTemperature = -15.0;
            break;
        case 5:
            iniMax = 1.0;
            iniMin = -1.0;
            iniSpread = 0.4;
            percentageOfLandNeeded = 50;
            percentageOfWaterNeeded = 40;
            biomeTemperature = 0.0;
            break;
        case 6:
            iniMax = 1.0;
            iniMin = 0.0;
            iniSpread = 0.5;
            percentageOfLandNeeded = 80;
            percentageOfWaterNeeded = 0;
            biomeTemperature = 0.0;
            break;
        case 7:
            iniMax = 1.0;
            iniMin = -1.0;
            iniSpread = 0.5;
            percentageOfLandNeeded = 40;
            percentageOfWaterNeeded = 30;
            biomeTemperature = 10.0;
            break;
        case 8:
            iniMax = 0.0;
            iniMin = 0.0;
            iniSpread = 8;
            percentageOfLandNeeded = 29;
            percentageOfWaterNeeded = 60;
            biomeTemperature = 0.0;
            break;
        case 9:
            iniMax = 10.0;
            iniMin = 0.0;
            iniSpread = 10;
            percentageOfLandNeeded = 0;
            percentageOfWaterNeeded = 0;
            biomeTemperature = 0;
            break;

    }
}
//" World() {{{2
World::World(){}
//" createWorld(width, height) {{{2
void World::createWorld(unsigned long long width, unsigned long long height){
    int n = std::ceil(log2(min(width, height)-1));    
    side = pow(2,n)+1;
    float land = -1.0, water = -1.0;
    int i = 1;
    while(land < percentageOfLandNeeded || water < percentageOfWaterNeeded){
        std::cout<<"intento "<<i++<<std::endl;
        water = land = -1.0;
        createBlankMap(elevation, side); 
        diamondSquare(elevation, iniSpread, iniMin, iniMax, side);
        expandElevationMap(width, height);
        getMinMaxElevation();
        //normalizeMap(elevation, minElevation, maxElevation);
        //denormalizeMap(elevation, minElevation, maxElevation);
        getLandPercentage(land, width, height);
        water = 100.0 - land;
    }
	normalizeMap(elevation, minElevation, maxElevation);
	Erode();
	denormalizeMap(elevation, minElevation, maxElevation);
    adjustElevationMapSize(width, height);
    createRiverMap();
    //printHeightMap();   
    std::cout<<"Land: "<<land<<"\%  Ocean: "<<100.0-land<<"\%\n"; 
    createTemperatureMap();
    createAPMap();
    getInformationOfWorld();
    std::cout<<"Max Elevation: "<<maxElevation<<" Min Temperature: "<<minTemperature<<" Min Elevation: "<<minElevation<<" Max Temperature: "<<maxTemperature<<std::endl;
    std::cout<< elevation[0].size()<<" "<<elevation.size()<<std::endl;
    //resourcesGeneration();
    std::cout<<sizeof(elevation)<<std::endl;
}     
//" printHeightMap() {{{2
void World::printHeightMap(){
    int i = 0, j = 0;
    const int espacio = 1;
    for(auto row: elevation){
        for(auto elem: row){
            if(elem <= 0 || river[i][j])
                std::cout<<" "<<std::setw(espacio);
            else if(elem <= 1)
                std::cout<<"."<<std::setw(espacio);
            else if(elem <= 2 )
                std::cout<<"~"<<std::setw(espacio);
            else if(elem <= 4)
                std::cout<<"^"<<std::setw(espacio);
            else if(elem <= 6)
                std::cout<<"n"<<std::setw(espacio);
            else if(elem <= 8)
                std::cout<<"ŋ"<<std::setw(espacio);
            else if(elem > 8)
                std::cout<<"A"<<std::setw(espacio); 
            j++;
        }
        std::cout<<"\n";
        i++;
        j=0;
    }
}   
//" ~World() {{{2
World::~ World(){}      

// draw(renderer) {{{2
void World::draw(SDL_Renderer* renderer){
	for(std::size_t j = 0; j < elevation.size(); ++j){
		for(std::size_t i = 0; i < elevation[0].size(); ++i){
			/* if(elevation[j][i] > 0 && !river[j][i]){ */
			/* 	SDL_SetRenderDrawColor(renderer, 255*((temperature[j][i] <= 0)? 1:(elevation[j][i]/maxElevation)), 139, 255*((temperature[j][i] <= 0)? 1:(elevation[j][i]/maxElevation)), 255); */
			/* } */
			/* else{ */
			/* 	SDL_SetRenderDrawColor(renderer,  0, 0, 255*(1 - elevation[j][i]/minElevation), 255); */
			/* 	if(river[j][i]) */
			/* 		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); */
			/* } */
			if(river[j][i]){
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			}
			else if(elevation[j][i] < -3){
				SDL_SetRenderDrawColor(renderer, 0, 0, 30, 255);
			}
			else if(elevation[j][i] < -2){
				SDL_SetRenderDrawColor(renderer, 0, 0, 130, 255);
			}
			else if(elevation[j][i] < -1){
				SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255);
			}
			else if(elevation[j][i] < 0){
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			}
			else if(elevation[j][i] < 1){
				SDL_SetRenderDrawColor(renderer, 220, 226, 198, 255);
			}
			else if(elevation[j][i] < 3){
				SDL_SetRenderDrawColor(renderer, 0, 139, 0, 255);
			}
			else if(elevation[j][i] < 5){
				SDL_SetRenderDrawColor(renderer, 139, 139, 139, 255);
			}
			else{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
			SDL_RenderDrawPoint(renderer, i , j);
		}
	}
}

//" private {{{1  
//" getLandPercentage(land, width , height) {{{2
/*Gives the variable land the percentage of land that exists on the map*/
void World::getLandPercentage(float& land, unsigned long long width, unsigned long long height){
    for(decltype(height) i = 0; i < height; i++)
        for(decltype(width) j = 0; j < width; j++)
            if(elevation[i][j] > 0)
                land++;
    land = 100.0*(land/(width* height* 1.0 ));
}
//" createTemperatureMap() {{{2
/*Creates the temperature map based on the elevation map*/
void World::createTemperatureMap(){
    for(auto row: elevation){
        std::vector<int> temp;
        for(auto elem: row ){
            int tem = (elem >= 0.0)? (288.15-0.0065*(1000*elem))-273.15 + biomeTemperature:15 + biomeTemperature;
            temp.emplace_back(tem);
        }
        temperature.emplace_back(temp);
        temp.clear();
    }
 } 
//" getMinMaxElevation() {{{2
/*assigns the min and max elevation values*/
void World::getMinMaxElevation(){
    maxElevation = -10000, minElevation = 10000;
    for(decltype(elevation.size()) i = 0; i < elevation.size(); i++)
        for(decltype(elevation[0].size()) j = 0; j < elevation[0].size(); j++){
            if(elevation[i][j] > maxElevation){
                maxElevation = elevation[i][j];
            }
            if(elevation[i][j] < minElevation){
                minElevation = elevation[i][j];
            }
        } 
}
//" expandElevationMap(width, height) {{{2 
/*expands the elevation map to surpass or be equal to the max(width, height)*/
void World::expandElevationMap(unsigned long long width, unsigned long long height){
    if(width <= side && height > side){
        int i = std::ceil((height - side)/((side-1)*1.0));
        for(int j = 0; j < i; j++)
            yElevationExpansion();
    }
    if(height <= side && width > side){
        int i = std::ceil((width - side)/((side-1)*1.0));
        for(int j = 0; j < i; j++)
            xElevationExpansion();
    }
} 
//" adjustElevationMapSize(width, height) {{{2
/*Eliminate the excess of the elevation map*/
void World::adjustElevationMapSize(unsigned long long width, unsigned long long height){
        unsigned long long cutY = elevation.size() - height, cutX = elevation[0].size() - width;
        for(unsigned long long  i = 0; i < cutY; i++)
            elevation.pop_back();
        for(auto& row : elevation)
            for(unsigned long long i = 0; i < cutX; i++)
                row.pop_back();
} 
//" yElevationExpansion() {{{2
/*Expands on the y axis side-1 rows*/
void World::yElevationExpansion(){
    std::vector<std::vector<float>> extra;
    createBlankMap(extra,side);
    extra[0] = elevation.back();
    diamondSquare(extra, iniSpread, iniMin, iniMax, side);
    for(auto row: extra)
        elevation.emplace_back(row);
} 
//" xElevationExpansion() {{{2
/*Expands on the x axis side-1 columns*/
void World::xElevationExpansion(){
    std::vector<std::vector<float>> extra;
    createBlankMap(extra, side);
    for(decltype(elevation.size()) i = 0; i < elevation.size(); i++)
        extra[i][0] = elevation[i].back();
    diamondSquare(extra, iniSpread, iniMin, iniMax, side);
    for(decltype(elevation.size()) i = 0; i < elevation.size(); i++)
        elevation[i].insert(elevation[i].end(), extra[i].begin(), extra[i].end());
}
//" surfaceNormal(i, j) {{{2 
/* creates the normal of the surface*/
glm::vec3 World::surfaceNormal(int i, int j){
    float scale = 60.0;
	glm::vec3 n = glm::vec3(0.15) * glm::normalize(glm::vec3(scale*(elevation[i][j]-elevation[i+1][j]), 1.0, 0.0));  //Positive X
	n += glm::vec3(0.15) * glm::normalize(glm::vec3(scale*(elevation[i-1][j]-elevation[i][j]), 1.0, 0.0));  //Negative X
	n += glm::vec3(0.15) * glm::normalize(glm::vec3(0.0, 1.0, scale*(elevation[i][j]-elevation[i][j+1])));    //Positive Y
	n += glm::vec3(0.15) * glm::normalize(glm::vec3(0.0, 1.0, scale*(elevation[i][j-1]-elevation[i][j])));  //Negative Y

	//Diagonals! (This removes the last spatial artifacts)
	n += glm::vec3(0.1) * glm::normalize(glm::vec3(scale*(elevation[i][j]-elevation[i+1][j+1])/sqrt(2), sqrt(2), scale*(elevation[i][j]-elevation[i+1][j+1])/sqrt(2)));    //Positive Y
	n += glm::vec3(0.1) * glm::normalize(glm::vec3(scale*(elevation[i][j]-elevation[i+1][j-1])/sqrt(2), sqrt(2), scale*(elevation[i][j]-elevation[i+1][j-1])/sqrt(2)));    //Positive Y
	n += glm::vec3(0.1) * glm::normalize(glm::vec3(scale*(elevation[i][j]-elevation[i-1][j+1])/sqrt(2), sqrt(2), scale*(elevation[i][j]-elevation[i-1][j+1])/sqrt(2)));    //Positive Y
	n += glm::vec3(0.1) * glm::normalize(glm::vec3(scale*(elevation[i][j]-elevation[i-1][j-1])/sqrt(2), sqrt(2), scale*(elevation[i][j]-elevation[i-1][j-1])/sqrt(2)));    //Positive Y

	return n;


}

Math::Vector<double> World::surfaceNormal(std::size_t i, std::size_t j){
	using Math::Vector;
	const double SQRT2 = 1.41421; 
	double scale = 60.0;
	Vector<double> n = Vector<double>(0.15, 0.15, 0.15) * Math::normalize(Vector<double>(scale*(elevation[i][j] - elevation[i+1][j]), 1.0, 0.0));
	n += Vector<double>(0.15, 0.15, 0.15) * Math::normalize(Vector<double>(scale*(elevation[i-1][j] - elevation[i][j]), 1.0, 0.0)); 
	n += Vector<double>(0.15, 0.15, 0.15) * Math::normalize(Vector<double>(0.0, 1.0, scale*(elevation[i][j] - elevation[i][j+1])));
	n += Vector<double>(0.15, 0.15, 0.15) * Math::normalize(Vector<double>(0.0, 1.0, scale*(elevation[i][j-1] - elevation[i+1][j])));
	
	n += Vector<double>(0.1, 0.1, 0.1) * Math::normalize(Vector<double>(scale*(elevation[i][j] - elevation[i+1][j+1])/SQRT2, SQRT2, scale*(elevation[i][j] - elevation[i+1][j+1])/SQRT2));
	n += Vector<double>(0.1, 0.1, 0.1) * Math::normalize(Vector<double>(scale*(elevation[i][j] - elevation[i+1][j-1])/SQRT2, SQRT2, scale*(elevation[i][j] - elevation[i+1][j-1])/SQRT2));
	n += Vector<double>(0.1, 0.1, 0.1) * Math::normalize(Vector<double>(scale*(elevation[i][j] - elevation[i-1][j+1])/SQRT2, SQRT2, scale*(elevation[i][j] - elevation[i-1][j+1])/SQRT2));
	n += Vector<double>(0.1, 0.1, 0.1) * Math::normalize(Vector<double>(scale*(elevation[i][j] - elevation[i-1][j-1])/SQRT2, SQRT2, scale*(elevation[i][j] - elevation[i-1][j-1])/SQRT2));

	return n;

}
//" Erode(){{{2
/*Erodes the elevation map with hydraulic erosion */
void World::Erode(){
	using Math::Vector;
    float minVol = 0.01f, friction = 0.05f, depositionRate = 0.1f, density = 1.0f, dt = 1.2f, evapRate = 0.01f;
    int cycles = 200000; 

    Vector<std::size_t> dim(side-1,side-1);
  /*
    Note: Everything is properly scaled by a time step-size "dt"
  */

  //Do a series of iterations! (5 Particles)
  for(int i = 0; i < cycles; i++){

    //Spawn New Particle
    Vector<std::size_t> newpos(random_int(1,elevation[0].size()-2), random_int(1,elevation.size()-2));
    Particle drop(newpos);

    //As long as the droplet exists...
    while(drop.volume > minVol){
		Vector<std::size_t> ipos = drop.position;                   //Floored Droplet Initial Position
		Vector<double> n = surfaceNormal(ipos.x, ipos.y);  //Surface Normal at Position
		/* glm::vec3 n2 = surfaceNormal((int)ipos.y, (int)ipos.x); */
		/* std::cout << n << "\n"; */ 
		/* std::cout << n2.x << " " << n2.y << " " << n2.z << "\n"; */

		//Accelerate particle using newtonian mechanics using the surface normal.
		drop.speed += dt*Vector<double>(n.x, n.z)/(drop.volume*density);//F = ma, so a = F/m
		drop.position += dt*drop.speed;
		drop.speed *= (1.0-dt*friction);       //Friction Factor

		/*
			Note: For multiplied factors (e.g. friction, evaporation)
			time-scaling is correctly implemented like above.
		*/

		//Check if Particle is still in-bounds
		if(!(drop.position.x >= 1 && drop.position.y >= 1) || !(drop.position.x < dim.x && drop.position.y < dim.y))
			break;

      //Compute sediment capacity difference
      double maxsediment = drop.volume*drop.speed.length()*(elevation[ipos.x][ipos.y]-elevation[(int)drop.position.x][(int)drop.position.y]);
      if(maxsediment < 0.0) maxsediment = 0.0;
      float sdiff = maxsediment - drop.sediment;

      //Act on the Heightmap and Droplet!
      drop.sediment += dt*depositionRate*sdiff;
      elevation[ipos.x][ipos.y] -= dt*drop.volume*depositionRate*sdiff;

      //Evaporate the Droplet (Note: Proportional to Volume! Better: Use shape factor to make proportional to the area instead.)
      drop.volume *= (1.0-dt*evapRate);
    }
  }
}  
//" getInformationOfWorld() {{{2
/*assignd each information variable with its respective value*/
void World::getInformationOfWorld(){
    maxElevation = -10000, minElevation = 10000;
    for(decltype(elevation.size()) i = 0; i < elevation.size(); i++)
        for(decltype(elevation[0].size()) j = 0; j < elevation[0].size(); j++){
            if(elevation[i][j] > maxElevation){
                maxElevation = elevation[i][j];
                minTemperature = temperature[i][j];
            }
            if(elevation[i][j] < minElevation){
                minElevation = elevation[i][j];
                maxTemperature = temperature[i][j];
            }
        }
} 
//" saveWorld() {{{2
/* Save world data*/
void World::saveWorld(){
    
}
//" loadWorld() {{{2
/*Loads world data*/
void World::loadWorld(){

}
//" resourcesGeneration() {{{2
/*Generate the resources map with the lazyFloodFill algorithm*/
void World::resourcesGeneration(){
    createBlankMap(resources, elevation);
    for(int i = 0; i < 30; i++){
        short j = i%10;
        lazyFloodFill(resources, j, random_int(0, resources[0].size()-1), random_int(0, resources.size()-1), 100, 0.9975);
    }
    printResources();
}

//" printResources() {{{2
/*Prints the map of resources*/
void World::printResources(){
    for(auto row: resources){
        for(auto elem: row){
            if(elem == 0)
                std::cout<<" "<<std::setw(1);
            else
                std::cout<<elem<<std::setw(1);
        }
        std::cout<<std::endl;
    }
}

//" createAPMap() {{{2
/*creates atomspheric pressure map*/
void World::createAPMap(){
    for(auto row: elevation){
        std::vector<float> ap;
        for(auto elem: row ){
            int api = (elem > 0)? 101325*pow((1-((0.00976*elem*1000)/288.16)),((9.80665*0.02896968)/(8.314462618*0.00976))):101325.0F;
            ap.emplace_back(api);
        }
        atmospheric_pressure.emplace_back(ap);
        ap.clear();
    }

}
//" creat eRiverMap () {{{2 
/*Creates de river map*/
void World::createRiverMap(){
    
    /*float minVol = 0.01f, friction = 0.05f, depositionRate = 0.1f, density = 1.0f, dt = 0.25f, evapRate = 0.001f;
    std::vector<std::vector<bool>> mat(elevation.size(), std::vector<bool>(elevation[0].size(), false));
    river = mat;
    for(int i = 0; i < 5; i++){
        glm::vec2 newpos(random_int(1,elevation[0].size()-2),random_int(1, elevation.size()-2));
        Particle drop(newpos);
        //std::cout<<"------New drop------"<<std::endl;
        while(drop.volume > minVol){
            glm::ivec2 ipos = drop.pos;
            //std::cout<<(int)drop.pos.x<<" "<<(int) drop.pos.y<<std::endl;
            river[ipos.x][ipos.y] = true;
            std::cout<<elevation[ipos.y-1][ipos.x]<<std::endl<<elevation[ipos.y][ipos.x-1]<<" "<<elevation[ipos.y][ipos.x]<<" "<<elevation[ipos.y][ipos.x+1]<<std::endl<<elevation[ipos.y+1][ipos.x]<<std::endl;
            glm::vec3 n = surfaceNormal(ipos.x, ipos.y);
            std::cout<<"normal: "<<n.x<<" "<<n.y<<" "<<n.z<<std::endl;
            if(n.z == 1)
                break;
            drop.speed += glm::vec2(n.x,n.z)*(dt/(drop.volume*density));
            std::cout<<"speed: "<<drop.speed.x<<" "<<drop.speed.y<<std::endl;
            drop.pos += drop.speed*dt;
            drop.speed *= (1.0f-dt*friction);

            if(drop.pos.x < 1 || drop.pos.y < 1 ||  drop.pos.x >= elevation[0].size()-1|| drop.pos.y >= elevation.size()-1) 
                break;

            float maxsediment = drop.volume*glm::length(drop.speed)*(elevation[ipos.x][ipos.y]-elevation[(int)drop.pos.x][(int)drop.pos.y]);
            if(maxsediment < 0.0) maxsediment = 0.0f;
            float sdiff = maxsediment - drop.sediment;
            drop.sediment += dt*depositionRate*sdiff;
            elevation[ipos.x][ipos.y] -= dt*drop.volume*depositionRate*sdiff;
            drop.volume *= (1.0-dt*evapRate);
        }
    }*/

	using Math::Vector;
     std::vector<std::vector<bool>> mat(elevation.size(), std::vector<bool>(elevation[0].size(), false));
    river = mat;
   for(int i = 0; i < 30; i++){
       Vector<std::size_t> riv(random_int(1,elevation[0].size()-2),random_int(1, elevation.size()-2));
       //std::cout<<"---nuevo rio---"<<std::endl;
       //std::cout<<riv.x<<" "<<riv.y<<std::endl;
        while(riv.x < elevation[0].size()-1 && riv.x > 0 && riv.y < elevation.size()-1 && riv.y > 0 && elevation[riv.y][riv.x] > 0 && !river[riv.y][riv.x]){
            //std::cout<<riv.x<<" "<<riv.y<<std::endl;
            river[riv.y][riv.x] = true;
            float mini = 100;
            mini = (river[riv.y-1][riv.x])? mini:min(mini,elevation[riv.y-1][riv.x]);
            mini = (river[riv.y+1][riv.x])? mini:min(mini,elevation[riv.y+1][riv.x]);
            mini = (river[riv.y][riv.x-1])? mini:min(mini,elevation[riv.y][riv.x-1]);
            mini = (river[riv.y][riv.x+1])? mini:min(mini,elevation[riv.y][riv.x+1]);
            if(elevation[riv.y-1][riv.x] == mini){
                riv.y--;
            }
            else if(elevation[riv.y+1][riv.x] == mini){
                riv.y++;
            }
            else if(elevation[riv.y][riv.x-1] == mini){
                riv.x--;
            }
            else{
                riv.x++;
            }

        }
        river[riv.y][riv.x] = true;
   }
}

