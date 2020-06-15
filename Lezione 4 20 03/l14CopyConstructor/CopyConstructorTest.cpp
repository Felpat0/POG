#include <iostream>
#include "Personaggio.h"
#include "Guerriero.h"
#include "Arma.h"

using namespace std;

// Definisco le variabili statiche delle classi 
int Personaggio::CHARACTER_COUNT = 0;

int main()
{

	cout << endl << "Instanzio la spada " << endl;
	Arma* spada = new Arma( 3, 3, 0);
	 
	cout << endl << "Instanzio pt " << endl;
	Guerriero* pt = new Guerriero( (char*) "Ken" , 20, 18, 10, 16, 10, 12, 13 ); 
	pt->setArma( spada );
	
	cout << endl << "Copio pt dentro pt2 " << endl;
	Guerriero* pt2 = new Guerriero( *pt );
	cout << endl << "Modifico l'arma di pt2 " << endl;
	pt2->getNonConstArma()++; // vengono deletate 2 armi 
	 
	cout << endl; 
	cout << "Arma di pt " << pt->getArma() << endl << endl;
	cout << "Arma di pt2 " << pt2->getArma() << endl << endl;
	
	*pt2 = *pt;

	cout << "Arma di pt2 " << pt2->getArma() << endl << endl;

	delete pt;
	delete pt2;
	 
	cout << endl << "Instanzio g1 " << endl;
	Guerriero g1 = Guerriero( (char*) "Toki" , 20, 18, 10, 16, 10, 12, 13 );
	cout << endl << "Instanzio l'arma " << endl;
	Arma* armaG1 = new Arma( 1, 6, 0 );
	g1.setArma( armaG1 ); 
	
	cout << endl << "Copiassegno g1 a g2 " << endl;
	Guerriero g2 = Guerriero();
	g2 = g1;
	// Se avessi scritto Guerriero g2; g2 = g1; (senza richiamare il costruttore di Guerriero) sarebbe partito il COPY constructor!
	cout << endl << "Modifico l'arma della copia di g2 " << endl << endl;
	g2.getNonConstArma()++;
	
	cout << "Arma di g1 " << g1.getArma() << endl << endl;
	cout << "Arma di g2 " << g2.getArma() << endl << endl;
	
	// Non servono in questo caso, le deleto direttamente da g2 e g1
	//delete g2.getArmaPtr();
	//delete g1.getArmaPtr();
	
	return 0;
	
	
}