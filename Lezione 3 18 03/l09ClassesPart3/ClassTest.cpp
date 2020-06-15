#include <iostream>
#include "Personaggio.h"
#include "Arma.h"

using namespace std;

int Personaggio::CHARACTER_COUNT = 0; // Le variabili statiche (non costanti) VANNO definite nel cpp, obbligatoriamente!

int main()
{	 
    char* nomeInInput = new char [ Personaggio::NAME_MAX_LENGTH ];
    cout << "Inserire il nome del personaggio ( max " << Personaggio::NAME_MAX_LENGTH << " caratteri ) : " ;
    
    cin >> nomeInInput;
    Personaggio* A = new Personaggio( nomeInInput, 10, 16, 12, 12, 12, 12, 10 );
    
    nomeInInput = new char [ Personaggio::NAME_MAX_LENGTH ];
    cout << "Inserire il nome del personaggio ( max " << Personaggio::NAME_MAX_LENGTH << " caratteri ) : " ;
    cin >> nomeInInput;
    Personaggio* B = new Personaggio( nomeInInput, 8, 10, 12, 12, 12, 12, 10 );
    
    nomeInInput = new char [ Arma::NAME_MAX_LENGTH ];
    cout << "Inserire il nome dell'arma ( max " << Arma::NAME_MAX_LENGTH << " caratteri ) : " ;
    cin >> nomeInInput;
    Arma* spada = new Arma( nomeInInput, 8, 10 );
     
    A->setArma( spada ); 
    
	cout << "Conta PG: " << Personaggio::CHARACTER_COUNT << endl;
	
    cout << B->getName() << " has " << B->getHp() << " hp!" << endl;
    A->attacks( *B );
    cout << B->getName() << " has " << B->getHp() << " hp!" << endl;
    
    delete A;
    delete B;
    
	cout << "Conta PG: " << Personaggio::CHARACTER_COUNT << endl;
	
    return 0;
}