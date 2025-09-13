#pragma once
#include <EstadoFoco.hpp>
class Foco
{
private:
    EstadoFoco estado;

public:
    void Encender() {estado = true;}
    void Apagar() {estado = false;}
    Foco() {}
    ~Foco() {}
};