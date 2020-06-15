#include <iostream>
#include <vector>
#include <list>
#include "Personaggio.h"
#include "Guerriero.h"
#include "Arma.h"

using namespace std;

// Definisco le variabili statiche delle classi 
int Personaggio::CHARACTER_COUNT = 0;

// ESEMPIO di Emplace vs Insert
struct Foo 
{
  int n;
  double x;
  Foo(int n, double x) : n(n), x(x) {};
};

void emplaceVsInsert()
{
	std::vector<Foo> v;
	// random-access  ++iter --iter iter+=n
	// bidirectional  ++iter --iter 
	// forward / monodirectional ++iter 
	std::vector<Foo>::iterator someIterator = v.begin();
	v.emplace(someIterator, 42, 3.1416);		// Costruisce nel vettore, prende i parametri del costruttore direttamente in input
	someIterator = v.begin();
	v.insert(someIterator, Foo(42, 3.1416));	// Copia nel vettore
	someIterator = v.begin();
	v.insert(someIterator, std::move(Foo(42, 3.1416) ) ); // Muove nel vettore 
	
	// Inserire un elemento puo' invalidare gli iteratori del vettore/
	// Se a seguito dell'inserimento avviene una riallocazione, tutti gli iteratori sono invalidati
	// in caso contrario, sono invalidati solo quelli dall'iteratore in cui si e' iniziato ad inserire, e i successivi
}


// Stampo una lista usando gli iteratori
void print_lst(const std::list<int>& lst)
{
    for (std::list<int>::const_iterator x = lst.begin(); x != lst.end(); ++x ) {
         std::cout << ' ' << *x;
    }
    std::cout << '\n';
}
void print_vec(std::vector<int>& vec) // Non mettendo "const" e' possibile utilizzare ::iterator invece di ::const_iterator
{
    for (std::vector<int>::iterator x = vec.begin(); x != vec.end(); ++x ) {
         std::cout << ' ' << *x;
    }
    std::cout << '\n';
}

// ESEMPIO lista
void listExample()
{
	std::list<int> lint = { 0, 1, 8, 2, 11, 13 };
	print_lst( lint );
	
	lint.push_back( 5 ); // 0 1 8 2 11 13 5
	print_lst( lint );
	
	list<int>::iterator lintIt = lint.begin();
	// lintIt += 4; // Fosse stato un vector (che permette l'accesso randomico) avrei potuto scrivere cosi'
	std::advance( lintIt, 4 ); // Per incrementare (=far avanzare) un iteratore non ad accesso randomico, bisogna utilizzare std::advance(iterator, n); 
	lint.emplace( lintIt, 3 ); // 0 1 8 2 3 11 13 5  
	print_lst( lint );
	
	auto lintItValid = lint.begin();
	std::advance( lintItValid, 3 ); // Un iteratore che punta al due, finche' l'elemento cui fa riferimento non viene rimosso, rimane valido
	cout << " iteratore verso '2' -> " << *lintItValid << endl; 
	
	// lintIt = lint.end() - 1; // Fosse stato un vector avrei potuto fare cosi'
	lintIt = lint.end();
	advance( lintIt, - 1 ); // Posso applicare il -1 perche' e' un iteratore bidirezionale (mentre std::forward_list<> e' una lista che fornisce iteratori mono direzionali )
	
	lint.emplace( lintIt, 4 ); // 0 1 8 2 3 11 13 4 5
	print_lst( lint );
	
	// lintIt = lint.begin() + 2; // Fosse stato un vector...
	lintIt = lint.begin();
	++lintIt; 
	++lintIt;
	lintIt = lint.erase( lintIt ); // Restituisce un iteratore che punta all'elemento seguente quello rimosso (il vecchio iteratore e' invalidato)
	print_lst( lint );// Gli iteratori che puntano agli elementi rimossi vengono invalidati, gli altri restano validi
	cout << " iteratore verso '2' -> " << *lintItValid << endl; // E' ancora valido
	
	// Il container vector invalida TUTTI gli iteratori (eccetto quelli precedenti all'iteratore usato per la rimozione) 
	// se viene rimosso un elemento dal vettore diverso dall'ultimo
	
	// 0 1 2 3 11 13 4 5
	
	//auto lintIt2 = lint.end() - 1; // Fosse stato un vector...
	auto lintIt2 = lint.end(); // Punta all'element dopo l'ultimo
	--lintIt2; // Punta all'ultimo (5)
	--lintIt2; // Punta al penultimo (4)
	//lintInt += 2; //Fosse stato un vector...
	advance( lintIt, 2 ); // Puntava all'attuale 2, voglio portarlo fino ad 11
	lintIt = lint.erase( lintIt, lintIt2 ); // vengono rimossi gli elemnti a partire da lintIt fino all'elemento precedente a lintIt2 
	// Restituisce un iteratore che punta all'elemento seguente quello rimosso (praticamente restituisce una copia di lintIt2)
	print_lst( lint );
	lintIt++;
	cout << " lintIt ora punta all'ultimo elemento -> " << *lintIt << endl;
	cout << " iteratore verso '2' -> " << *lintItValid << endl; // E' ancora valido
	
	// Con questi esempi e' visibile quanto vector sia piu' comodo e performante di list quando e' richiesto un random-access agli elementi
	// purtuttavia se bisogna inserire/rimuovere elementi non in coda al container, vector e' costretto a riallocare o spostare gli elementi
	// dell'array ogni volta, mentre la lista no
	
	
	
	std::list<Guerriero> guerrieri = { 	{ "Gianni", 10,10,10,10,10,10,10 }, 
											{ "Pinotto", 10,10,10,10,10,10,10 }, 
											{ "Amilcare", 10,10,10,10,10,10,10 } };
	cout << "\n\n" ;
	Guerriero picard  { "Picard", 99,99,99,99,99,99,99 } ;
	cout << "\n\n" ;
	guerrieri.push_back( picard);
	
	cout << "\n\n" ;
	
	// Se voglio utilizzare il polimorfismo dobbiamo come al solito utilizzare i puntatori
	// vector<Guerriero*> ptrGuerrieri (4); // <-- e' poco sicuro, perche' ci sono puntatori raw all'interno
	
	list<unique_ptr<Guerriero>> uPtrGuerrieri; 
	
	uPtrGuerrieri.push_back( unique_ptr<Guerriero>(new Guerriero()) );
	uPtrGuerrieri.push_back( unique_ptr<Guerriero>(new Guerriero()) );
	uPtrGuerrieri.push_back( unique_ptr<Guerriero>(new Guerriero()) );
	uPtrGuerrieri.push_back( unique_ptr<Guerriero>(new Guerriero()) );
	
	int counter = 0;
	for (list<unique_ptr<Guerriero>>::iterator it = uPtrGuerrieri.begin();
			it != uPtrGuerrieri.end();	++it )
	{
		string name = "Guerriero " + std::to_string(++counter);
		// Gli iteratori sono come puntatori, vanno dereferenziati per accedere all'elemento del container
		// ma l'elemento stesso e' un puntatore, quindi bisogna dereferenziare due volte
		(*it)->setName( name );
		
		cout << (**it).getName() <<  endl;
	}
}

