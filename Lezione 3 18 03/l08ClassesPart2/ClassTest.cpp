#include <iostream>
#include "Personaggio.h"
#include "Arma.h"


using namespace std;

int main()
{
    // Costruttore Personaggio (char* n,int h,int s,int d,int c,int m,int w,int ch);
    Personaggio* A = new Personaggio((char*)"Ajeje", 10, 16, 12, 12, 12, 12, 10 );
    Personaggio* B = new Personaggio((char*)"Brazof", 8, 10, 12, 12, 12, 12, 10 );
    
    Arma* spada = new Arma( (char*)"Spada", 8, 10 );
    
    A->setArma( spada );
    
    cout << B->getName() << " has " << B->getHp() << " hp!" << endl;
    A->attacks( *B ); // <- Dereferenzio e NON passo l'indirizzo!
    // Perche' la funzione prende in input una reference e non un puntatore
    cout << B->getName() << " has " << B->getHp() << " hp!" << endl;
    
    delete A;
    delete B;
    
    return 0;
}