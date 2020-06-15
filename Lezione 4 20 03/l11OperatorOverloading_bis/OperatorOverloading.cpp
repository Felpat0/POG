#include <iostream>
#include "Personaggio.h"
#include "Arma.h"

using namespace std;

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
    
    Arma* pspada = new Arma((char*)"Spada" , 8, 10 );
    
    A->setArma( pspada );
    
    cout << B->getName() << " has " << B->getHp() << " hp!" << endl;
    A->attacks( *B );
    cout << B->getName() << " has " << B->getHp() << " hp!" << endl;
    
    delete A;
    delete B;
    
	// Giochiamo con gli operatori delle armi
	
	// 					Tipo 	   min / max / rank / bonusMin / bonusMax
	Arma spada ((char*)"Spada",4,8);
	Arma ascia ((char*)"Ascia",2,12);
	Arma lancia ((char*)"Lancia",5,7);
	Arma arco ((char*)"Arco",4,12);
	Arma scettro ((char*)"Scettro",8,8);
	
	cout << endl << endl << "\tLe Armi di Base " << endl;
	cout << spada << endl << ascia << endl << lancia << endl << arco << endl << scettro << endl;
	
	Arma fusione1 = spada + lancia;
	
	cout << "Fusione = Spada + Lancia " << endl << fusione1 << endl;
	
	spada += lancia; 
	
	cout << "Spada += Lancia " << endl << spada << endl;
	
	spada += fusione1;
	
	cout << "Spada += Fusione " << endl << spada << endl;
	
	Arma semplice ((char*)"Semplice",0,0);
	
	cout << "Test sull'incremento " << endl << semplice << endl;
	cout << ++semplice << endl;
	cout << semplice++ << endl;
	cout << semplice << endl;
	
    return 0;
}