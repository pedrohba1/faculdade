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
    int size;
    int entitiesInQueue;
    std::string typeOfDist;
    float totalSimTime;
    std::list<Entity> Entities;

    Queue(int size);
    int generateInputs();
    float *processIt();
    float averageQueueSize();
};

#endif