void reverseIteratorExample() {

	cout << "\n\nReverse iterators" << endl;
	vector<int> myvector;
  	for (int i=0; i<10; i++) myvector.push_back(i);

	cout << "myvector:";
	
	// Uso la virgola per definire un'unica volta end, altrimenti sarebbe stato calcolato ad ogni iterazione del ciclo
	for (vector<int>::iterator it = myvector.begin()    , end = myvector.end()  ; it != end; ++it)
		cout << ' ' << *it;

	cout << "\n\n";

	// Un typedef per sintetizzare
	typedef vector<int>::iterator iter_type;

	// genero i reverse_iterator
	reverse_iterator<iter_type> rev_begin (myvector.end()); 
	reverse_iterator<iter_type> rev_end (myvector.begin());
	// myvector.end() punta all'elemento successivo all'ultimo del vettore (fuori dal vettore)
	// rev_begin punta all'elemento "reversamente successivo" di myvector.end() (quindi all'ultimo elemento del vettore)
	cout << "rev_begin " << *rev_begin << endl;
	// myvector.begin() punta al primo elemento del vettore
	// rev_end punta all'elemento "reversamente successivo" di myvector.begin() (quindi all'elemento precedente al primo del vettore, fuori dal vettore)
	cout << "rev_end " << *rev_end << endl;
	
	cout << "myvector reverse:";
	for (reverse_iterator<iter_type> it = rev_begin; it != rev_end; ++it)
		cout << ' ' << *it;

	cout << "\n\n";
	// il metodo base() dei reverse_iterators restituisce un iterator normale che punta all'elemento "reversamente precedente" del reverse_iterator
	cout << "rev_begin.base() " << *rev_begin.base() << endl; // punta all'elemento "reversamente precedente" di rev_begin, quindi all'elemento dopo l'ultimo del vettore
	cout << "rev_end.base() " << *rev_end.base() << endl; // punta all'elemento "revesramente precedente" di rev_end, quindi al primo elemento del vettore

	// partendo dal base() posso eseguire un ciclo nella direzione normale
	cout << "myvector:";
	for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
		cout << ' ' << *it;
  	cout << '\n';

}


int main()
{
	// Da vedere:
	emplaceVsInsert(); // <--- Semplicemente un reminder
	
	listExample();
	
	reverseIteratorExample();

	return 0;
	
	
}