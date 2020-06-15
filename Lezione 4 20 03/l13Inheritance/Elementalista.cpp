//#include "Personaggio.h"
#include "Elementalista.h"
#include <iostream>

using namespace std;
															// Chiamo il costruttore di Mago, posso richiamare solo quelli delle classi direttamente madri
Elementalista::Elementalista(char* n,int h,int s,int d,int c,int m,int w,int ch): Mago(n,h,s,d,c,m,w,ch)
{}

Elementalista::~Elementalista()
{
    cout << "Deleting the elementalist : " << getName() << endl;
}

void Elementalista::deathRattle() 
{
	cout << "'My flame died out...' " << endl << getName() << " the elementalist dies. " << endl;
}

void Elementalista::attacks(Personaggio& target)  // virtual 
{
	// Non posso piu' accedere direttamente al nome perche' e' private
	cout << getName() << " attacks " << target.getName() << " : ";
	int damage = (*equip).CalculateDamage( cha + dex + lvl) ;
    target.increaseHp( - damage ); // Ho cambiato il parametro da passare (invece della semplice str)
}

void Elementalista::castSpellUpon(Personaggio& target, char element)
{
	char* selected;
	switch( element )
	{
		case 'f':
		selected = "fire";
		break;
		case 'w':
		selected = "water";
		break;
		case 'a':
		selected = "air";
		break;
		case 'e':
		selected = "earth";
		break;
		default:
		selected = "unknown element";
		break;
	}
	cout << getName() << " calls the elements of " << selected << " upon " << target.getName();
	int damage = CalculateSpellDamage( wis * 2 ) ;
    target.increaseHp( - damage ); // Ho cambiato il parametro da passare (invece della semplice str)
}

void Elementalista::greetings()
{
    std::cout << "'Hello, my name is " << getName() << "' said the Elementalist." << endl;
}