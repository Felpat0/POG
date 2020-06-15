#ifndef _ARMA_H
#define _ARMA_H

#include <iostream>

// Articolo interessante sull'overload degli operatori : http://www.tutorialspoint.com/cplusplus/cpp_overloading.htm

class Arma
{
    private:
    char* name;
    int minDmg;
    int maxDmg;
    
    int rank; // quante volte e' stata modificata (quante armi ha assimilato)
	
	
    public:
    static const int NAME_MAX_LENGTH = 16;
	Arma();
    Arma(char* n, int min, int max);
    Arma(char* n, int min, int max, int r);
    ~Arma();
    
    int CalculateDamage(int stat);
    
    // Voglio aggiungere degli operatori alla classe Arma 
    // Per dare la possibilita' di modificare l'arma, volendo
    
    // MODIFICHE
    
    // FUSIONE: fondere due armi restituisce una nuova Arma ommando i valori per ciascun campo, il nome cambia in "Fusione"
    // Arma fusione = arma1 + arma2;
    Arma operator+(const Arma& a) const; // Operatore binario, l'argomento e' l'elemento a destra dell'operatore 

    // ASSIMILAZIONE : come la fusione ma invece di restituire una nuova arma, modifica quella attuale
    // armaBase += armaAssimilata;
    void operator+=(const Arma& a); // Operatore di assegnazione, l'argomento e' l'elemento a destra
        
    // AUTOPOTENZIAMENTO : l'arma si potenzia da se
    // ++arma;
    Arma operator++(); // Operatore di incremento, senza parametro si effettua l'overloading di ++var; (prefix)
    
    // arma++;
    Arma operator++(int); // Operatore di incremento, col parametro 'int' si effettua l'overloading di var++; (postfix)
    

    // cout << arma;
    // Overload operatore di inserimento (da mandare al cout, per intenderci)
	friend std::ostream& operator<<( std::ostream &output, const Arma &a );
    // il primo parametro e' l'elemento che stara' a sinistra, il secondo e' l'elemento che stara' a destra (il nostro oggetto arma)

    // La parola chiave 'friend' conferisce al metodo (o alla classe) dichiarata la capacita' di accedere ai campi privati e protetti
    // di questa classe. In questo modo stiamo facendo un override dell'operatore  << non richiamato da questa classe
    // (lo useremo come std::cout << unArma ) e quindi di norma non potremmo accedere ai campi di questa classe 
    // definendolo cosi' invece aggiriamo questo limite!
};

#endif