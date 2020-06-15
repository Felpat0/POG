//#include "Personaggio.h"
#include "Guerriero.h"
#include <iostream>

using namespace std;
										// Richiamo il copy-constructor di Personaggio
Guerriero::Guerriero(const Guerriero& g) : Personaggio( g )
{
	cout << "Guerriero COPY Constructor" << endl;
	// Non ho altre variabili da copiare, apposto
	// Pero' occhio, se non esplicitavo la chiamata a Personaggio( pg ),
	// il compilatore avrebbe richiamato implicitamente Personaggio(), 
	// quindi tale chiamata va effettuata categoricamente!
}


Guerriero& Guerriero::operator=(const Guerriero& g)
{
	cout << "Guerriero COPY Assignment" << endl;
	// Richiamo l'operatore della classe madre
	Personaggio::operator=( g );
	// Non ho altre variabili da sistemare, apposto
	return *this;
}

Guerriero::Guerriero() : Personaggio()
{
	cout << "Guerriero() Constructor " << this << endl;
}
																		// Chiamo il costruttore di personaggio
Guerriero::Guerriero(char* n,int h,int s,int d,int c,int m,int w,int ch): Personaggio(n,h,s,d,c,m,w,ch)
{
	cout << "Guerriero() Constructor " << this << endl;
}

Guerriero::~Guerriero()
{
    cout << "Deleting the warrior : " << getName() << endl;
}

void Guerriero::deathRattle() 
{
	cout << "'My king, I failed you...' " << endl << getName() << " the warrior dies. " << endl;
}

void Guerriero::deathRat() // Un possibile tentativo di override di deathRattle andato male per un 'refuso'
{
	cout << "Il death rattle scritto male... -.-'' " << endl;
}

void Guerriero::attacks(Personaggio& target)  // virtual 
{
	// Non posso piu' accedere direttamente al nome perche' e' private
	cout << getName() << " attacks " << target.getName() << " : ";
	int damage = (*equip).CalculateDamage( (str * 2 ) + lvl) ;
    target.increaseHp( - damage ); // Ho cambiato il parametro da passare (invece della semplice str)
}

void Guerriero::levelUp()  // La implemento, cosi' non e' piu' astratta
{
	// Posso accedere alle stats perche' sono protected
	lvl++;
	mHp += 4;
	hp += 4;
	str += 3;
	dex += 1;
	con += 2;
	mnd += 0;
	wis += 1;
	cha += 1;
	
	cout << getName() << " the Warrior has leveled up!" << endl;
}

void Guerriero::greetings()
{
    std::cout << "'Hello, my name is " << getName() << "' said the Warrior." << endl;
}