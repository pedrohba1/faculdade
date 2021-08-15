#ifndef QUEUE_H
#define QUEUE_H
#include "Entity.h"
#include <string>
#include <list>

class Queue
{
public:
    float meanArrival;
    float meanAttendance;
    std::string typeOfDist;
    float totalSimTime;
    std::list<Entity> Entities;

    Queue();
    int generateInputs();
    int processIt();
    float averageQueueSize();
};

#endif