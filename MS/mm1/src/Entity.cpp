#include "include/Entity.h"
#include <iostream>

Entity::Entity(int id, float tArrival, float tService)
{
    this->id = id;
    this->tArrival = tArrival;
    this->tService = tService;
};

void Entity::ShowData()
{
    std::cout << "Entidade ID: " << this->id << std::endl;
    std::cout << "tempo de chegada: " << this->tArrival << std::endl;
    std::cout << "tempo de serviço: " << this->tService << std::endl;
    std::cout << "tempo na fila: " << this->tInQueue << std::endl;
    std::cout << "tempo de atendimento: " << this->tAttendance << std::endl;
    std::cout << "tempo de saída: " << this->tAttendance + this->tService << std::endl;
    std::cout << "tempo no sistema: " << this->tInSystem << std::endl;
    std::cout << std::endl;
}