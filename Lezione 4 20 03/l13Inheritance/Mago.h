#ifndef _MAGO_H
#define _MAGO_H

// MOSTRARE COME L'OVERLOAD NASCONDE ( Mago::foo(double) nasconde Personaggio::foo(int) ) e la parola chiave using Personaggio::foo per ovviare
#include "Personaggio.h"

class Mago : public Personaggio 
{
	public:
	Mago(char* n,int h,int s,int d,int c,int m,int w,int ch);
    virtual ~Mago();
	
	virtual void castSpellUpon(Personaggio& target, int castingTime); // NUOVA FUNZIONE DELLA CLASSE MAGO, non potro' richiamarla da un Personaggio* senza fare cast
	int CalculateSpellDamage(int stat) const; // NUOVA FUNZIONE DELLA CLASSE MAGO, non potro' richiamarla da un Personaggio* senza fare cast
	
	virtual void deathRattle() override; 
	
    virtual void attacks(Personaggio& target) override;  
	
	virtual void levelUp() final override; // FINAL OVERRIDE le classi figlie di Mago non potranno fare l'override di questa funzione
	// Il final puo' essere utilizzato pure sulla classe 'final class NomeClasse' il che vuol dire che la classe non potra' essere estesa
	
	void greetings();
};

#endif