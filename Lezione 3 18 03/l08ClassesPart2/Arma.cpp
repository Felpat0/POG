#include "Arma.h"
#include <iostream>
#include <cstdlib> // srand, rand
#include <ctime> // time


Arma::Arma(char* n, int min, int max): name((char*)n), minDmg(min), maxDmg(max) 
{

}


Arma::~Arma()
{
    // delete [] name; // <- NO perche' gli passo una string literal, in altri casi pero' potrebbe essere utile
}

int Arma::CalculateDamage(int stat)
{
    srand ( time(NULL ) ); // prepara il seed
    int damage = rand() % (maxDmg - minDmg);   
    damage += minDmg; // porto "damage" tra minDmg e maxDmg
    damage = ( damage * stat ) / 10; // per ogni punto di stat a partire da 10 aumento il danno del 10%
    
    std::cout << "using " << name << " inflicts " << damage << " damage!" << std::endl;
    return damage;
}