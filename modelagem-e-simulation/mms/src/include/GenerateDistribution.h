#ifndef GENDISTRIBUTION_H
#define GENDISTRIBUTION_H
#include <math.h>

class GenerateDistribution
{
public:
    long int previous;
    long int a;
    long int b;
    long int m;
    float lbd;
    int mu;
    int sigma;
    float RandomGen();
    float GenExponential(float lbd);
    float GenNormal(int mu, int sigma);
    GenerateDistribution(long int seed, long int a,long  int b, long int m);
};

#endif