#include <iostream>
#include "Personaggio.h"
#include "Guerriero.h"
#include "Ladro.h"
#include "Assassino.h"
#include "Mago.h"
#include "Elementalista.h"
#include "Arma.h"

using namespace std;

// Definisco le variabili statiche delle classi 
int Personaggio::CHARACTER_COUNT = 0;

int main()
{
	// MEMO:   Costruttore Personaggio (char* n,int h,int s,int d,int c,int m,int w,int ch);
	
	//Personaggio pg = Personaggio("Diprova", 12, 10, 10, 10, 10, 10, 10 ); // <- NON POSSO CREARE UN Personaggio perche' e' astratta!
	
	//Personaggio pg = Guerriero( (char*) "Ken" , 20, 18, 10, 16, 10, 12, 13 ); // <- NON POSSO COMUNQUE CREARE UN GUERRIERO DA UNA VARIABILE Personaggio perche' e' astratta!
	
	Personaggio* ppgToGuerr = new Guerriero( (char*) "Ken" , 20, 18, 10, 16, 10, 12, 13 ); // <- POSSO INSTANZIARLO TRAMITE PUNTATORE PERO'

	ppgToGuerr->deathRattle(); // Richiama il deathRattle di Guerriero (binding dinamico)
	cout << endl;
	ppgToGuerr->greetings(); // Richiama il greetings di Personaggio ( perche' greetings() non e' VIRTUAL!!! )
	cout << endl;
	
	cout << "# pg : " << Personaggio::CHARACTER_COUNT << endl;

	
	
	
	cout << endl;
	
	// Il Polimorfismo (un Elementalista e' anche un Mago) funziona solo tramite puntatori
	// Mago magoToElem = Elementalista( (char*) "Sub-Zero", 12, 13, 12, 11, 14, 13, 18 ); // <-- richiama il distruttore gia' in questa riga
	// Usare il Polimorfismo SEMPRE e solo tramite puntatori 
	
	// Vediamo un po' di problemi con l'overload di funzioni tra classi madre-figlie
	Elementalista* pElem = new Elementalista( (char*) "Piros", 12, 13, 12, 11, 14, 13, 18 );
	Mago* pMageToElem = pElem;	
	
	pMageToElem->castSpellUpon( *ppgToGuerr, 1 ); // <- Non sono override (la firma e' diversa) quindi mi aspetto quella di Mago
	pElem->castSpellUpon( *ppgToGuerr, 1 ); // <- Mi aspetterei di vedere la funzione del Mago e invece richiama quella dell'Elementalista (converte 1 to char)
	// Cio' avviene perche' la classe figlia NASCONDE la funzione della classe madre (quando ci sono tipi automaticamente convertibili)
	// Per risolvere questa cosa decommentiamo l'using Mago::castSpellUpon; dalla classe Elementalista
		
	cout << endl;
	
	Assassino* pSin = new Assassino( (char*) "Creed", 8,14,20,14,12,13,16 );
	Ladro* pLadToSin = pSin; // Ok
	Personaggio* pgToSin = pLadToSin; // Ok
	pLadToSin->greetings();
	pgToSin->greetings();

	cout << endl << "# pg : " << Personaggio::CHARACTER_COUNT << endl;

	delete ppgToGuerr;
	delete pMageToElem;
	delete pSin; 

	cout << endl << "# pg : " << Personaggio::CHARACTER_COUNT << endl;
	
	cout << endl;
	
	// E se voglio metterli tutti in un array? Array di puntatori for the win
	int array [3]; // <- cosi' definisco un array di interi sulla stack
	Personaggio* ppgArray[4]; // <- cosi' di puntatori di pg sulla stack
	int i = 0;
	ppgArray[i++] = new Guerriero( (char*) "Boromir", 20,15,15,15,10,10,10);
	ppgArray[i++] = new Mago( (char*) "Gandalf", 15,10,10,10,15,15,15);
	ppgArray[i++] = new Elementalista( (char*) "Balrog", 50,25,25,25,25,25,25);
	ppgArray[i] = new Ladro( (char*) "Smeagol", 15,8,12,10,10,10,8,7);
	// Non posso metterci dentro instanze di Ladro (e quindi neanche di Assassino ) 
	
	// Non posso richiamare il metodo di Mago/Elementalista da un Personaggio, devo effettuare un cast!
	/*
	Ne abbiamo 4 a disposizione:
		
		dynamic_cast <new_type> (expression)	: 
			upcast/downcast con controllo che l'oggetto sia compatibile (puntatore annullato in caso di fallimento)
			puo' fare il cast solo su puntatori a classi
		
		static_cast <new_type> (expression)		: 
			upcast/downcast senza controllo che l'oggetto sia compatibile, piu' veloce ma meno sicuro 
			(il programmatore deve assicurarsi che il cast sia valido)
			non e' limitato ai soli puntatori a classi (puo' fare le conversioni tipiche dei cast classici)
		
		reinterpret_cast <new_type> (expression): 
			casta un puntatore a qualsiasi altro tipo di puntatore. non ha restrizioni, ma dereferenziare
			un puntatore partendo dal tipo sbagliato non e' una pratica sicura (come ad esempio dereferenziare un 
			puntatore di tipo Arma, castato a Personaggio, sono classi incompatibili)
			
		const_cast <new_type> (expression)		:
			serve per castare un puntatore ad una variabile costante ( const type * ) in un puntatore ad una 
			variabile non constante ( type * ) magari per passarlo ad una funzione che abbia ( type * ) come parametro
			
	Altre info alla pagina: http://www.cplusplus.com/doc/tutorial/typecasting/
	*/

	// Se siamo certi che il cast funzioni possiamo quindi utilizzare
	Elementalista* pe = static_cast<Elementalista*>(ppgArray[2]);
	pe->castSpellUpon( *ppgArray[1], 'f' );
	// Che posso scrivere anche come
	// static_cast<Elementalista*>(ppgArray[2])->castSpellUpon( *ppgArray[1], 'f' );
	
	// Altrimenti sfruttiamo il controllo del dynamic_cast
	//Elementalista* p = dynamic_cast<Elementalista*>(ppgArray[2]) ;
	//if ( p != nullptr )
	if ( Elementalista* p = dynamic_cast<Elementalista*>(ppgArray[2]) )
	{
		// Entrera' qui dentro solo se il cast ha successo
		(*p).castSpellUpon( *ppgArray[0], 'f' );
	}
	
	cout << endl;
	// Adesso pero' devo chiamare il delete su tutti gli elementi dell'array!
	for (auto e = 0; e < 4; e++ )
	{
		delete ppgArray[e];
	}
	
 
	
	// Infine... e se volessimo un array di puntatori di dimensioni non note in fase di compilazione? Da mettere sulla heap?
	// Eh, serve un doppio puntatore allora! :D 
	int size = 5;
	//int* arr = new int[size];
	Guerriero** pointerToPointersArray = new Guerriero*[ size ]; // Creo un array di puntatori nella heap e lo assegno a un puntatore di puntatore
	for ( auto e = 0; e < size; e++ )
	{											    
		pointerToPointersArray[e] = new Guerriero( (char*) "Anon" , e+1, 10,10,10,10,10,10 ); 
		pointerToPointersArray[e]->greetings();
		cout << " HP : " << pointerToPointersArray[e]->getHp() << endl;
	}
	cout << endl;
	// Ed ora devo cancellarli
	for ( auto e = 0; e < size; e++ )
	{
		delete pointerToPointersArray[e]; // Prima gli elementi dell'array nella heap
	}
	delete [] pointerToPointersArray; // <- stavolta devo deletare anche l'array (perche' sta nella heap pure lui)
	
    return 0;
}
