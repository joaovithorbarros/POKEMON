#include <iostream>
#include <ctype.h>
#include <unistd.h>
#include <cstdlib>
#include <locale.h>
#include <ctime>
#include <vector>
#include "pokemonCONTROLLER.cpp"
#include "historicoCONTROLLER.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>

using namespace std;

void linhaCol(int lin, int col);
void box(int lin1, int col1, int lin2, int col2);
int menu(int lin1, int col1, int qtd, char lista[3][40]);
void textColor(int letras, int fundo);
// COR DA LETRA
enum
{
    BLACK,        // 0
    BLUE,         // 1
    GREEN,        // 2
    CYAN,         // 3
    RED,          // 4
    MAGENTA,      // 5
    BROWN,        // 6
    LIGHTGRAY,    // 7
    DARKGRAY,     // 8
    LIGHTBLUE,    // 9
    LIGHTGREEN,   // 10
    LIGHTCYAN,    // 11
    LIGHTRED,     // 12
    LIGHTMAGENTA, // 13
    YELLOW,       // 14
    WHITE         // 15

};
// COR DO FUNDO
enum
{
    _BLACK = 0,          // 0
    _BLUE = 16,          // 1
    _GREEN = 32,         // 2
    _CYAN = 48,          // 3
    _RED = 64,           // 4
    _MAGENTA = 80,       // 5
    _BROWN = 96,         // 6
    _LIGHTGRAY = 112,    // 7
    _DARKGRAY = 128,     // 8
    _LIGHTBLUE = 144,    // 9
    _LIGHTGREEN = 160,   // 10
    _LIGHTCYAN = 176,    // 11
    _LIGHTRED = 192,     // 12
    _LIGHTMAGENTA = 208, // 13
    _YELLOW = 224,       // 14
    _WHITE = 240         // 15
};

void textColor(int letra, int fundo)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letra + fundo);
}

