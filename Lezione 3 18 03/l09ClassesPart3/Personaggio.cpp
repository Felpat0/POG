#include "Personaggio.h"
#include <iostream>

Personaggio::Personaggio(char* n,int h,int s,int d,int c,int m,int w,int ch):name((char*)n),
                                                                            mHp(h),hp(h),
                                                                            str(s),dex(d),con(c),
                                                                            mnd(m),wis(w),cha(ch)
{
	Personaggio::CHARACTER_COUNT++;
    equip = nullptr;
}

Personaggio::~Personaggio()
{
	Personaggio::CHARACTER_COUNT--;
    delete [] name; // Adesso serve perche' non passo piu' una string literal!!
    // if ( equip != nullptr) <-- superfluo, e' 'safe' deletare un puntatore nullo
    delete equip;
}

void Personaggio::deathRattle()
{
    std::cout << "Aaaaaah..." << std::endl;
}

void Personaggio::increaseHp(int value)
{
    hp += value;
    if ( hp > mHp )
        hp = mHp;
    if ( hp <= 0 )
    {
        hp = 0;
        deathRattle();
    }
}
    
void Personaggio::increaseHP(int value)
{
    mHp += value;
}

void Personaggio::increaseSTR(int value)
{
    str += value;
}
void Personaggio::increaseDEX(int value)
{
    dex += value;
}
void Personaggio::increaseCON(int value)
{
    con += value;
}
void Personaggio::increaseMND(int value)
{
    mnd += value;
}
void Personaggio::increaseWIS(int value)
{
    wis += value;
}
void Personaggio::increaseCHA(int value)
{
    cha += value;
}

const int& Personaggio::getSTR() const
{
    return str;
}
const int& Personaggio::getDEX() const
{
    return dex;
}
const int& Personaggio::getCON() const
{
    return con;
}
const int& Personaggio::getMND() const
{
    return mnd;
}
const int& Personaggio::getWIS() const
{
    return wis;
}
const int& Personaggio::getCHA() const
{
    return cha;
}

void Personaggio::attacks(Personaggio& target)
{
    std::cout << name << " attacks " << target.name << " : ";
    target.increaseHp( - (*equip).CalculateDamage(str) );
}