#ifndef _PERSONAGGIO_H
#define _PERSONAGGIO_H

#include "Arma.h"


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
	static int CHARACTER_COUNT;
	
    Personaggio(char* n,int h,int s,int d,int c,int m,int w,int ch);
    ~Personaggio();
    
    inline const char* getName() const { return name;  }
    inline const int& getHp() const { return hp; }
    inline const Arma& getArma() const { return *equip; }
    inline void setArma(Arma* a) { equip = a; }
    
    void deathRattle();
    void increaseHp(int value );
    
    const int& getSTR() const;
    const int& getDEX() const;
    const int& getCON() const;
    const int& getMND() const;
    const int& getWIS() const;
    const int& getCHA() const;
    void increaseHP(int value);
    void increaseSTR(int value);
    void increaseDEX(int value);
    void increaseCON(int value);
    void increaseMND(int value);
    void increaseWIS(int value);
    void increaseCHA(int value);

    void attacks(Personaggio& target);
};

#endif 