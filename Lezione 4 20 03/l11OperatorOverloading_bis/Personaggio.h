#ifndef _PERSONAGGIO_H
#define _PERSONAGGIO_H

#include "Arma.h"

enum class Stats { mHp, str, dex, con, mnd, wis, cha };

class Personaggio
{
    private:
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
    static const int NAME_MAX_LENGTH = 16;
    Personaggio(char* n,int h,int s,int d,int c,int m,int w,int ch);
    ~Personaggio();
    
    inline const char* getName() const { return name;  }
    inline const int& getHp() const { return hp; }
    inline const Arma& getArma() const { return *equip; }
    inline void setArma(Arma* a) { equip = a; }
    
    void deathRattle();
    void increaseHp(int value );
    void increaseStat(Stats s, int value);
    const int& getStat(Stats s) const;
    void attacks(Personaggio& target);
};

#endif 