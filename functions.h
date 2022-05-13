#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <random>

typedef std::random_device device;
typedef std::uniform_real_distribution<float> distribution;

float random_number(float low, float high);


typedef std::uniform_int_distribution<int> intDistribution;
int random_int(int low, int high);

template<typename T>
T min(T first){
    return first;
}

template<typename T, typename... Params>
T min(T first, Params... args){
    T recMin = min(args...);
    return (first < recMin)? first:recMin;
}

template<typename T>
T max(T first){
    return first;
}

template<typename T, typename... Params>
T max(T first, Params... args){
    T recMax = max(args...);
    return (first > recMax)? first:recMax;
}

template <typename T>
T sum(T first_arg) {
    return first_arg;
}

template <typename T, typename... Types>
T sum(T first_arg, Types... args) {
    return first_arg + sum(args...);
}

template <typename... Types>
float mean(Types... args){
    return sum(args...)/float(sizeof...(args));
}

#endif //FUNCTIONS_H
