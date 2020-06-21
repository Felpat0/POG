#ifndef _CHARACTERS_H
#define _CHARACTERS_H
#include "InventoryElements.h"

class Character{
    private:
    int hp;
    unsigned int maxHp;
    unsigned int str;
    unsigned int dex;
    unsigned int mnd;
    unsigned int wis;
    unsigned int res;

    protected:
    unsigned int movementIntention; //0=no movement 1=up 2=down 3=left 4=right
    
    public:
    float movTime;
    float actTime;
    unsigned int x;
    unsigned int y;
    
    Character(unsigned int x, unsigned int y, unsigned int maxHP, unsigned int str, 
    unsigned int dex, unsigned int mnd, unsigned int wis, unsigned int res, 
    float movTime, float actTime);

    int getMovementIntention() const;
    void resetMovementIntention();
    void setCoordinates(const int x, const int y);
    int getX()const;
    int getY()const;
};

class Player : public Character{
    public:
    unsigned int lvl;
    unsigned int mp;
    unsigned int maxMp;
    unsigned int exp;
    unsigned int keys;
    unsigned int gp;
    std::vector<std::unique_ptr<InventoryElement>> InventoryElements;

    Player(unsigned int x, unsigned int y, unsigned int MaxMp, unsigned int maxHP, unsigned int str, 
    unsigned int dex, unsigned int mnd, unsigned int wis, unsigned int res, 
    float movTime, float actTime);
    int input(const std::string command);
    void setMovementIntention(const std::string direction);
};

class Warrior : public Player{
    public:
    Warrior(unsigned int x, unsigned int y);
};

class Enemy : public Character{
    private:
    float nextActTime;
    unsigned int attackRange;
    unsigned int sightRange;
    std::string attackStat; //Does it use str, dex or mnd?
    std::string label;

    public:
    Enemy(unsigned int x, unsigned int y, unsigned int maxHP, unsigned int str, 
    unsigned int dex, unsigned int mnd, unsigned int wis, unsigned int res, 
    float movTime, float actTime, std::string attackStat, unsigned int attackRange, unsigned int sightRange, std::string label);

    float getNextActTime() const;
    float getActTime() const;
    float getMovTime() const;
    void setNextActTime(float nextActTime);
};

class Goblin : public Enemy{
    public:
    char ch;
    Goblin(unsigned int x, unsigned int y);
};
#endif