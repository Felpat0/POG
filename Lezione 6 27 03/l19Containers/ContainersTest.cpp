#include <iostream>
#include <vector>
#include "Personaggio.h"
#include "Guerriero.h"
#include "Arma.h"

using namespace std;

// cplusplus

// Definisco le variabili statiche delle classi 
int Personaggio::CHARACTER_COUNT = 0;

void print_vec(const std::vector<int>& vec)
{
    for (auto x: vec) {
         std::cout << ' ' << x;
    }
    std::cout << '\n';
}
 
int numericExample ()
{
	// Costruisco un vettore, il primo valore e' la dimensione iniziale, il secondo il valore di partenza
    std::vector<int> vec(3,100);
    print_vec(vec);
  
	// Mi faccio restituire un iterator del vettore, un oggetto che permette di scorrere gli elementi in esso contenuti 
    auto it = vec.begin(); // begin restituisce l'iteratore in posizione 0
    it = vec.insert(it, 200); // insert inserisce l'oggetto nella posizione dell'iteratore e sposta gli altri elementi di un indice
    print_vec(vec);
 
    vec.insert(it,2,300); // in questa forma inserisce 2 copie di 300
    print_vec(vec);
 
    // "it" no longer valid, get a new one:
    it = vec.begin();
 
    std::vector<int> vec2(5,400);
    vec.insert(it+2, vec2.begin(), vec2.end() );
    print_vec(vec);
 
    int arr[] = { 501,502,503 };
    vec.insert(vec.begin(), arr, arr+3);
    print_vec(vec);
	
	return 0;
}

int main()
{
	// vector e' un container con un array, si possono inserire elementi al suo interno e si occupera' lui dei resize
	// inoltre eliminare l'array (fa il delete dell'array ma NON dei contenuti, quindi se e' un array di puntatori dovrete effettuari i delete
	// di ogni puntatore che si trova all'interno)

	numericExample();

	vector<Guerriero> guerrieri = { 	{ "Gianni", 10,10,10,10,10,10,10 }, 
											{ "Pinotto", 10,10,10,10,10,10,10 }, 
											{ "Amilcare", 10,10,10,10,10,10,10 } 
									};
	cout << "\n\n" ;
	Guerriero picard { "Picard", 99,99,99,99,99,99,99 } ;
	cout << "\n\n" ;
	guerrieri.push_back( picard);
	
	cout << "\n\n" ;
	
	// Se voglio utilizzare il polimorfismo dobbiamo come al solito utilizzare i puntatori
	// vector<Guerriero*> ptrGuerrieri (4); // <-- e' poco sicuro, perche' ci sono puntatori raw all'interno
	
	vector<unique_ptr<Guerriero>> uPtrGuerrieri; 
	
	uPtrGuerrieri.push_back( unique_ptr<Guerriero>(new Guerriero()) );
	uPtrGuerrieri.push_back( unique_ptr<Guerriero>(new Guerriero()) );
	uPtrGuerrieri.push_back( unique_ptr<Guerriero>(new Guerriero()) );
	uPtrGuerrieri.push_back( unique_ptr<Guerriero>(new Guerriero()) );
	
	
	for (unsigned int i = 0; i < uPtrGuerrieri.size(); i++)
	{
		string name = "Guerriero " + std::to_string(i);  // Trasformo l'int in stringa per concatenarle
		uPtrGuerrieri[i]->setName( name );
		cout << uPtrGuerrieri.at(i)->getName() << endl; // at(index) controlla se effettivamente l'indice rientra nel vettore
		// se e' un indice non valido lancia un'eccezione
	}
	
	return 0;
	
	
}