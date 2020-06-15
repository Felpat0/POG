//#include "Personaggio.h"
#include "Mago.h"
#include <iostream>
#include <cstdlib> // srand, rand
#include <ctime> // time

using namespace std;
																		// Chiamo il costruttore di personaggio
Mago::Mago(char* n,int h,int s,int d,int c,int m,int w,int ch): Personaggio(n,h,s,d,c,m,w,ch)
{}

Mago::~Mago()
{
    cout << "Deleting the wizard : " << getName() << endl;
}

void Mago::deathRattle() 
{
	cout << "'Fly, you fool...' " << endl << getName() << " the wizard dies. " << endl;
}

void Mago::attacks(Personaggio& target)  // virtual 
{
	// Non posso piu' accedere direttamente al nome perche' e' private
	cout << getName() << " attacks " << target.getName() << " : ";
	int damage = (*equip).CalculateDamage( str + lvl) ;
    target.increaseHp( - damage ); // Ho cambiato il parametro da passare (invece della semplice str)
}

void Mago::castSpellUpon(Personaggio& target, int castingTime)
{
	cout << getName() << " casts a spell upon " << target.getName();
	cout << ". After chanting for " << castingTime << " seconds ";
	int damage = CalculateSpellDamage( mnd * 2 ) ;
    target.increaseHp( - damage ); // Ho cambiato il parametro da passare (invece della semplice str)
}

int Mago::CalculateSpellDamage(int stat) const
{
    srand ( time(NULL ) ); // prepara il seed
    int damage = rand() % 10; // numero tra 0 e 9
    damage += 10; // porto "damage" tra 10 e 19
    damage = ( damage * stat ) / 10; // per ogni punto di stat aumento il danno del 10%
    
    cout << " the spell inflicts " << damage << " damage!" << endl;
    return damage;
}

void Mago::levelUp()  // La implemento, cosi' non e' piu' astratta
{
	// Posso accedere alle stats perche' sono protected
	lvl++;
	mHp += 2;
	hp += 2;
	str += 0;
	dex += 1;
	con += 1;
	mnd += 3;
	wis += 1;
	cha += 2;
	
	cout << getName() << " the Wizard has leveled up!" << endl;
}

void Mago::greetings()
{
    std::cout << "'Hello, my name is " << getName() << "' said the Wizard." << endl;
}