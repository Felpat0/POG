#ifndef _GUERRIERO_H
#define _GUERRIERO_H

#include "Personaggio.h"


class Guerriero : public Personaggio 
{
	public:
	Guerriero(); 
	Guerriero(char* n,int h,int s,int d,int c,int m,int w,int ch);
    virtual ~Guerriero();
	Guerriero(const Guerriero& g); // Copy Constructor
	Guerriero& operator=(const Guerriero& g); // Copy Assignment
	
	virtual void deathRattle() override; // override -> specifico che sto facendo l'override di una funzione della classe madre
	virtual void deathRat(); // Un possibile tentativo di override di deathRattle andato male per un 'refuso'
	
    virtual void attacks(Personaggio& target) override; // virtual 
	
	void greetings();
	
	virtual void levelUp() override; // La implemento, cosi' non e' piu' astratta
};

#endif