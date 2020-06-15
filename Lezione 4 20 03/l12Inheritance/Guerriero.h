#ifndef _GUERRIERO_H
#define _GUERRIERO_H

#include "Personaggio.h"
/*
Sintassi per l'ereditarieta'

class Child : public Base <--- Child estende Base
		Il Polimorfismo funziona solo coi puntatori, quindi posso scrivere
		Base* object = new Child();
		Ma NON posso scrivere
		Base object = Child();
*/
class Guerriero : public Personaggio 
{
	public:
	Guerriero(); 
	Guerriero(char* n,int h,int s,int d,int c,int m,int w,int ch);
    virtual ~Guerriero();
	
	virtual void deathRattle() override; // override -> specifico che sto facendo l'override di una funzione della classe madre
	virtual void deathRat(); // Un possibile tentativo di override di deathRattle andato male per un 'refuso'
	
    virtual void attacks(Personaggio& target) override; // virtual 
	
	void greetings();
	
	virtual void levelUp() override; // La implemento, cosi' non e' piu' astratta
};

#endif