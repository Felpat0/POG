#ifndef _PERSONAGGIO_H
#define _PERSONAGGIO_H

#include "Arma.h"

class Personaggio
{
    //private:
    char* name;
    int mHp;
    int hp;
    int str;
    int dex;
    int con;
    int mnd;
    int wis;
    int cha;
    Arma* equip;
    
    public:
    
    Personaggio(char* n,int h,int s,int d,int c,int m,int w,int ch);
    ~Personaggio();
    
    // inline vuol dire che la funzione viene copiata nel codice in fase di compilazione
    // il primo const fa riferimento al tipo restituito: const int& vuol dire
    // che viene passata la reference dell'intero (senza fare copie) ma che tale valore NON PUO' essere modificato
    // L'ultimo const invece significa che la funzione "promette" di non modificare le variabili membro dell'oggetto
    inline const char* getName() const 
    { 
        return name;  
    }

    inline const int getHp() const 
    { 
        return hp; 
    }

    inline const Arma& getArma() const { return *equip; }
    inline void setArma(Arma* a) { equip = a; }

    //int getSTRnonConstSenzaECommerciale();
    //int& getSTRnonConst();
    //const int getSTRsenzaEcommerciale() const;
    const int& getSTR() const;
    const int& getDEX() const;
    const int& getCON() const;
    const int& getMND() const;
    const int& getWIS() const;
    const int& getCHA() const;
    
    void increaseHpMax(int value);
    void increaseSTR(int value);
    void increaseDEX(int value);
    void increaseCON(int value);
    void increaseMND(int value);
    void increaseWIS(int value);
    void increaseCHA(int value);
    
    void deathRattle();

    void increaseHp(int value);
    void attacks(Personaggio& target);
};

#endif 