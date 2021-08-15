#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
public:
    int id;
    float tArrival;
    float tService;
    float tInQueue;
    float tAttendance;
    float tInSystem;
    Entity();
    Entity(int id, float tArrival, float tGone);
    void ShowData();
};

#endif