void linhaCol(int lin, int col)
{
    //Coordenadas da Tela.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){col - 1, lin - 1}); 


    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
void box(int lin1, int col1, int lin2, int col2)
{
    int i, j, tamlin, tamcol;

    //Encontrar o tamanho da caixa.
    tamlin = lin2 - lin1;
    tamcol = col2 - col1;

    
    //Montando a caixa.
    for (i = col1; i <= col2; i++)
    { // linhas
        linhaCol(lin1, i);
        printf("%c", 196);
        linhaCol(lin2, i);
        printf("%c", 196);
    }

    for (i = lin1; i <= lin2; i++)
    { // colunas
        linhaCol(i, col1);
        printf("%c", 179);
        linhaCol(i, col2);
        printf("%c", 179);
    }
    for (i = lin1 + 1; i < lin2; i++)
    {
        for (j = col1 + 1; j < col2; j++)
        {
            linhaCol(i, j);
            printf(" ");
        }
    }
    // Posição dos cantos
    linhaCol(lin1, col1);
    printf("%c", 218);
    linhaCol(lin1, col2);
    printf("%c", 191);
    linhaCol(lin2, col1);
    printf("%c", 192);
    linhaCol(lin2, col2);
    printf("%c", 217);
}
int menu(int lin1, int col1, int qtd, char lista[3][40])
{
    int opc = 1, lin2, col2, linha, i, tamMaxItem, tecla;

    //Calcula as coordenadas.
    tamMaxItem = strlen(lista[0]);
    //Define o tamanho máximo do menu(HUD).
    for (i = 1; i < qtd; i++)
    {
        if (strlen(lista[i]) > tamMaxItem)
        {
            tamMaxItem = strlen(lista[i]);
        }
    }
    lin2 = lin1 + (qtd * 2 + 2);
    col2 = col1 + tamMaxItem + 4;

    // Monta a Tela.
    textColor(WHITE, _BLUE);
    setlocale(LC_ALL, "C");
    box(lin1, col1, lin2, col2);
    setlocale(LC_ALL, "");
    //Opções do menu em um laço.
    while (1)
    {

        linha = lin1 + 2;
        for (i = 0; i < qtd; i++)
        {
            if (i + 1 == opc)
                textColor(BLACK, _LIGHTGREEN);
            else
                textColor(WHITE, BLUE);
            linhaCol(linha, col1 + 2);
            printf("%s", lista[i]);
            linha += 2;
        }

        // Aguarda tecla
        linhaCol(1, 1);
        tecla = getch();
        linhaCol(22, 1);
        // printf(" tecla:  %d   ",tecla);
        // Opção
        if (tecla == 27)
        { // ESC
            opc = 0;
            break;
        }
        else if (tecla == 13)
        { // ENTER
            break;
        }
        //Dois "ifs" que determinam a interação do usuário com a tela, a tecla 72 eleva o seletor de opções, porém a 80 o abaixa.
        else if (tecla == 72)
        { // se possivel seleciona o item anterior - seta para cima
            if (opc > 1)
                opc--; // se opcao for maior que 1, pode voltar
        }
        else if (tecla == 80)
        { 
            if (opc < qtd)
                opc++; // Se opcao for menor que quantidade de itens, posso avançar

        }
    }
    textColor(WHITE, BLACK);
    return opc;
}

int main()
{
    int opc;
    char lista[7][40] = {
        "Listar pokemons(IDs e nomes)",
        "Listar pokemons com todos os dados",
        "Inserir pokemons",
        "Remover pokemons",
        "Listar historico",
        "Iniciar batalha",
        "Sair"};
    setlocale(LC_ALL, "");
    Pokemon pok;
    vector<Pokemon> pokemons, pokemonsUsuario(6), pokemonsMaquina(6);
    vector<int> ids;
    vector<Historico> historicos;
    historicos = buscarHistorico();

    int xid, u_indice, m_indice, xatk, xmatk, xdef, xmdef, xhp, xsp, i;
    string xnome;
    char xelem, ataque, elementos[5] = {'A', 'F', 'T', 'E', 'P'};

    bool geral = true;

    while (true)
    {
        opc = menu(10, 70, 7, lista);
        system("cls");
        linhaCol(1, 1);
        if (opc == 0)
        {
            break;
        }
        else if (opc == 1)
        {
            listarPokemonId_nome(pokemons);
            sleep(2);
        }
        else if (opc == 2)
        {
            listarPokemons(pokemons);
            sleep(2);
            pokemons.clear();
        }
        else if (opc == 3)
        {
            cout << "=======================CADASTRAR POKEMON=======================\n";
            pokemons = buscarPokemon();
            if (pokemons.size() == 0)
            {
                pok.setID(1);
            }
            else
                pok.setID(pokemons[pokemons.size() - 1].getID() + 1);
            cout << "Nome....: ";
            cin >> xnome;
            i = 0;
            while (xnome[i] != '\0')
            {
                if (i == 0)
                {
                    xnome[i] = toupper(xnome[i]);
                }
                else
                {
                    xnome[i] = tolower(xnome[i]);
                }
                i++;
            }
            pok.setNome(xnome);

            geral = true;
            while (geral == true)
            {
                cout << "Elemento: ";
                cin >> xelem;
                for (char e : elementos)
                {
                    if (toupper(xelem) == e)
                        geral = false;
                }
                if (geral == true)
                {
                    cout << "\033[31m"
                         << "Insira um elemento existente.\n"
                         << "\033[0m";
                    sleep(1);
                }
            }
            pok.setElem(toupper(xelem));

            cout << "Atk.....: ";
            cin >> xatk;
            pok.setAtk(xatk);
            cout << "Matk....: ";
            cin >> xmatk;
            pok.setMatk(xmatk);
            cout << "Def.....: ";
            cin >> xdef;
            pok.setDef(xdef);
            cout << "Mdef....: ";
            cin >> xmdef;
            pok.setMdef(xmdef);
            cout << "Hp......: ";
            cin >> xhp;
            pok.setHp(xhp);
            cout << "Sp......: ";
            cin >> xsp;
            pok.setSp(xsp);
            sleep(1);
            cout << "Inserindo pokemon...\n";
            sleep(1);
            cadastrarPokemon(pok);
            cout << "=============================================================\n";
            cout << "                       POKEMON INSERIDO                      \n";
            cout << "=============================================================\n";
            sleep(1);
        }
        else if (opc == 4)
        {
            cout << "=======================DELETAR POKEMON=======================\n";
            cout << "Id a ser deletado: ";
            cin >> xid;
            sleep(1);
            cout << "Deletando pokemon...\n";
            sleep(1);
            deletarPokemon(xid);
            cout << "==============================================================\n";
            cout << "                       POKEMON DELETADO                       \n";
            cout << "==============================================================\n";
            sleep(1);
        }
        else if (opc == 5)
        {
            listarHistorico(historicos);
            sleep(2);
            pokemons.clear();
        }
        else if (opc == 6)
        {
            listarPokemonId_nome(pokemons);
            sleep(1);
            pokemons.clear();
            ids.clear();
            pokemonsUsuario.clear();
            pokemonsMaquina.clear();

            // Usuário escolher pokemons
            pokemonsUsuario.clear();
            pokemons = buscarPokemon();
            cout << "Escolha 6 pokemons.\n";
            for (int i = 0; i < 6;)
            {
                bool encontrado = false;
                cout << "Id.: ";
                cin >> xid;
                for (Pokemon p : pokemons)
                {
                    if (p.getID() == xid)
                    {
                        if (pokemonsUsuario.size() == 0)
                        {
                            pokemonsUsuario.push_back(p);
                            encontrado = true;
                            break;
                        }
                        else
                        {
                            bool jaEscolhido = false;
                            for (Pokemon po : pokemonsUsuario)
                            {
                                if (po.getID() == xid)
                                {
                                    jaEscolhido = true;
                                    break;
                                }
                            }
                            if (!jaEscolhido)
                            {
                                pokemonsUsuario.push_back(p);
                                encontrado = true;
                                break;
                            }
                        }
                    }
                }
                if (encontrado)
                    i++;
                else
                    cout << "\033[31m"
                         << "Digite um ID válido.\n"
                         << "\033[0m";
            }
            cout << "==============================================================";
            // maquina esta escolhendo pokemons aleatoriamente
            srand(time(0));
            while (ids.size() < 6)
            {
                int tam = pokemons.size();
                int number = rand() % tam;
                if (ids.size() == 0)
                {
                    ids.push_back(number);
                }
                else
                {
                    if (ja_existe(ids, number) == false)
                    {
                        ids.push_back(number);
                    }
                }
            }

            for (int i = 0; i < 6; i++)
            {
                pokemonsMaquina.push_back(pokemons[ids[i]]);
            }

            cout << "\nMáquina está escolhendo os pokemons...\n";
            sleep(2);
            cout << "==============================================================\n";
            cout << "                         TUDO PRONTO                          \n";
            cout << "==============================================================\n";
            sleep(2);
            cout << "Seu primeiro pokemon a batalhar.\n";
            u_indice = escolher_pokemon_usuario(pokemonsUsuario);
            sleep(1);
            m_indice = escolher_pokemon_maquina(pokemonsMaquina);
            cout << "Máquina escolhendo pokemon...\n\n";

            sleep(2);
            cout << "==============================================================";
            cout << endl
                 << pokemonsUsuario[u_indice].getNome() << " X " << pokemonsMaquina[m_indice].getNome() << endl;
            cout << "==============================================================";
            sleep(2);
            // batalha
            while (pokemonsUsuario.size() > 0 && pokemonsMaquina.size() > 0)
            {
                while (true)
                {
                    // ataque usuário.
                    cout << "\nAtaque mágico 'M' | Ataque físico 'F' | Substituir pokemon 'S' \n";
                    cout << "Sua escolha: ";
                    cin >> ataque;
                    if (toupper(ataque) == 'F')
                    {
                        if ((pokemonsUsuario[u_indice].getAtk() - pokemonsMaquina[m_indice].getDef()) <= 0)
                        {
                            sleep(1);
                            cout << "Seu ataque não causou dano. "
                                 << "Hp do oponente: " << pokemonsMaquina[m_indice].getHp() << endl;
                            sleep(1);
                        }
                        else
                        {
                            sleep(1);
                            pokemonsMaquina[m_indice].setHp(pokemonsMaquina[m_indice].getHp() - (pokemonsUsuario[u_indice].getAtk() - pokemonsMaquina[m_indice].getDef()));
                            cout << "Hp do oponente: ";
                            if (pokemonsMaquina[m_indice].getHp() <= 0)
                            {
                                cout << '0' << endl;
                            }
                            else
                            {
                                cout << pokemonsMaquina[m_indice].getHp() << endl;
                            }
                            sleep(1);
                        }
                    }
                    else if (toupper(ataque) == 'M')
                    {
                        if (pokemonsUsuario[u_indice].getSp() < 10)
                        {
                            sleep(1);
                            cout << "SP esgotado. " << endl;
                            sleep(1);
                            continue;
                        }
                        pokemonsUsuario[u_indice].setSp(pokemonsUsuario[u_indice].getSp() - 10);
                        if ((pokemonsUsuario[u_indice].getElem() == 'F' && pokemonsMaquina[m_indice].getElem() == 'P') || (pokemonsUsuario[u_indice].getElem() == 'P' && pokemonsMaquina[m_indice].getElem() == 'T') || (pokemonsUsuario[u_indice].getElem() == 'E' && pokemonsMaquina[m_indice].getElem() == 'A') || (pokemonsUsuario[u_indice].getElem() == 'A' && pokemonsMaquina[m_indice].getElem() == 'F') || (pokemonsUsuario[u_indice].getElem() == 'T' && pokemonsMaquina[m_indice].getElem() == 'E'))
                        {
                            if ((2 * (pokemonsUsuario[u_indice].getMatk() - pokemonsMaquina[m_indice].getMdef())) <= 0)
                            {
                                sleep(1);
                                cout << "Seu ataque não causou dano. "
                                     << "Hp do oponente: " << pokemonsMaquina[m_indice].getHp() << endl;
                                sleep(1);
                            }
                            else
                            {
                                sleep(1);
                                pokemonsMaquina[m_indice].setHp(pokemonsMaquina[m_indice].getHp() - (2 * (pokemonsUsuario[u_indice].getAtk() - pokemonsMaquina[m_indice].getDef())));
                                cout << "Hp do oponente: ";
                                if (pokemonsMaquina[m_indice].getHp() <= 0)
                                {
                                    cout << '0' << endl;
                                }
                                else
                                {
                                    cout << pokemonsMaquina[m_indice].getHp() << endl;
                                }
                                sleep(1);
                            }
                        }
                        else if ((pokemonsUsuario[u_indice].getElem() == 'P' && pokemonsMaquina[m_indice].getElem() == 'F') || (pokemonsUsuario[u_indice].getElem() == 'T' && pokemonsMaquina[m_indice].getElem() == 'P') || (pokemonsUsuario[u_indice].getElem() == 'A' && pokemonsMaquina[m_indice].getElem() == 'E') || (pokemonsUsuario[u_indice].getElem() == 'F' && pokemonsMaquina[m_indice].getElem() == 'A') || (pokemonsUsuario[u_indice].getElem() == 'E' && pokemonsMaquina[m_indice].getElem() == 'T'))
                        {
                            if (((pokemonsUsuario[u_indice].getMatk() - pokemonsMaquina[m_indice].getMdef()) / 2) <= 0)
                            {
                                sleep(1);
                                cout << "Seu ataque não causou dano. "
                                     << "Hp do oponente: " << pokemonsMaquina[m_indice].getHp() << endl;
                                sleep(1);
                            }
                            else
                            {
                                sleep(1);
                                pokemonsMaquina[m_indice].setHp(pokemonsMaquina[m_indice].getHp() - ((pokemonsUsuario[u_indice].getMatk() - pokemonsMaquina[m_indice].getMdef()) / 2));
                                cout << "Hp do oponente: ";
                                if (pokemonsMaquina[m_indice].getHp() <= 0)
                                {
                                    cout << '0' << endl;
                                }
                                else
                                {
                                    cout << pokemonsMaquina[m_indice].getHp() << endl;
                                }
                                sleep(1);
                            }
                        }
                        else
                        {
                            if ((pokemonsUsuario[u_indice].getMatk() - pokemonsMaquina[m_indice].getMdef()) <= 0)
                            {
                                sleep(1);
                                cout << "Seu ataque não causou dano. "
                                     << "Hp do oponente: " << pokemonsMaquina[m_indice].getHp() << endl;
                                sleep(1);
                            }
                            else
                            {
                                sleep(1);
                                pokemonsMaquina[m_indice].setHp(pokemonsMaquina[m_indice].getHp() - (pokemonsUsuario[u_indice].getMatk() - pokemonsMaquina[m_indice].getMdef()));
                                cout << "Hp do oponente: ";
                                if (pokemonsMaquina[m_indice].getHp() <= 0)
                                {
                                    cout << '0' << endl;
                                }
                                else
                                {
                                    cout << pokemonsMaquina[m_indice].getHp() << endl;
                                }
                                sleep(1);
                            }
                        }
                    }
                    else if (toupper(ataque) == 'S')
                    {
                        cout << "Novo Id: ";
                        u_indice = escolher_pokemon_usuario(pokemonsUsuario);
                        sleep(2);
                        cout << "\n==============================================================";
                        cout << endl
                             << pokemonsUsuario[u_indice].getNome() << " X " << pokemonsMaquina[m_indice].getNome() << endl;
                        cout << "==============================================================\n";
                        sleep(2);
                        continue;
                    }
                    else
                    {
                        cout << "\033[31m"
                             << "Digite uma escolha válida. \n"
                             << "\033[0m";
                        continue;
                    }
                    break;
                }

                // eliminar pokemonmaquina
                if (pokemonsMaquina[m_indice].getHp() <= 0)
                {
                    cout << "O HP do pokemon oponente chegou a 0.\n";
                    sleep(1);
                    pokemonsMaquina.erase(pokemonsMaquina.begin() + m_indice);
                    if (pokemonsMaquina.size() == 0)
                    {
                        Historico h;
                        if (historicos.size() == 0)
                        {
                            h.setID(1);
                        }
                        else
                            h.setID(historicos[historicos.size() - 1].getID() + 1);
                        h.setqtdPokemons(pokemonsUsuario.size());
                        h.setVencedor(1);
                        adicionarHistorico(h);
                        historicos.push_back(h);
                        sleep(2);
                        cout << "\n==============================================================\n";
                        cout << "                         VOCÊ GANHOU                          \n";
                        cout << "==============================================================\n\n";
                        sleep(2);
                        break;
                    }
                    m_indice = escolher_pokemon_maquina(pokemonsMaquina);
                    sleep(2);
                    cout << "\n==============================================================";
                    cout << endl
                         << pokemonsUsuario[u_indice].getNome() << " X " << pokemonsMaquina[m_indice].getNome() << endl;
                    cout << "==============================================================\n";
                    sleep(2);
                }
                // ataque maquina
                while (true)
                {
                    // ataque maquina
                    srand(0);
                    i = rand() % 2;
                    ataque = (i == 1) ? 'M' : 'F';
                    if (toupper(ataque) == 'F')
                    {
                        if ((pokemonsMaquina[m_indice].getAtk() - pokemonsUsuario[u_indice].getDef()) <= 0)
                        {
                            sleep(1);
                            cout << "Ataque oponente não causou dano. "
                                 << "Seu HP: " << pokemonsUsuario[u_indice].getHp() << endl;
                            sleep(1);
                        }
                        else
                        {
                            sleep(1);
                            pokemonsUsuario[u_indice].setHp(pokemonsUsuario[u_indice].getHp() - (pokemonsMaquina[m_indice].getAtk() - pokemonsUsuario[u_indice].getDef()));
                            cout << "Seu HP: ";
                            if (pokemonsUsuario[u_indice].getHp() <= 0)
                            {
                                cout << '0' << endl;
                            }
                            else
                            {
                                cout << pokemonsUsuario[u_indice].getHp() << endl;
                            }
                            sleep(1);
                        }
                    }
                    else if (toupper(ataque) == 'M')
                    {
                        if (pokemonsMaquina[m_indice].getSp() < 10)
                        {
                            continue;
                        }
                        pokemonsMaquina[m_indice].setSp(pokemonsMaquina[m_indice].getSp() - 10);
                        if ((pokemonsMaquina[m_indice].getElem() == 'F' && pokemonsUsuario[u_indice].getElem() == 'P') || (pokemonsMaquina[m_indice].getElem() == 'P' && pokemonsUsuario[u_indice].getElem() == 'T') || (pokemonsMaquina[m_indice].getElem() == 'E' && pokemonsUsuario[u_indice].getElem() == 'A') || (pokemonsMaquina[m_indice].getElem() == 'A' && pokemonsUsuario[u_indice].getElem() == 'F') || (pokemonsMaquina[m_indice].getElem() == 'T' && pokemonsUsuario[u_indice].getElem() == 'E'))
                        {
                            if ((2 * (pokemonsMaquina[m_indice].getMatk() - pokemonsUsuario[u_indice].getMdef())) <= 0)
                            {
                                sleep(1);
                                cout << "Ataque oponente não causou dano. "
                                     << "Seu HP: " << pokemonsUsuario[u_indice].getHp() << endl;
                                sleep(1);
                            }
                            else
                            {
                                sleep(1);
                                pokemonsUsuario[u_indice].setHp(pokemonsUsuario[u_indice].getHp() - (2 * (pokemonsMaquina[m_indice].getMatk() - pokemonsUsuario[u_indice].getMdef())));
                                cout << "Seu HP: ";
                                if (pokemonsUsuario[u_indice].getHp() <= 0)
                                {
                                    cout << '0' << endl;
                                }
                                else
                                {
                                    cout << pokemonsUsuario[u_indice].getHp() << endl;
                                }
                                sleep(1);
                            }
                        }

                        else if ((pokemonsMaquina[m_indice].getElem() == 'P' && pokemonsUsuario[u_indice].getElem() == 'F') || (pokemonsMaquina[m_indice].getElem() == 'T' && pokemonsUsuario[u_indice].getElem() == 'P') || (pokemonsMaquina[m_indice].getElem() == 'A' && pokemonsUsuario[u_indice].getElem() == 'E') || (pokemonsMaquina[m_indice].getElem() == 'F' && pokemonsUsuario[u_indice].getElem() == 'A') || (pokemonsMaquina[m_indice].getElem() == 'E' && pokemonsUsuario[u_indice].getElem() == 'T'))
                        {
                            if (((pokemonsMaquina[m_indice].getMatk() - pokemonsUsuario[u_indice].getMdef()) / 2) <= 0)
                            {
                                sleep(1);
                                cout << "Ataque oponente não causou dano. "
                                     << "Seu HP: " << pokemonsUsuario[u_indice].getHp() << endl;
                                sleep(1);
                            }
                            else
                            {
                                sleep(1);
                                pokemonsUsuario[u_indice].setHp(pokemonsUsuario[u_indice].getHp() - ((pokemonsMaquina[m_indice].getMatk() - pokemonsUsuario[u_indice].getMdef()) / 2));
                                cout << "Seu HP: ";
                                if (pokemonsUsuario[u_indice].getHp() <= 0)
                                {
                                    cout << '0' << endl;
                                }
                                else
                                {
                                    cout << pokemonsUsuario[u_indice].getHp() << endl;
                                }
                                sleep(1);
                            }
                        }
                        else
                        {
                            if ((pokemonsMaquina[m_indice].getMatk() - pokemonsUsuario[u_indice].getMdef()) <= 0)
                            {
                                sleep(1);
                                cout << "Ataque oponente não causou dano. "
                                     << "Seu HP: " << pokemonsUsuario[u_indice].getHp() << endl;
                                sleep(1);
                            }
                            else
                            {
                                sleep(1);
                                pokemonsUsuario[u_indice].setHp(pokemonsUsuario[u_indice].getHp() - (pokemonsMaquina[m_indice].getMatk() - pokemonsUsuario[u_indice].getMdef()));
                                cout << "Seu HP ";
                                if (pokemonsUsuario[u_indice].getHp() <= 0)
                                {
                                    cout << '0' << endl;
                                }
                                else
                                {
                                    cout << pokemonsUsuario[u_indice].getHp() << endl;
                                }
                                sleep(1);
                            }
                        }
                    }
                    else
                    {
                        continue;
                    }
                    break;
                }

                // eliminar pokemonusuario
                if (pokemonsUsuario[u_indice].getHp() <= 0)
                {
                    cout << "\nO HP do seu pokemon chegou a zero.\n";
                    pokemonsUsuario.erase(pokemonsUsuario.begin() + u_indice);
                    if (pokemonsUsuario.size() == 0)
                    {
                        Historico h;
                        if (historicos.size() == 0)
                        {
                            h.setID(1);
                        }
                        else
                            h.setID(historicos[historicos.size() - 1].getID() + 1);
                        h.setqtdPokemons(pokemonsMaquina.size());
                        h.setVencedor(2);
                        adicionarHistorico(h);
                        historicos.push_back(h);
                        sleep(2);
                        cout << "\n==============================================================\n";
                        cout << "                       A MAQUINA GANHOU                       \n";
                        cout << "==============================================================\n\n";
                        sleep(2);
                        break;
                    }
                    u_indice = escolher_pokemon_usuario(pokemonsUsuario);
                    sleep(2);
                    cout << "\n==============================================================";
                    cout << endl
                         << pokemonsUsuario[u_indice].getNome() << " X " << pokemonsMaquina[m_indice].getNome() << endl;
                    cout << "==============================================================";
                    sleep(2);
                }
            }
        }
        else if (opc == 7)
        {
            system("cls");
            break;
        }
    }
    return 0;
}
