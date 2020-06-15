#ifndef _ASSASSINO_H
#define _ASSASSINO_H


#include "Personaggio.h"
#include "Ladro.h"


class Assassino : public Ladro 
{
	
	public:
	Assassino(char* n,int h,int s,int d,int c,int m,int w,int ch);
	Assassino(char* n,int h,int s,int d,int c,int m,int w,int ch,int lck);
    virtual ~Assassino();
	
	virtual void deathRattle() override; // override -> specifico che sto facendo l'override di una funzione della classe madre
	
	virtual void attacks(Personaggio& pg) override;

	void greetings();
	
	void levelUp() override; 
};

#endif