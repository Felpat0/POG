#ifndef _ARMA_H
#define _ARMA_H

class Arma
{
    private:
    char* name;
    int minDmg;
    int maxDmg;
    
    public:
    static const int NAME_MAX_LENGTH = 16;
    Arma(char* n, int min, int max);
    ~Arma();
    
    int CalculateDamage(int stat);
};

#endif