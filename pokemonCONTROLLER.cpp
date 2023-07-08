#include <iostream>
#include "pokemonDAO.cpp"
#include "pokemonMODEL.hpp"
#include <vector>
#include <cstring>

using namespace std;

void listarPokemons(vector<Pokemon> pokemons)
{
    pokemons = buscarPokemon();
    cout << "=====================LISTAGEM POKEMONS=======================\n";
    for (Pokemon p : pokemons)
    {
        cout << "Id......: ";
        cout << p.getID() << endl;
        cout << "Nome....: ";
        cout << p.getNome() << endl;
        cout << "Elemento: ";
        cout << p.getElem() << endl;
        cout << "Atk.....: ";
        cout << p.getAtk() << endl;
        cout << "Matk....: ";
        cout << p.getMatk() << endl;
        cout << "Def.....: ";
        cout << p.getDef() << endl;
        cout << "Mdef....: ";
        cout << p.getMdef() << endl;
        cout << "Hp......: ";
        cout << p.getHp() << endl;
        cout << "Sp......: ";
        cout << p.getSp() << endl;
        cout << endl;
    }
    cout << "============================================================\n";
}

void listarPokemonId_nome(vector<Pokemon> pokemons)
{
    pokemons = buscarPokemon();
    cout << "=====================LISTAGEM POKEMONS=======================\n";
    for (Pokemon p : pokemons)
    {
        cout << "Id..: ";
        cout << p.getID() << endl;
        cout << "Nome: ";
        cout << p.getNome() << endl;
    }
    cout << "=============================================================\n";
}

bool ja_existe(vector<int> numeros, int num)
{
    for (vector<int>::size_type i = 0; i < numeros.size(); i++)
    {
        if (num == numeros[i])
            return true;
    }
    return false;
}

int escolher_pokemon_usuario(vector<Pokemon> vector)
{
    bool encontrado = false;
    int indice;
    while (encontrado == false)
    {
        cout << "Id:";
        cin >> indice;
        for (std::vector<Pokemon>::size_type i = 0; i < vector.size(); i++)
        {
            if (indice == vector[i].getID())
            {
                // posição no vector do pokemon
                indice = i;
                encontrado = true;
                break;
            }
        }
        if (encontrado == false)
        {
            cout << "\033[31m"
                 << "Digite um id válido.\n"
                 << "\033[0m";
        }
    }
    return indice;
}

int escolher_pokemon_maquina(vector<Pokemon> vector)
{
    int indice;
    srand(time(0));
    indice = rand() % vector.size();
    return indice;
}