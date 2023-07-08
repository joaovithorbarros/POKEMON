#include <iostream>
#include <string>
#include "pokemonMODEL.hpp"

// getters e setters de cada variável para a proteção dos dados

int Pokemon::getID()
{
    return id;
}
void Pokemon::setID(int id)
{
    this->id = id;
}
std::string Pokemon::getNome()
{
    return nome;
}
void Pokemon::setNome(std::string nome)
{
    this->nome = nome;
}
char Pokemon::getElem()
{
    return elem;
}
void Pokemon::setElem(char elem)
{
    this->elem = elem;
}
int Pokemon::getAtk()
{
    return atk;
}
void Pokemon::setAtk(int atk)
{
    this->atk = atk;
}
int Pokemon::getMatk()
{
    return matk;
}
void Pokemon::setMatk(int matk)
{
    this->matk = matk;
}
int Pokemon::getDef()
{
    return def;
}
void Pokemon::setDef(int def)
{
    this->def = def;
}
int Pokemon::getMdef()
{
    return mdef;
}
void Pokemon::setMdef(int mdef)
{
    this->mdef = mdef;
}
int Pokemon::getHp()
{
    return hp;
}
void Pokemon::setHp(int hp)
{
    this->hp = hp;
}
int Pokemon::getSp()
{
    return sp;
}
void Pokemon::setSp(int sp)
{
    this->sp = sp;
}
