#ifndef SERVER_H
#define SERVER_H
#include "Entity.h"
#include <string>
#include <list>

class Server
{
public:
    int id;
    bool occupied;
    float serverTimeFrame;
    Entity currentEntity;

    Server(int id);
    int attend(Entity entity);
    void showData();
};

#endif