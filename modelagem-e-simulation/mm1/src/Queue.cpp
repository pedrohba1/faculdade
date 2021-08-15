#include "include/Queue.h"
#include "include/Entity.h"
#include <random>
#include <iostream>
#include <chrono>
#include <list>
#include <math.h>
#include <tuple>
#include <algorithm>

//função simples que eu vou usar para tirar as médias
float average(std::list<float> li, float n)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += li.front();
        li.pop_front();
    }

    return (float)sum / n;
}

Queue::Queue(){};

int Queue::generateInputs()
{
    // seed baseada em tempo:
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    // dois tipos de distribuições, uma normal e uma exponencial, escolher uma dentre elas:
    std::exponential_distribution<float> exp_distribution_TbA(1 / meanArrival);
    std::normal_distribution<double> normal_distribution_TbA(meanArrival);

    std::exponential_distribution<float> exp_distribution_ToS(1 / meanAttendance);
    std::normal_distribution<double> normal_distribution_ToS(meanAttendance);

    // uma lista com os tempos entre chegada (Time between Arrival):
    std::list<float> distTbA;
    // outra com o tempo de serviço (Time of service):
    std::list<float> distToS;

    if (this->typeOfDist == "exponential")
        for (int i = 0; i < 10000; ++i)
        {
            distTbA.push_back(exp_distribution_TbA(generator));
            distToS.push_back(exp_distribution_ToS(generator));
        }
    else
        for (int i = 0; i < 10000; ++i)
        {
            distTbA.push_back(normal_distribution_TbA(generator));
            distToS.push_back(normal_distribution_ToS(generator));
        }

    float timeFrame = 0;

    std::list<Entity> Entities;
    Entities.push_back(Entity(1, 0, distToS.front()));
    distToS.pop_front();
    int i = 2;
    while (timeFrame + distTbA.front() <= totalSimTime)
    {
        timeFrame += distTbA.front();
        distTbA.pop_front();
        Entity nextEntity = Entity(i, timeFrame, distToS.front());
        distToS.pop_front();
        Entities.push_back(nextEntity);
        i++;
    }
    this->Entities = Entities;
    return 0;
};

float Queue::averageQueueSize()
{
    std::vector<std::tuple<float, int>> events;
    std::vector<bool> inSystem;

    for (auto &entity : this->Entities)
    {
        events.push_back(std::make_tuple(entity.tArrival, entity.id));
        events.push_back(std::make_tuple(entity.tAttendance, entity.id));
        inSystem.push_back(false);
    }
    std::sort(events.begin(), events.end());

    //checar se está no sistema

    float lastTime = 0;
    int qSize = 0;
    float weightedSum = 0;

    for (auto &event : events)
    {
        float currentTime = std::get<0>(event);
        int clientId = std::get<1>(event);
        weightedSum += qSize * (currentTime - lastTime);
        if (inSystem[clientId - 1])
            qSize += -1;
        else
            qSize += 1;
        inSystem[clientId - 1] = !inSystem[clientId - 1];
        lastTime = currentTime;
    }

    return (weightedSum / this->totalSimTime);
}

int Queue::processIt()
{
    float timeFrame = 0;
    float awaitTime = 0;
    for (auto &entity : this->Entities)
    {
        if (timeFrame < entity.tArrival)
        {
            std::cout << "Sistema esperando por " << entity.tArrival - timeFrame << " minuto(s)" << std::endl
                      << std::endl;
            awaitTime += entity.tArrival - timeFrame;
            timeFrame = entity.tArrival;
        }
        entity.tInQueue = timeFrame - entity.tArrival;
        entity.tAttendance = timeFrame;
        entity.tInSystem = entity.tAttendance + entity.tService - entity.tArrival;
        timeFrame += entity.tService;

        entity.ShowData();
    }
    std::list<float> timesInSystem;
    for (auto &entity : this->Entities)
        timesInSystem.push_back(entity.tInSystem);

    std::list<float> timesInQueue;
    for (auto &entity : this->Entities)
        timesInQueue.push_back(entity.tInQueue);

    std::list<float> timesOfService;
    for (auto &entity : this->Entities)
        timesOfService.push_back(entity.tService);

    float meanTiS = average(timesInSystem, timesInSystem.size());
    float meanTiQ = average(timesInQueue, timesInQueue.size());
    float meanToF = average(timesOfService, timesOfService.size());
    float roh = meanArrival / meanAttendance;

    float lq = (pow(roh, 2)) / (1 - roh);

    std::cout << "média de tempo da entidade no sistema: " << meanTiS << std::endl;
    std::cout << "média de tempo da entidade na fila: " << meanTiQ << std::endl;
    std::cout << "média de tempo de serviço da entidade: " << meanToF << std::endl;
    std::cout << "tempo ocioso:  " << awaitTime << std::endl;
    std::cout << "taxa média de ocupação dos servidores:  " << roh << std::endl;
    std::cout << "número médio de entidades na fila:  " << this->averageQueueSize() << std::endl;

    return 0;
}
