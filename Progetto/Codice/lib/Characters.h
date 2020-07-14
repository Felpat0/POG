#ifndef _CHARACTERS_H
#define _CHARACTERS_H
#include "InventoryElements.h"


class Character{
    protected:
    int hp;
    unsigned int maxHp;
    float str;
    float dex;
    float mnd;
    float wis;
    float res;
    float movTime;
    float actTime;
    unsigned int x;
    unsigned int y;
    std::string ch;

    protected:
    unsigned int movementIntention; //0=no movement 1=up 2=down 3=left 4=right
    
    public:
    
    Character(unsigned int x, unsigned int y, unsigned int maxHP, float str, 
    float dex, float mnd, float wis, float res, 
    float movTime, float actTime, std::string ch);

    int getMovementIntention() const;
    void resetMovementIntention();
    void setCoordinates(const int x, const int y);
    unsigned int getX() const;
    unsigned int getY() const;
    unsigned int getHP() const;
    unsigned int getMaxHP() const;
    float getStr() const;
    float getDex() const;
    float getMnd() const;
    float getWis() const;
    float getRes() const;
    float getMovTime() const;
    float getActTime() const;

    std::string getCh() const;
};

class Player : public Character{
    private:
    std::string name;
    unsigned int lvl;
    unsigned int mp;
    unsigned int maxMp;
    unsigned int exp;
    unsigned int keys;
    unsigned int gp;
    unsigned int upHpMax;
    unsigned int upMpMax;
    unsigned int upStr;
    std::string playerClass;
    std::vector<std::unique_ptr<InventoryElement>> inventoryElements;

    public:
    Player(std::string name, unsigned int x, unsigned int y, unsigned int maxMp, unsigned int maxHP, float str, 
    float dex, float mnd, float wis, float res, 
    float movTime, float actTime, std::string playerClass, std::string ch);
    std::string getName() const;
    unsigned int getLvl() const;
    int getMP() const;
    unsigned int getMaxMP() const;
    unsigned int getExp() const;
    unsigned int getKeys() const;
    unsigned int getGp() const;
    unsigned int getInventorySize() const;
    std::string getPlayerClass() const;
    InventoryElement getInventoryElementAt(unsigned int n) const;

    int input(const std::string command);
    void setMovementIntention(const std::string direction);
    void addInventoryElement(std::unique_ptr<InventoryElement>& element);
};


class Enemy : public Character{
    private:
    float nextActTime;
    unsigned int attackRange;
    unsigned int sightRange;
    unsigned int exp;
    unsigned int gp;
    std::string label;
    std::string attackStat; //Does it use str, dex or mnd?
    
    public:

    Enemy(unsigned int x, unsigned int y, unsigned int maxHP, float str, 
    float dex, float mnd, float wis, float res, 
    float movTime, float actTime, std::string attackStat, unsigned int attackRange, 
    unsigned int sightRange, unsigned int exp, unsigned int gp, std::string label, std::string ch);
    Enemy(const Enemy& e, unsigned int x, unsigned int y);

    float getNextActTime() const;
    void setNextActTime(float nextActTime);
    std::string getAttackStat() const;
    std::string getLabel() const;
    unsigned int getAttackRange() const;
    unsigned int getSightRange() const;
    unsigned int getExp() const;
    unsigned int getGp() const;
};

#endif