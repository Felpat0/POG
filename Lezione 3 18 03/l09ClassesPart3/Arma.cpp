#include "Arma.h"
#include <iostream>
#include <cstdlib> // srand, rand
#include <ctime> // time

Arma::Arma(char* n, int min, int max): name((char*)n), minDmg(min), maxDmg(max) {}


Arma::~Arma()
{
    delete [] name; // Adesso serve perche' non passo piu' una string literal!!
}
    
int Arma::CalculateDamage(int stat)
{
    srand ( time(NULL ) ); // prepara il seed
    int damage = rand() % maxDmg; // numero tra 1 e maxDmg
    damage += minDmg; // porto "damage" tra minDmg e maxDmg
    damage = ( damage * stat ) / 10; // per ogni punto di stat aumento il danno del 10%
    
    std::cout << "using " << name << " inflicts " << damage << " damage!" << std::endl;
    return damage;
}