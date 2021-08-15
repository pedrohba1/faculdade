#include "include/Server.h"
#include "include/Entity.h"
#include <random>
#include <iostream>
#include <chrono>
#include <list>
#include <math.h>
#include <tuple>
#include <algorithm>

Server::Server(int id)
{
    this->id = id;
    this->occupied = false;
    this->serverTimeFrame = 0;
};

void Server::showData()
{
    if (this->serverTimeFrame == 0)
        return;
    std::cout << "Time frame do servidor " << this->id << ": " << this->serverTimeFrame << std::endl;
    std::cout << "ID da entidade em atendimento: " << this->currentEntity.id << std::endl;
    std::cout << std::endl;
}

int Server::attend(Entity entity)
{
    this->currentEntity = entity;
    this->occupied = true;
    this->serverTimeFrame = entity.tArrival + entity.tService;
    return 1;
}