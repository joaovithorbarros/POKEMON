#include <iostream>
#include <string.h>
#include "historicoMODEL.hpp"

int Historico::getID()
{
    return id;
}
void Historico::setID(int id)
{
    this->id = id;
}

int Historico::getVencedor()
{
    return vencedor;
}
void Historico::setVencedor(int vencedor)
{
    this->vencedor = vencedor;
}
int Historico::getqtdPokemons()
{
    return qtdPokemons;
}
void Historico::setqtdPokemons(int qtdPokemons)
{
    this->qtdPokemons = qtdPokemons;
};
