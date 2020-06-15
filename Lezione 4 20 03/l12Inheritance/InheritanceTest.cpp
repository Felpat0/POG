#include <iostream>
#include "Personaggio.h"
#include "Guerriero.h"
#include "Arma.h"

using namespace std;


// Definisco le variabili statiche delle classi 
int Personaggio::CHARACTER_COUNT = 0;

int main()
{
	// MEMO:   Costruttore Personaggio (char* n,int h,int s,int d,int c,int m,int w,int ch);
	
	//Personaggio pg = Personaggio("Diprova", 12, 10, 10, 10, 10, 10, 10 ); // <- NON POSSO CREARE UN Personaggio perche' e' astratta!
	
	//Personaggio pg = Guerriero( (char*) "Ken" , 20, 18, 10, 16, 10, 12, 13 ); // <- NON POSSO COMUNQUE CREARE UN GUERRIERO DA UNA VARIABILE Personaggio perche' e' astratta!
	
	//Guerriero g = Guerriero( (char*) "Dartagnan" , 20, 20,20,20,20,20,22 ) // <- Questo POSSO FARLO

	Personaggio* ppgToGuerr = new Guerriero( (char*) "Ken" , 20, 18, 10, 16, 10, 12, 13 ); // <- POSSO INSTANZIARLO TRAMITE PUNTATORE PERO'
	
	
	ppgToGuerr->deathRattle(); // Richiama il deathRattle di Guerriero (binding dinamico)
	cout << endl;
	ppgToGuerr->greetings(); // Richiama il greetings di Personaggio ( perche' greetings() non e' VIRTUAL!!! )
	cout << endl;
	
	cout << "# pg : " << Personaggio::CHARACTER_COUNT <<  endl;
	 
	delete ppgToGuerr;
	
	cout << "# pg : " << Personaggio::CHARACTER_COUNT << endl;
	
	return 0;
	
	
}