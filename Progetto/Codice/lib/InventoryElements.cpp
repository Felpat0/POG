#include "InventoryElements.h"

//EFFECT SECTION
Effect::Effect(std::string stat, float value) : stat(stat), value(value){}

std::string Effect::getStat(){return stat;}
float Effect::getValue(){return value;}

//----------------------------------------------------------------------------------------------------

//INVENTORYELEMENT SECTION
InventoryElement::InventoryElement(unsigned int x, unsigned int y, std::string label, std::string type, std::string ch, std::vector<Effect> effects){
    this->label = label;
    this->type = type;
    this->ch = ch;
    this->x = x;
    this->y = y;

    std::vector<Effect> temp = effects;
    std::vector<Effect>::iterator it = temp.begin();
    std::vector<Effect>::iterator end = temp.end();
    for(it; it != end; it++){
        this->effects.push_back(*it);
    }
}

InventoryElement::InventoryElement(unsigned int x, unsigned int y, std::string label, std::string type, std::string ch){
    this->label = label;
    this->type = type;
    this->ch = ch;
    this->x = x;
    this->y = y;
}

InventoryElement::InventoryElement(InventoryElement& element, unsigned int x, unsigned int y){
    this->label = element.getLabel();
    this->type = element.getType();
    this->ch = element.getCh();
    this->x = x;
    this->y = y;
    
    std::vector<Effect> temp = element.getEffect();
    std::vector<Effect>::iterator it = temp.begin();
    std::vector<Effect>::iterator end = temp.end();
    for(it; it != end; it++){
        this->effects.push_back(*it);
    }
}

void InventoryElement::setX(unsigned int x){this->x = x;}
void InventoryElement::setY(unsigned int y){this->y = y;}

int InventoryElement::getX() const{return this->x;}
int InventoryElement::getY() const{return this->y;}
std::string InventoryElement::getLabel() const{return this->label;}
std::string InventoryElement::getType() const{return this->type;}
std::string InventoryElement::getCh() const{return this->ch;}
std::vector<Effect> InventoryElement::getEffect() const{return effects;}

void InventoryElement::addEffect(Effect effect){effects.push_back(effect);}

//----------------------------------------------------------------------------------------------------
//SQUARE SECTION
Square::Square(int fd, int rd, std::string stat, float pot) : fd(fd), rd(rd), pot(pot), stat(stat){}

int Square::gedFd() const{return this->fd;}
int Square::getRd() const{return this->rd;}
float Square::getPot() const{return this->pot;}
std::string Square::getStat() const{return this->stat;}

//----------------------------------------------------------------------------------------------------
//WEAPON SECTION
Weapon::Weapon(unsigned int x, unsigned int y, std::string label, std::string type, std::string ch, unsigned int durability, unsigned int range) : InventoryElement(x, y, label, type, ch){
    this->durability = durability;
    this->range = range;
}

Weapon::Weapon(Weapon& w, unsigned int x, unsigned int y) : InventoryElement(x, y, w.getLabel(), w.getType(), w.getCh(), w.getEffect()){
    this->durability = w.getDurability();
    this->range = w.getRange();

    std::vector<Square> temp = w.getAreasOfEffect();
    std::vector<Square>::iterator it = temp.begin();
    std::vector<Square>::iterator end = temp.end();
    for(it; it != end; it++){
        this->areasOfEffect.push_back(*it);
    }
}

unsigned int Weapon::getDurability() const{return durability;}
unsigned int Weapon::getRange() const{return range;}
std::vector<Square> Weapon::getAreasOfEffect() const{return areasOfEffect;}

void Weapon::addAreasOfEffect(Square area){areasOfEffect.push_back(area);}