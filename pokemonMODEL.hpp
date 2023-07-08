#ifndef pokemonMODEL_h
#define pokemonMODEL_h

class Pokemon
{
private:
    int id;
    std::string nome;
    char elem;
    int atk;
    int matk;
    int def;
    int mdef;
    int hp;
    int sp;

public:
    int getID();

    void setID(int id);

    std::string getNome();

    void setNome(std::string nome);

    char getElem();

    void setElem(char elem);

    int getAtk();

    void setAtk(int atk);

    int getMatk();

    void setMatk(int matk);

    int getDef();

    void setDef(int def);

    int getMdef();

    void setMdef(int mdef);

    int getHp();

    void setHp(int hp);

    int getSp();

    void setSp(int sp);
};

#endif