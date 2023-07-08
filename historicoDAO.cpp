#include <iostream>
#include "historicoMODEL.hpp"
#include <vector>
#include <cstring>

using namespace std;

// cadastra his
int cadastrarHistorico(Historico h)
{
    // abre arquivo
    FILE *arq;
    arq = fopen("HISTORICO.txt", "a");
    // escreve no arquivo cada uma das variáveis em ordem com espaços entre cada variável
    fprintf(arq, "%d %d %d\n", h.getID(), h.getVencedor(), h.getqtdPokemons());
    fclose(arq);
    // retorna 1 se ele for inserido
    return 1;
}
// busca his
vector<Historico> buscarHistorico()
{
    vector<Historico> his;
    // abre arquivo
    FILE *arq;
    arq = fopen("HISTORICO.txt", "rt");
    // verifica no arquivo inteiro cada partida ocorrida e retorne um vetor do historico
    Historico h;
    int i, v, q;
    while (fscanf(arq, "%d %d %d", &i, &v, &q) != EOF)
    {
        h.setID(i);
        h.setVencedor(v);
        h.setqtdPokemons(q);
        his.push_back(h);
    }

    fclose(arq);
    return his;
}
