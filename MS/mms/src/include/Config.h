
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct Config
{
    int num;
    std::string str;
    double flt;
};

void loadConfig(Config &config);