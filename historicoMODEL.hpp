#ifndef historicoMODEL_h
#define historicoMODEL_h

class Historico
{
private:
    int id;
    int vencedor;
    int qtdPokemons;

public:
    int getID();
    void setID(int id);
    int getVencedor();
    void setVencedor(int vencedor);
    int getqtdPokemons();
    void setqtdPokemons(int qtdPokemons);
};
#endif