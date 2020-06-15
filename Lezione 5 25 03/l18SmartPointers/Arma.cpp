#include "Arma.h"
#include <iostream>
#include <cstdlib> // srand, rand
#include <ctime> // time

using namespace std;

Arma::Arma()
{
	minDmg = 0;
	maxDmg = 1;
	rank = 1;
}

Arma::Arma( int min, int max): minDmg(min), maxDmg(max) 
{
    rank = 1;
}

Arma::Arma( int min, int max, int r): minDmg(min), maxDmg(max), rank(r)
{
}

Arma::~Arma()
{
    cout << "Deleting Weapon " << *this << " " << this << endl;
}
    

int Arma::CalculateDamage(int stat) const
{
    srand ( time(NULL ) ); // prepara il seed
    int damage = rand() % maxDmg; // numero tra 1 e maxDmg
    damage += minDmg; // porto "damage" tra minDmg e maxDmg
    damage = ( damage * stat ) / 10; // per ogni punto di stat aumento il danno del 10%
    
    cout << " inflicts " << damage << " damage!" << endl;
    return damage;
}

// OVERLOAD OPERATORI

// FUSIONE: fondere due armi restituisce una nuova Arma con i valori migliori per ciascun campo, il nome cambia in "Fusione"
// Arma fusione = arma1 + arma2;
Arma Arma::operator+(const Arma& a) const// Operatore binario, l'argomento e' l'elemento a destra dell'operatore 
{
    Arma result;
    result.minDmg = minDmg + a.minDmg;
    result.maxDmg = maxDmg + a.maxDmg;
    if ( result.minDmg > result.maxDmg ) result.maxDmg = result.minDmg;
    
    result.rank = rank + a.rank ;
        
    return result;
}
    
// ASSIMILAZIONE : assimilare un'arma vuol dire aumentare i parametri dell'arma base con i bonus di quella in argomento, il rank di quella base aumenta
// armaBase += armaAssimilata;
void Arma::operator+=(const Arma& a) // Operatore di assegnazione, l'argomento e' l'elemento a destra
{
    minDmg += a.minDmg;
    maxDmg += a.maxDmg;
    if ( minDmg > maxDmg ) maxDmg = minDmg;
        
    rank+= a.rank;
}
    
// AUTOASSIMILAZIONE : l'arma assimila se stessa
// ++arma;
Arma Arma::operator++() // Operatore di incremento, senza parametro si effettua l'overloading di ++var; (prefix)
{
    minDmg += minDmg;
    maxDmg += maxDmg;
    if ( minDmg > maxDmg ) maxDmg = minDmg;
        
    rank++;
      
    return Arma(minDmg,maxDmg,rank);
}
// arma++;
Arma Arma::operator++(int) // Operatore di incremento, col parametro 'int' si effettua l'overloading di var++; (postfix)
{
    cout << " arma++ " << endl;
    Arma a = *this;
		
    cout << " incremento " << endl;
    ++*this; // Anche il ++arma restituisce un'arma, che non sta venendo assegnata a nessuno, quindi viene distrutta
        
    cout << " restituisco la copia" << endl;
    return a;
}

// overload dell'operatore di inserimento
// NON e' nello scope della classe, quindi la struttura e' :  returnType operator ( elementoASinistra, elementoADestra) (come nel caso degli Enum)
// nel caso specifico fa l'overload di:    cout << oggettoArma; 
// cout : elemento di sinistra (di tipo ostream )
// oggettoArma : elemento di destra (di tipo const Arma& )
ostream& operator<<( ostream& output, const Arma &a ) // Non devo ripetere il friend
{
	output << "Weapon Rank : " << a.rank << " Damage : " << a.minDmg << " - " << a.maxDmg;
	return output;
}