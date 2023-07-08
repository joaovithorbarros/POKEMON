#include <iostream>
#include "pokemonMODEL.hpp"
#include <vector>
#include <cstring>

using namespace std;

// cadastra pokemon
int cadastrarPokemon(Pokemon pokemon)
{
    // abre arquivo
    FILE *arq;
    arq = fopen("POKEMON.txt", "a");
    // escreve no arquivo cada uma das variáveis em ordem com espaços entre cada variável
    char nome[30];
    strcpy(nome, pokemon.getNome().c_str());
    fprintf(arq, "%d %s %c %d %d %d %d %d %d\n", pokemon.getID(), nome, pokemon.getElem(), pokemon.getAtk(), pokemon.getMatk(), pokemon.getDef(), pokemon.getMdef(), pokemon.getHp(), pokemon.getSp());
    fclose(arq);
    // retorna 1 se ele for inserido
    return 1;
}
// busca pokemon
vector<Pokemon> buscarPokemon()
{
    vector<Pokemon> pokemons;
    // abre arquivo
    FILE *arq;
    arq = fopen("POKEMON.txt", "rt");
    // verifica no arquivo inteiro pokemon por pokemon e retorne um vetor de pokemons
    Pokemon p;
    int i, a, ma, d, md, h, s;
    char n[30], elem;
    while (fscanf(arq, "%d %s %c %d %d %d %d %d %d", &i, n, &elem, &a, &ma, &d, &md, &h, &s) != EOF)
    {

        p.setID(i);
        string nome(n);
        p.setNome(nome);
        p.setElem(elem);
        p.setAtk(a);
        p.setMatk(ma);
        p.setDef(d);
        p.setMdef(md);
        p.setHp(h);
        p.setSp(s);
        pokemons.push_back(p);
    }

    fclose(arq);
    return pokemons;
}
// deleta pokemon
void deletarPokemon(int id)
{
    vector<Pokemon> pokemons = buscarPokemon();
    FILE *arq;
    arq = fopen("POKEMON.txt", "w");
    for (Pokemon p : pokemons)
    {
        if (p.getID() != id)
        {
            char nome[30];
            strcpy(nome, p.getNome().c_str());
            fprintf(arq, "%d %s %c %d %d %d %d %d %d\n", p.getID(), nome, p.getElem(), p.getAtk(), p.getMatk(), p.getDef(), p.getMdef(), p.getHp(), p.getSp());
        }
    }
    fclose(arq);
}
