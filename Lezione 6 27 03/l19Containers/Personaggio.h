#ifndef _PERSONAGGIO_H
#define _PERSONAGGIO_H

// La regola del 5: Se avete anche solo uno tra questi dovete implementarli tutti
// Distruttore
// Copy Constructor
// Copy Assignment
// Move Constructor
// Move Assignment

#include "Arma.h"
#include <memory>

using namespace std;

class Personaggio
{
    private:
	string name;
	
	protected: // Le classi che la derivano possono accedervi
	int lvl;
    int mHp;
    int hp;
    int str;
    int dex;
    int con;
    int mnd;
    int wis;
    int cha;
    shared_ptr<Arma> equip;
    
    public:
	Personaggio();
    Personaggio(string n,int h,int s,int d,int c,int m,int w,int ch);
    virtual ~Personaggio();
	Personaggio(const Personaggio& pg); // Copy constructor
	Personaggio& operator=(const Personaggio& pg); // Copy assignment
	
	// Personaggio&& indica un 'rvalue' di tipo Personaggio
	Personaggio(Personaggio&& pg); // Move constructor
	Personaggio& operator=(Personaggio&& pg); // Move assignment
	
	static int CHARACTER_COUNT; // <- se non sono const posso solo dichiararle, vanno definite in uno scope global
	// E' consigliato evitare di definirle nell'header, meglio farlo nei cpp o nel main
    static const int NAME_MAX_LENGTH = 16;
	
    
    inline const string getName() const { return name;  }
	inline void setName(string n) { name = n; }
    inline const int& getHp() const { return hp; }
    inline const Arma& getArma() const { return *equip; }
	inline Arma& getNonConstArma() { return *equip; }
	inline shared_ptr<Arma> getArmaPtr() { return equip; }
	inline const shared_ptr<Arma> getArmaPtr() const { return equip; }
    inline void setArma(shared_ptr<Arma> a) { equip = a; }
	inline void setHp(int h) { hp = h; }
    
	void greetings(); // non e' virtuale, le classi figlie potranno fare l'override ma non sara' 'bindato dinamicamente'
	
    virtual void deathRattle(); // virtual -> vuol dire che posso fare l'override dalle sottoclassi
    void increaseHp(int value );
    const int& getSTR() const;
    const int& getDEX() const;
    const int& getCON() const;
    const int& getMND() const;
    const int& getWIS() const;
    const int& getCHA() const;
    
    void increaseHP(int value);
    void increaseSTR(int value);
    void increaseDEX(int value);
    void increaseCON(int value);
    void increaseMND(int value);
    void increaseWIS(int value);
    void increaseCHA(int value);
    virtual void attacks(Personaggio& target); // virtual 
	
	virtual void levelUp() = 0; // <---- metodo ASTRATTO devo implementarlo nelle sottoclassi, non posso instanziare Personaggio
};

#endif 