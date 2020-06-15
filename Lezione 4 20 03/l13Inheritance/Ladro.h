#ifndef _LADRO_H
#define _LADRO_H

#include "Personaggio.h"


class Ladro : public Personaggio 
{
	protected:
	int lck; // Luck, membro solo di Ladro e delle sue sottoclassi
	
	public:
	Ladro(char* n,int h,int s,int d,int c,int m,int w,int ch);
	Ladro(char* n,int h,int s,int d,int c,int m,int w,int ch, int l);
    virtual ~Ladro();
	
	virtual void deathRattle() override; // override -> specifico che sto facendo l'override di una funzione della classe madre
	
    virtual void attacks(Personaggio& target) override; // virtual 
	
	virtual void levelUp() override; // La implemento, cosi' non e' piu' astratta
	
	void greetings(); // override; // <-- Non posso utilizzare la parola override su di un metodo non virtuale della classe madre
	

};

#endif