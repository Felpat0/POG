#include <iostream>
#include "Personaggio.h"
#include "Guerriero.h"
#include "Arma.h"

using namespace std;

// Definisco le variabili statiche delle classi 
int Personaggio::CHARACTER_COUNT = 0;

void esempio_shared () {
  shared_ptr<int> foo;
  shared_ptr<int> bar (new int(10));
  shared_ptr<int> lol;
  
  foo = bar;                          // copy
  lol = std::move(bar);					// move

  bar = std::make_shared<int> (20);  

  std::unique_ptr<int> unique (new int(30));
  foo = std::move(unique);            // move from unique_ptr

  cout << "*foo: " << *foo << '\n';
  cout << "*bar: " << *bar << '\n';

}
 

void perPassareUnoUniquePointer( unique_ptr<Guerriero>& byReference )
{
	// Essendo uno "unique" pointer non puo' avere copie, non ci possono
	// essere altri puntatori che puntano allo stesso oggetto,
	// quindi diventa assolutamente indispensabile passarlo alle funzioni
	// tramite reference!
	byReference->greetings();
}

int main()
{
	esempio_shared();
	
	// Due modi di inizializzare degli shared_ptr
	shared_ptr<Arma> p_spada = std::make_shared<Arma>( 3, 3, 0 );
	shared_ptr<Arma> p_lancia (new Arma( 2, 6, 0) );
	shared_ptr<Arma> p_ascia (new Arma( 2, 6, 0) );
	
	Guerriero* gianni = new Guerriero(  "Gianni", 10,10,10,10,10,10,10 );
	unique_ptr<Guerriero> pinotto (  new Guerriero( "Pinotto", 10,10,10,10,10,10,10)   );
	unique_ptr<Guerriero> amilcare (new Guerriero("Amilcare", 10,10,10,10,10,10,10));
	
	cout << endl << endl;
	perPassareUnoUniquePointer( amilcare );
	cout << endl << endl;

	gianni->setArma( p_spada );
	(*pinotto).setArma( p_spada );
	amilcare->setArma( std::move(p_ascia) ); // Eseguo il move per togliere una copia dello shared da 'ascia'
	
	
	delete gianni;
	
	amilcare.reset(); // Un delete esplicito di un unique_ptr
	
	cout << "Ancora non e' stata distrutta la spada!! Perche' Pinotto ed il main ne hanno una copia ciascuno" << endl;
	
	return 0;
	
	
}