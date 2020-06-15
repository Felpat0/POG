#ifndef _ELEMENTALISTA_H
#define _ELEMENTALISTA_H

#include "Mago.h"

class Elementalista : public Mago 
{
	public:
	Elementalista(char* n,int h,int s,int d,int c,int m,int w,int ch);
    virtual ~Elementalista();
	 
	//using Mago::castSpellUpon; // <- Permette di rendere visibile la funzione della classe Mago anche in caso di parametri implicitamente convertibili
	// cosi' da far funzionare l'overload di
	virtual void castSpellUpon(Personaggio& target, char element); // E' cambiata la FIRMA (c'e' char) vedremo come questo NASCONDA la funzione della classe madre
	
	virtual void deathRattle() override; 
	
    virtual void attacks(Personaggio& target) override;  
	
	//virtual void levelUp(); // <-- NON POSSO IMPLEMENTARLO PERCHE' NELLA CLASSE MADRE E' FINAL
	
	void greetings();
};


#endif