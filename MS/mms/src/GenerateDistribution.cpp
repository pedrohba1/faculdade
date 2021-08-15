#include "include/GenerateDistribution.h"
#include <iostream>
#include <math.h>
#define _USE_MATH_DEFINES

GenerateDistribution::GenerateDistribution(long int seed, long int a, long int b, long int m)
{
    this->previous = seed;
    this->a = a;
    this->b = b;
    this->m = m;
};

float GenerateDistribution::
    RandomGen()
{
    long int randomNumber = (this->a * this->previous + this->b) % this->m;
    this->previous = randomNumber;
    return (float(randomNumber) / float(this->m));
}

float GenerateDistribution::GenExponential(float lbd = 1)
{
    float exp = (-1) * (1 / lbd) * log(1 - this->RandomGen());
    return exp;
}

float GenerateDistribution::
    GenNormal(int mu = 0, int sigma = 1)
{
    float r1 = this->RandomGen();
    float r2 = this->RandomGen();

    float z1 = cos(2 * M_PI * r2) * sqrt((-2) * log(r1));
    float z2 = sin(2 * M_PI * r2) * sqrt((-2) * log(r1));

    z1 = sigma * z1 + mu;
    z2 = sigma * z2 + mu;

    if (r1 > r2)
        return z1;
    return z2;
}