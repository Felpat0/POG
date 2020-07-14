#ifndef _INVENTORY_H
#define _INVENTORY_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <memory>
#include <fstream>
#include <ctype.h>

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"


#define MAX_ROOM_HEIGHT 9
#define MAX_ROOM_WIDTH 9
#define MAX_X_VALUE 90
#define MAX_Y_VALUE 90
#define MAX_MATRIX_WIDTH 100
#define MAX_MATRIX_HEIGHT 100
#define MAP_WIDTH 81
#define MAP_HEIGHT 21
#define ROOMS_NUMBER 15
#define PLAYER_SIGHT 10
#define MIN_ENEMIES_NUMBER 0
#define MAX_ENEMIES_NUMBER 2
#define MIN_ITEMS_NUMBER 1
#define MAX_ITEMS_NUMBER 2
#define MIN_CHEST_NUMBER 0
#define MAX_CHESTS_NUMBER 1

class Effect{
    private:
    std::string stat;
    float value;

    public:
    Effect(std::string stat, float value);
    std::string getStat();
    float getValue();
};

class InventoryElement{
    protected:
    int x;
    int y;
    std::string label;
    std::string type;
    std::string ch;
    std::vector<Effect> effects;

    public:
    InventoryElement(unsigned int x, unsigned int y, std::string label, std::string type, std::string ch, std::vector<Effect> effects);
    InventoryElement(unsigned int x, unsigned int y, std::string label, std::string type, std::string ch);
    InventoryElement(InventoryElement& element, unsigned int, unsigned int y);

    void setX(unsigned int x);
    void setY(unsigned int y);

    int getX() const;
    int getY() const;
    std::string getLabel() const;
    std::string getType() const;
    std::string getCh() const;
    std::vector<Effect> getEffect() const;

    void addEffect(Effect effect);
};

class Square{
    private:
    int fd; //Forward distance (where the player directed the attack)
    int rd; //Right distance (next direction clockwise)
    float pot;
    std::string stat;

    public:
    Square(int fd, int rd, std::string stat, float pot);

    int gedFd() const;
    int getRd() const;
    float getPot() const;
    std::string getStat() const;
};

class Weapon : public InventoryElement{
    private:
    unsigned int durability;
    unsigned int range;
    std::vector<Square> areasOfEffect;

    public:
    Weapon(unsigned int x, unsigned int y, std::string label, std::string type, std::string ch, unsigned int durability, unsigned int range);
    Weapon(Weapon& w, unsigned int x, unsigned int y);

    unsigned int getDurability() const;
    unsigned int getRange() const;
    std::vector<Square> getAreasOfEffect() const;

    void addAreasOfEffect(Square area);
};

#endif