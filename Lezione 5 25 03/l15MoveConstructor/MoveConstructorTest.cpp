#include <iostream>
#include "Personaggio.h"
#include "Guerriero.h"
#include "Arma.h"

using namespace std;

// un buon articolo sull'argomento: https://smartbear.com/blog/develop/c11-tutorial-introducing-the-move-constructor-and/

// Definisco le variabili statiche delle classi 
int Personaggio::CHARACTER_COUNT = 0;

// Proviamo a swappare due oggetti (NON PUNTATORI)
void swapByCopy ( Guerriero& a, Guerriero& b )
{
	cout << " Swap By Copy " << endl;
	Guerriero temp(a); 	// Ho due copie di a
	a = b; 				// Ho due copie di b
	b = temp;			// Ho due copie di tmp (l'originale a)

}


// E se non volessi creare tutte queste copie?
void swapByMove ( Guerriero& a, Guerriero& b )
{
	cout << " Swap By Move " << endl;
	Guerriero temp( std::move(a) );
	a = std::move(b);
	b = std::move(temp);
	// Nessuna copia fatta, ho solo spostato i dati qua e la' :D 
}

int main() 
{
	Arma* spada = new Arma( 3, 3, 0);
	Arma* lancia = new Arma( 2, 6, 0);
	
	Guerriero gianni = Guerriero( (char*) "Gianni", 10,10,10,10,10,10,10 );
	Guerriero pinotto = Guerriero( (char*) "Pinotto", 10,10,10,10,10,10,10);
	gianni.setArma( spada );
	pinotto.setArma( lancia );
	
	cout << endl << "Gianni e' " << gianni.getName() << " e Pinotto e' " << pinotto.getName() << endl;
	
	swapByCopy( gianni, pinotto ); 
	
	cout << endl << "Gianni e' " << gianni.getName() << " e Pinotto e' " << pinotto.getName() << endl;
	
	swapByMove( gianni, pinotto ); 
	
	cout << endl << "Gianni e' " << gianni.getName() << " e Pinotto e' " << pinotto.getName() << endl;
	cout << endl;
	
	return 0;
	
	
}