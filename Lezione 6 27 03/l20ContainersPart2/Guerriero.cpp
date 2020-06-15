//#include "Personaggio.h"
#include "Guerriero.h"
#include <iostream>

using namespace std;


// Richiamo il move constructor di Personaggio, ma devo castare g 
// che gia' dalla initialization list risulta essere un lvalue, in un rvalue
// se passassi soltanto Personaggio(g) verrebbe richiamato il COPY Constructor
// di Personaggio invece del suo MOVE Constructor!
// Questo cast viene fatto dalla funzione std::move()
Guerriero::Guerriero(Guerriero&& g) : Personaggio( std::move( g ) )
{
	cout << "Guerriero MOVE Constructor "<< "from " << getName() << endl;
}

Guerriero& Guerriero::operator=(Guerriero&& g)
{
	cout << "Guerriero MOVE Assignment "<< "from " << g.getName() << endl;
	// Personaggio::operator=( ) richiama l'operatore della classe madre
	// anche in questo caso pero' se gli passassi 'g' richiamerebbe il COPY assignment
	// allora effettuo un cast su 'g' per renderlo una rvalue con std::move(g).
	// Infine, l'operatore Personaggio restituisce un Personaggio&, devo quindi
	// effettuare un cast a Guerriero& (non mi serve fare un test perche' so che
	// si tratta di un Guerriero, quindi uso lo static_cast invece del dynamic_cast)
	return static_cast<Guerriero&> (Personaggio::operator=( std::move(g) ) );
}
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
	cout << "Guerriero COPY assignmnt" << endl;
	// Richiamo l'operatore della classe madre
	Personaggio::operator=( g );
	// Non ho altre variabili da sistemare, apposto
	return *this;
}

Guerriero::Guerriero()
{}
																		// Chiamo il costruttore di personaggio
Guerriero::Guerriero(string n,int h,int s,int d,int c,int m,int w,int ch): Personaggio(n,h,s,d,c,m,w,ch)
{
	cout << "Guerriero() Constructor" << endl;
}

Guerriero::~Guerriero()
{
	if ( getName() != "" )
    cout << "Deleting the warrior : " << getName() << endl;
	else
	cout << "Deleting the warrior (WITHOUT NAME) " << endl;
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