#include "include/Queue.h"
#include "include/Entity.h"
#include "include/Server.h"
#include "include/GenerateDistribution.h"
#include <random>
#include <iostream>
#include <chrono>
#include <list>
#include <math.h>
#include <tuple>
#include <algorithm>
#include <fstream>
#include <time.h>

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

Queue::Queue(int size)
{
    this->size = size;
    this->entitiesInQueue = 0;
};

int Queue::generateInputs()
{

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    // dois tipos de distribuições, uma normal e uma exponencial, escolher uma dentre elas:
    GenerateDistribution distGen(rand(), 1103515245, 12938, pow(2, 31));

    // uma lista com os tempos entre chegada (Time between Arrival):
    std::list<float> distTbA;
    // outra com o tempo de serviço (Time of service):
    std::list<float> distToS;

    if (this->typeOfDist == "exponential")
        for (int i = 0; i < 10000; i++)
        {
            distTbA.push_back(distGen.GenExponential(1 / meanArrival));
            distToS.push_back(distGen.GenExponential(1 / meanAttendance));
        }
    else
        for (int i = 0; i < 10000; i++)
        {
            distTbA.push_back(distGen.GenNormal(meanArrival, 1));
            distToS.push_back(distGen.GenNormal(meanAttendance, 1));
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

float *Queue::processIt()
{
    Server server1(1), server2(2);

    float timeFrame = 0;
    float awaitTime = 0;
    for (auto &entity : this->Entities)
    {

        if (timeFrame == server1.serverTimeFrame)
            server1.occupied = false;
        if (timeFrame == server2.serverTimeFrame)
            server2.occupied = false;

        if (timeFrame < entity.tArrival)
        {
            if (!server1.occupied)
            {
                std::cout << "Servidor " << server1.id << " ficou ocioso por: " << entity.tArrival - timeFrame << " minuto(s)" << std::endl;
                std::cout << std::endl;
            }
            if (!server2.occupied)
            {
                std::cout << "Servidor " << server2.id << " ficou ocioso por: " << entity.tArrival - timeFrame << " minuto(s)" << std::endl;
                std::cout << std::endl;
            }
            awaitTime += entity.tArrival - timeFrame;
            timeFrame = entity.tArrival;
        }

        if (!server1.occupied)
        {
            entity.tInQueue = timeFrame - entity.tArrival;
            entity.tAttendance = timeFrame;
            entity.tInSystem = entity.tAttendance + entity.tService - entity.tArrival;
            server1.attend(entity);
        }

        else if (!server2.occupied)
        {
            entity.tInQueue = timeFrame - entity.tArrival;
            entity.tAttendance = timeFrame;
            entity.tInSystem = entity.tAttendance + entity.tService - entity.tArrival;
            server2.attend(entity);
        }

        timeFrame = std::min(server1.serverTimeFrame, server2.serverTimeFrame);
        entity.ShowData();
        server1.showData();
        server2.showData();
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

    std::ofstream myfile;
    myfile.open("results.txt", std::ios::app);
    myfile << "média de tempo da entidade no sistema: " << meanTiS << std::endl;
    myfile << "média de tempo da entidade na fila: " << meanTiQ << std::endl;
    myfile << "média de tempo de serviço da entidade: " << meanToF << std::endl;
    myfile << "tempo ocioso:  " << awaitTime / 2 << std::endl;
    //TODO: Taxa média de ocupação de servidores no mm2 deve ser diferente, dá uma olhada aí como calcula
    myfile << "taxa média de ocupação dos servidores:  " << roh << std::endl;
    myfile << "número médio de entidades na fila:  " << this->averageQueueSize() << std::endl;
    myfile << "------------------------------------------" << std::endl;
    myfile.close();

    float idle = awaitTime / 2;

    static float means[3];
    means[0] = meanTiS;
    means[1] = meanTiQ;
    means[2] = meanToF;
    means[3] = idle;
    return means;
}