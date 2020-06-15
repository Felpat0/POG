//#include "Personaggio.h"
#include "Ladro.h"
#include <iostream>
#include <cstdlib> // srand, rand
#include <ctime> // time

using namespace std;

Ladro::Ladro(char* n,int h,int s,int d,int c,int m,int w,int ch): Personaggio(n,h,s,d,c,m,w,ch)
{
	lck = 15;
}

Ladro::Ladro(char* n,int h,int s,int d,int c,int m,int w,int ch,int l): Personaggio(n,h,s,d,c,m,w,ch)
{
	lck = l;
}

Ladro::~Ladro()
{
    cout << "Deleting the rogue : " << getName() << endl;
}

void Ladro::deathRattle() 
{
	cout << "'My treasure will die with me...' " << endl << getName() << " the rogue dies. " << endl;
}

void Ladro::attacks(Personaggio& target)  // virtual 
{
	// Non posso piu' accedere direttamente al nome perche' e' private
	cout << getName() << " attacks " << target.getName() << " : ";
	
	srand ( time(NULL ) ); // prepara il seed
    int chance = rand() % 100; // numero tra 1 e maxDmg
	int crit = ( chance <= lck ) ? 2 : 1;
	if ( crit == 2 ) cout << " CRITICAL HIT " ;
	
	int damage = (*equip).CalculateDamage( dex * crit );
    target.increaseHp( - damage  ); // Ho cambiato il parametro da passare (invece della semplice str)
}

void Ladro::levelUp()  // La implemento, cosi' non e' piu' astratta
{
	// Posso accedere alle stats perche' sono protected
	lvl++;
	mHp += 3;
	hp += 3;
	str += 1;
	dex += 3;
	con += 1;
	mnd += 1;
	wis += 1;
	cha += 2;
	lck += 2;
	
	cout << getName() << " the Rogue has leveled up!" << endl;
}


void Ladro::greetings()
{
    std::cout << "'Hello, my name is " << getName() << "' said the Rogue." << endl;
}