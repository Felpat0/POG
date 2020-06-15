#include "Personaggio.h"
#include "Assassino.h"
#include <iostream>
#include <cstdlib> // srand, rand
#include <ctime> // time

using namespace std;

Assassino::Assassino(char* n,int h,int s,int d,int c,int m,int w,int ch): Ladro(n,h,s,d,c,m,w,ch, 15)
{}

Assassino::Assassino(char* n,int h,int s,int d,int c,int m,int w,int ch,int l): Ladro(n,h,s,d,c,m,w,ch, l)
{}

Assassino::~Assassino()
{
    cout << "Deleting the assassin : " << getName() << endl;
}

void Assassino::deathRattle() 
{
	cout << "'I return to the shadows...' " << endl << getName() << " the assassin dies. " << endl;
}

void Assassino::attacks( Personaggio& target)  // virtual 
{
	
	cout << getName() << " attacks " << target.getName() << " twice : " << endl;
	
	srand ( time(NULL ) ); // prepara il seed
	
	cout << " the first time " ;
    int chance = rand() % 100; // numero tra 1 e maxDmg
	int crit = ( chance <= lck ) ? 2 : 1;
	if ( crit == 2 ) cout << " CRITICAL HIT " ;
	
    target.increaseHp( - getArma().CalculateDamage( dex ) * crit  ); 
	
	cout << " the second time " ;
    chance = rand() % 100; // numero tra 1 e maxDmg
	crit = ( chance <= lck ) ? 2 : 1;
	if ( crit == 2 ) cout << " CRITICAL HIT " ;
	
    target.increaseHp( - getArma().CalculateDamage( dex ) * crit );
	
}

void Assassino::levelUp()  // La implemento, cosi' non e' piu' astratta
{
	lvl++;
	mHp += 2;
	str += 2;
	dex += 4;
	con += 1;
	mnd += 1;
	wis += 2;
	cha += 3;
	lck += 3;
	
	cout << getName() << " the Assassin has leveled up!" << endl;
}

void Assassino::greetings()
{
    std::cout << "'Hello, my name is " << getName() << "' said the Assassin." << endl;
}