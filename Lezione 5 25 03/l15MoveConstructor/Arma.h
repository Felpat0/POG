#ifndef _ARMA_H
#define _ARMA_H

#include <iostream>

// Articolo interessante sull'overload degli operatori : http://www.tutorialspoint.com/cplusplus/cpp_overloading.htm

class Arma
{
    private:
    int minDmg;
    int maxDmg;
    
    int rank; // quante volte e' stata modificata (quante armi ha assimilato)
    
	
	
    public:
    static const int NAME_MAX_LENGTH = 16;
	Arma();
    Arma(int min, int max);
    Arma(int min, int max, int r); 
    ~Arma();
	Arma(const Arma& a ) = default; 
    
    int CalculateDamage(int stat) const;
    
    // Voglio aggiungere degli operatori alla classe Arma 
    // Per dare la possibilita' di modificare l'arma, volendo
    
    // MODIFICHE
    
    // FUSIONE: fondere due armi restituisce una nuova Arma con i valori migliori per ciascun campo, il nome cambia in "Fusione"
    // Arma fusione = arma1 + arma2;
    Arma operator+(const Arma& a) const; // Operatore binario, l'argomento e' l'elemento a destra dell'operatore 
        
    // ASSIMILAZIONE : assimilare un'arma vuol dire aumentare i parametri dell'arma base con i bonus di quella in argomento, il rank di quella base aumenta
    // armaBase += armaAssimilata;
    void operator+=(const Arma& a); // Operatore di assegnazione, l'argomento e' l'elemento a destra
        
    // AUTOASSIMILAZIONE : l'arma assimila se stessa
    // ++arma;
    Arma operator++(); // Operatore di incremento, senza parametro si effettua l'overloading di ++var; (prefix)
    
    // arma++;
    Arma operator++(int); // Operatore di incremento, col parametro 'int' si effettua l'overloading di var++; (postfix)
    
    // Overload operatore di inserimento (da mandare al cout, per intenderci)
	friend std::ostream& operator<<( std::ostream &output, const Arma &a );
};

#endif