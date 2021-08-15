#include <iostream>
#include "include/Entity.h"
#include "include/Queue.h"
#include "include/Config.h"
#include "ini/ini.h"
#include <unistd.h>
#include <chrono>
#include <thread>

int main()
{
    inih::INIReader r{"./config.ini"};

    // Pega os valores iniciais do arquivo para passar para o programa
    const auto &meanArrival = r.Get<float>("meanArrival", "value");
    const auto &meanAttendance = r.Get<float>("meanAttendance", "value");
    const auto &totalSimtime = r.Get<float>("totalSimTime", "value");
    const auto &typeOfDist = r.Get<std::string>("typeOfDist", "value");
    const auto &queueSize = r.Get<int>("queueSize", "value");
    const auto &iterations = r.Get<int>("iterations", "value");

    // trunca o arquivo para eliminar dados anteriores.
    std::ofstream myfile;
    myfile.open("results.txt", std::ofstream::trunc);
    myfile.close();

    Queue queue(queueSize);
    queue.meanArrival = meanArrival;
    queue.meanAttendance = meanAttendance;
    queue.totalSimTime = totalSimtime;
    queue.typeOfDist = typeOfDist;

    float sumTiS = 0, sumTiQ = 0, sumToF = 0, sumIdle = 0;

    if (iterations == 1)
    {
        queue.generateInputs();
        float *means = queue.processIt();
        sumTiS += means[0];
        sumTiQ += means[1];
        sumToF += means[2];
        sumIdle += means[3];
    }

    else
    {
        for (int i = 1; i <= iterations; i++)
        {
            queue.generateInputs();
            float *means = queue.processIt();
            sumTiS += means[0];
            sumTiQ += means[1];
            sumToF += means[2];
            sumIdle += means[3];
            sleep(1);
        }
    }
    std::cout << "média da soma de tempos da entidade no sistema: " << sumTiS / iterations << std::endl;
    std::cout << "média da soma de tempo da entidade na fila: " << sumTiQ / iterations << std::endl;
    std::cout << "média da soma de tempo  serviço da entidade: " << sumToF / iterations << std::endl;
    std::cout << "média de tempo ocioso das iterações " << sumIdle / iterations << std::endl;

    return 0;
}