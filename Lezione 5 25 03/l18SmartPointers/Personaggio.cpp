#include "Personaggio.h"
#include <iostream>
#include <cstring>

using namespace std;

Personaggio::Personaggio(Personaggio&& pg)
{
	cout << "Personaggio() MOVE constructor " << "from " << pg.getName() << endl;
	// Rubiamo le risorse dell'oggetto passato in argomento
	// Quindi copiamo precisamente i valori dei puntatori dell'oggetto 
	name = std::move(pg.getName());
	// Utilizzare il move() o make_shared() muove l'ownership dello shared
	// ovvero tra 'this' e 'pg' solo 'this' avra' un suo shared_ptr verso l'arma 
	equip = std::move(pg.getArmaPtr());
	// equip = std::make_shared<Arma>( pg.getArmaPtr() );
	// I valori non pointer li copiamo bellamente
	lvl = pg.lvl;
	mHp = pg.mHp;
	hp = pg.hp;
	str = pg.str;
	dex = pg.dex;
	con = pg.con;
	mnd = pg.mnd;
	wis = pg.wis;
	cha = pg.cha;
	
	// Adesso dobbiamo riportare l'altro oggetto allo stato di creazione vuota
	// come avessimo chiamato un costruttore vuoto che setta tutto a 0 o nullptr
	pg.name = nullptr;
	pg.equip = nullptr;
	pg.lvl = 0;
	pg.mHp = 0;
	pg.hp = 0;
	pg.str = 0;
	pg.dex = 0;
	pg.con = 0;
	pg.mnd = 0;
	pg.wis = 0;
	pg.cha = 0;
}


Personaggio& Personaggio::operator=(Personaggio&& pg)
{
	cout << "Personaggio() MOVE assignment "<< "from " << pg.getName() << endl;
	// Con string e smart pointers non devo piu' chiamare il delete
	// E adesso il resto e' come il MOVE Constructor
	// string::operator= effettua un move se gli passo una &&
	name = std::move(pg.getName());
	// Utilizzare il move() o make_shared() muove l'ownership dello shared
	// ovvero tra 'this' e 'pg' solo 'this' avra' un suo shared_ptr verso l'arma 
	equip = std::move(pg.getArmaPtr());
	// equip = std::make_shared<Arma>( pg.getArmaPtr() );
	// I valori non pointer li copiamo bellamente
	lvl = pg.lvl;
	mHp = pg.mHp;
	hp = pg.hp;
	str = pg.str;
	dex = pg.dex;
	con = pg.con;
	mnd = pg.mnd;
	wis = pg.wis;
	cha = pg.cha;
	
	// Adesso dobbiamo riportare l'altro oggetto allo stato di creazione vuota
	// come avessimo chiamato un costruttore vuoto che setta tutto a 0 o nullptr
	pg.name = nullptr;
	pg.equip = nullptr;
	pg.lvl = 0;
	pg.mHp = 0;
	pg.hp = 0;
	pg.str = 0;
	pg.dex = 0;
	pg.con = 0;
	pg.mnd = 0;
	pg.wis = 0;
	pg.cha = 0;
	
	return *this;
}
				

					
											
Personaggio::Personaggio(const Personaggio& pg)
{
	// I puntatori li copio in maniera attenta
	cout << "Personaggio() COPY Constructor " << endl ;
	// string::operator= effettua una copia se gli passo una reference
	name = pg.getName() ;
	// L'operatore = copia lo shared_ptr ed aggiunge l'ownership 
	// questo vuol dire che la memoria cui punta equip verra' liberata solo dopo
	// che sia 'this->equip' sia 'pg.equip' saranno usciti fuori dallo scope 
	equip = pg.getArmaPtr();
	
	
	// Il resto lo copio bellamente
	lvl = pg.lvl;
	mHp = pg.mHp;
	hp = pg.hp;
	str = pg.str;
	dex = pg.dex;
	con = pg.con;
	mnd = pg.mnd;
	wis = pg.wis;
	cha = pg.cha;
}

Personaggio& Personaggio::operator=(const Personaggio& pg)
{
	// I puntatori li copio in maniera attenta
	cout << "Personaggio() COPY assignment " << endl;
	// string::operator= effettua una copia se gli passo una reference
	name = pg.getName() ;
	
	// L'operatore = copia lo shared_ptr ed aggiunge l'ownership 
	// questo vuol dire che la memoria cui punta equip verra' liberata solo dopo
	// che sia 'this->equip' sia 'pg.equip' saranno usciti fuori dallo scope 
	equip = pg.getArmaPtr();
	
	// Il resto lo copio bellamente
	lvl = pg.lvl;
	mHp = pg.mHp;
	hp = pg.hp;
	str = pg.str;
	dex = pg.dex;
	con = pg.con;
	mnd = pg.mnd;
	wis = pg.wis;
	cha = pg.cha;
	
	
	return *this;
}

Personaggio::Personaggio()
{
	cout << "Personaggio() Constructor"<< endl ;
	name = "Anon";
	
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

Personaggio::Personaggio(string n,int h,int s,int d,int c,int m,int w,int ch):mHp(h),hp(h),
                                                                            str(s),dex(d),con(c),
                                                                            mnd(m),wis(w),cha(ch)
{
	cout << "Personaggio() Constructor" << endl;
	Personaggio::CHARACTER_COUNT++;
	name = n;
	
	lvl = 1;
    equip = nullptr;
}

Personaggio::~Personaggio()
{
	Personaggio::CHARACTER_COUNT--;
	if ( name != "" )
	cout << "Deleting the character : " << name << endl;
	else
	cout << "Deleting the character (WITHOUT NAME) " << endl;
	
   // Niente piu' delete nome / delete equip
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
    target.increaseHp( - damage );
}

void Personaggio::greetings()
{
    std::cout << "'Hello, my name is " << name << "' said the Character. " << endl;
}
