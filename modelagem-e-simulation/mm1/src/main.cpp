#include <iostream>
#include "include/Entity.h"
#include "include/Queue.h"
#include "include/Config.h"
#include "ini/ini.h"

int main()
{
    inih::INIReader r{"./config.ini"};

    // Pega os valores iniciais do arquivo para passar para o programa
    const auto &meanArrival = r.Get<float>("meanArrival", "value");
    const auto &meanAttendance = r.Get<float>("meanAttendance", "value");
    const auto &totalSimtime = r.Get<float>("totalSimTime", "value");
    const auto &typeOfDist = r.Get<std::string>("typeOfDist", "value");

    Queue queue;
    queue.meanArrival = meanArrival;
    queue.meanAttendance = meanAttendance;
    queue.totalSimTime = totalSimtime;
    queue.typeOfDist = typeOfDist;

    queue.generateInputs();
    queue.processIt();
    //Queue();
    return 0;
}