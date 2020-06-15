#ifndef _ARMA_H
#define _ARMA_H

class Arma
{
    private:
    char* name;
    int minDmg;
    int maxDmg;
    
    public:
    Arma(char* n, int min, int max);
    ~Arma();
        
    int CalculateDamage(int stat);
};

#endif