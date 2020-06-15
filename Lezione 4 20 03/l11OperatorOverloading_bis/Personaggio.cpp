#include "Personaggio.h"
#include <iostream>

Personaggio::Personaggio(char* n,int h,int s,int d,int c,int m,int w,int ch):name((char*)n),
                                                                            mHp(h),hp(h),
                                                                            str(s),dex(d),con(c),
                                                                            mnd(m),wis(w),cha(ch)
{
    equip = nullptr;
}

Personaggio::~Personaggio()
{
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
    
void Personaggio::increaseStat(Stats s, int value)
{
    switch(s)
    {
        case Stats::mHp :   mHp += value; return;
        case Stats::str :   str += value; return;
        case Stats::dex :   dex += value; return;
        case Stats::con :   con += value; return;
        case Stats::mnd :   mnd += value; return;
        case Stats::wis :   wis += value; return;
        case Stats::cha :   cha += value; return;
    }
    
}

const int& Personaggio::getStat(Stats s) const
{
    switch(s)
    {
        default:
        case Stats::mHp :   return mHp;
        case Stats::str :   return str;
        case Stats::dex :   return dex;
        case Stats::con :   return con;
        case Stats::mnd :   return mnd;
        case Stats::wis :   return wis;
        case Stats::cha :   return cha;
    }
    
    
}

void Personaggio::attacks(Personaggio& target)
{
    std::cout << name << " attacks " << target.name << " : ";
    target.increaseHp( - (*equip).CalculateDamage(str) );
}