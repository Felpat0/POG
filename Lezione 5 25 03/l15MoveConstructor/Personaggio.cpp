#include "Personaggio.h"
#include <iostream>
#include <cstring>

using namespace std;

Personaggio::Personaggio(Personaggio&& pg)
{
	cout << "Personaggio() MOVE constructor " << "from " << pg.getName() << endl;
	// Rubiamo le risorse dell'oggetto passato in argomento
	// Quindi copiamo precisamente i valori dei puntatori dell'oggetto 
	name = const_cast<char*> (pg.getName());
	equip = pg.getArmaPtr();
	// Non deleto i suoi puntatori, perche' i dati sulla heap di pg adesso sono quelli di this 
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
	pg.name =  nullptr ;
	pg.equip = nullptr ;
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
	// E' come il MOVE constructor ma PRIMA di prendere le risorse altrui
	// si devono liberare le risorse proprie dell'oggetto 
	delete name;
	delete equip;
	// E adesso il resto e' come il MOVE Constructor
	name = const_cast<char*> (pg.getName());
	equip = pg.getArmaPtr();
	// Non deleto i suoi puntatori, perche' i dati sulla heap di pg adesso sono quelli di this 
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
	pg.name =  nullptr ;
	pg.equip = nullptr ;
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
	char* charptr = const_cast <char*> (pg.getName()) ; // Devo castare da char * const di pg, a char * !
	int counter = 0;
	for (;*charptr!=0; ++charptr) ++counter;
	
	name = new char [ counter + 1 ];
	memcpy( name, pg.getName(), (counter+1)*sizeof(char) );
	name[ counter ] = '\0';
	
	if ( pg.getArmaPtr() != nullptr )
	{
		//cout << " Copio anche l'arma " << pg.getArma() << endl ;
		equip = new Arma( pg.getArma() ); // Creo una nuova arma richiamando il copy constructor dell'arma	
	}
	
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
	char* charptr = const_cast <char*> (pg.getName()) ; // Devo castare da char * const di pg, a char * !
	int counter = 0;
	for (;*charptr!=0; ++charptr) ++counter;
	
	delete [] name; // Deleto il vecchio nome
	name = new char [ counter + 1 ];
	memcpy( name, pg.getName(), (counter+1)*sizeof(char) );
	
	delete equip; // deleto la vecchia arma
	equip = new Arma( pg.getArma() ); // Creo una nuova arma richiamando il copy constructor dell'arma

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
	if ( name != nullptr )
	cout << "Deleting the character : " << name << endl;
	else
	cout << "Deleting the character (name nullptr) " << endl;
	
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
