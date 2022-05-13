#ifndef MAPFUNCTIONS_H
#define MAPFUNCTIONS_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <deque>
#include "functions.h"

//" diamondSquare {{{1
template<typename T>
void diamondSquare(std::vector<std::vector<T>>& noise, T randomSpread, T min, T max, size_t side){
    if(noise[0][0] == 0.0)
        noise[0][0] = random_number(min, max);
    if(noise[0][side-1] == 0.0)
        noise[0][side-1] = random_number(min, max);
    if(noise[side-1][0] == 0.0)
        noise[side-1][0] = random_number(min, max);
    if(noise[side-1][side-1] == 0.0)
        noise[side-1][side-1] = random_number(min, max);
    
    int chunkSize = side-1;
    T spread = randomSpread;
    while(chunkSize > 1){
        int half = chunkSize/2;
        for(size_t i = 0; i < side-1; i+=chunkSize)
            for(size_t j = 0; j < side-1;j+=chunkSize)
                noise[i+half][j+half] = mean(noise[i][j],noise[i][j+chunkSize], noise[i+chunkSize][j], noise[i+chunkSize][j+chunkSize]) + random_number(-spread, spread);
        
        for(size_t i = 0; i < side;i+=half){
            for(size_t j = (i+half)%chunkSize; j < side-1;j+=chunkSize){
                T sum = 0;
                int count = 0;
                if(i!=0){
                    sum += noise[i-half][j];
                    count++;
                }
                if(j!=0){
                    sum += noise[i][j-half];
                    count++;
                }
                if(j!=side-1){
                    sum += noise[i][j+half];
                    count++;
                }
                if(i!=side-1){
                    sum +=noise[i+half][j];
                    count++;
                }
                noise[i][j] = sum/count + random_number(-spread, spread);
            }
        }
        chunkSize /=2;
        spread /= 2;       
    }

}

//" printMapValues {{{1
template<typename T>
void printMapValues(std::vector<std::vector<T>>& map){
    for(auto row: map){
        for(auto elem: row)
            std::cout<<elem<<std::setw(3);
        std::cout<<"\n";
    }

}

//" createBlankMap {{{1
template<typename T>
void createBlankMap(std::vector<std::vector<T>>& map, size_t side){
    if(map.empty()){
        std::vector<std::vector<T>> vec(side, std::vector<T>(side, 0));
        map = vec;
    }
    else if(map.size() != side || map[0].size() != side){
        std::vector<std::vector<T>> vec(side, std::vector<T>(side, 0));
        map = vec;
    }
    else{
        for(auto& row: map)
            for(auto& elem: row)
                elem = 0;
    }
}

//" withinBounds {{{1
template<typename T>
bool withinBounds(std::vector<std::vector<T>>& map, unsigned long long y, unsigned long long x){
    return (0 <= x && x <= map[0].size()-1) && (0 <= y && y <= map.size()-1);
}

//" handleNeighbors {{{1
template<typename T>
void handleNeighbors(std::vector<std::vector<T>>& map, std::vector<std::vector<bool>>& visitados, std::pair<size_t, size_t>& coords , std::deque<std::pair<size_t, size_t>>& deq){
    if(withinBounds(map, coords.first-1, coords.second)){
        if(!map[coords.first-1][coords.second] && !visitados[coords.first-1][coords.second]){
            deq.emplace_back(std::make_pair(coords.first-1, coords.second));
            visitados[coords.first-1][coords.second] = true;
        }
    }
    if(withinBounds(map, coords.first, coords.second-1)){
        if(!map[coords.first][coords.second-1] && !visitados[coords.first][coords.second-1]){
            deq.emplace_back(std::make_pair(coords.first, coords.second-1));
            visitados[coords.first][coords.second-1] = true;
        }
    }
    if(withinBounds(map, coords.first, coords.second+1)){
        if(!map[coords.first][coords.second+1] && !visitados[coords.first][coords.second+1]){
            deq.emplace_back(std::make_pair(coords.first, coords.second+1));
            visitados[coords.first][coords.second+1] = true;
        }
    }
    if(withinBounds(map, coords.first+1, coords.second)){
        if(!map[coords.first+1][coords.second] && !visitados[coords.first+1][coords.second]){
            deq.emplace_back(std::make_pair(coords.first+1, coords.second));
            visitados[coords.first+1][coords.second] = true;
        }
    }

}

//" lazyFloodFill {{{1
template<typename T>
void lazyFloodFill(std::vector<std::vector<T>>& map, T value, size_t x, size_t y, float chance, float decay){
    std::vector<std::vector<bool>> visitado(map.size(), std::vector<bool>(map[0].size(), false));
    std::deque<std::pair<size_t, size_t>> deq;
    deq.emplace_back(std::make_pair(y,x));
    while(!deq.empty()){
        std::pair<size_t, size_t> coords = deq.front();
        deq.pop_front();
        map[coords.first][coords.second] = value;
        if(chance >= random_int(1, 100)){
            handleNeighbors(map, visitado, coords, deq);
        }
        chance*=decay;
    }
}

//" createBlankMap {{{1
template<typename T, typename U>
void createBlankMap(std::vector<std::vector<T>>& map, const std::vector<std::vector<U>>& base){
    std::vector<std::vector<T>> vec(base.size(), std::vector<T>(base[0].size(), 0));
    if(!map.empty())
        map.clear();
    map = vec;
}

//" normalizeMap {{{1
template<typename T>
void normalizeMap(std::vector<std::vector<T>>& map, T min , T max){
    for(size_t i = 0; i < map[0].size(); i++)
        for(size_t j = 0; j < map.size(); j++)
            map[i][j] = (map[i][j] - min)/(max - min);
}

//" denormalizeMap {{{1
template<typename T>
void denormalizeMap(std::vector<std::vector<T>>& map, T min, T max){
    for(size_t i = 0; i < map[0].size(); i++)
        for(size_t j = 0; j < map.size(); j++)
            map[i][j] = map[i][j]*(max - min) + min;
}

#endif
