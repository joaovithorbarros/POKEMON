#include <iostream>
#include "historicoMODEL.hpp"
#include "historicoDAO.cpp"

void listarHistorico(vector<Historico> historico)
{
    historico = buscarHistorico();
    cout << "=====================LISTAGEM HISTORICO=======================\n";
    for (Historico h : historico)
    {
        cout << "Id......: ";
        cout << h.getID() << endl;
        cout << "Vencedor....: ";
        cout << h.getVencedor() << endl;
        cout << "Quantidade de pokemons: ";
        cout << h.getqtdPokemons() << endl;
        cout << endl;
    }
    cout << "============================================================\n";
}

void adicionarHistorico(Historico h)
{
    cadastrarHistorico(h);
}