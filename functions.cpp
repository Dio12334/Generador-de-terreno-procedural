#include "functions.h"

device dev;

float random_number(float low, float high){
    distribution dis(low, high);
    return dis(dev);
}

int random_int(int low, int high){
    intDistribution dis(low, high);
    return dis(dev);
}
