#include "Personaggio.h"
#include <iostream>
#include <cstring>

using namespace std;

Personaggio::Personaggio()
{
    Personaggio::CHARACTER_COUNT++;
	cout << "Personaggio() Constructor" ;
	char* p = (char*) "Anon";
    int counter = 0;
    for (;*p!=0; ++p) ++counter;
    //cout << "size = " << counter << endl;
    	
    name = new char [ counter + 1];
    memcpy( name, p, (counter+1)*sizeof(char) );
	
	lvl = 1;
    equip = nullptr;
	mHp = 10;
	hp = 10;
	str = 10;
	dex = 10;
	con = 10;
	mnd = 10;
	wis = 10;
	cha = 10;
}

Personaggio::Personaggio(char* n,int h,int s,int d,int c,int m,int w,int ch):mHp(h),hp(h),
                                                                            str(s),dex(d),con(c),
                                                                            mnd(m),wis(w),cha(ch)
{
	Personaggio::CHARACTER_COUNT++;
	char* p = n;
    int counter = 0;
    for (;*p!=0; ++p) ++counter;
    //cout << "size = " << counter << endl;
    	
    name = new char [ counter + 1];
    memcpy( name, n, (counter+1)*sizeof(char) );
	
	lvl = 1;
    equip = nullptr;
}

Personaggio::~Personaggio()
{
	Personaggio::CHARACTER_COUNT--;
	cout << "Deleting the character : " << name << endl;
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
	int damage = (*equip).CalculateDamage(str);
    //int damage = equip->CalculateDamage(str);
    target.increaseHp( - damage );
}

void Personaggio::greetings()
{
    std::cout << "'Hello, my name is " << name << "' said the Character. " << endl;
}
