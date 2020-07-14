#include "Characters.h"

//----------------------------------------------------------------------------------------------------

//CHARACTER SECTION
Character::Character(unsigned int x, unsigned int y, unsigned int maxHP, float str, 
    float dex, float mnd, float wis, float res, 
    float movTime, float actTime, std::string ch){
        this->x = x;
        this->y = y;
        this->maxHp = maxHP;
        this->hp = maxHp;
        this->str = str;
        this->dex = dex;
        this->mnd = mnd;
        this->wis = wis;
        this->res = res;
        this->movTime = movTime;
        this->actTime = actTime;
        this->movementIntention = 0;
        this->ch = ch;
}

int Character::getMovementIntention() const {return this->movementIntention;}
void Character::resetMovementIntention(){this->movementIntention = 0;}
void Character::setCoordinates(const int x, const int y){
    this->x = x;
    this->y = y;
}
unsigned int Character::getX()const{return this->x;}
unsigned int Character::getY()const{return this->y;}
unsigned int Character::getHP()const{return this->hp;};
unsigned int Character::getMaxHP()const{return this->maxHp;};
float Character::getStr() const{return this->str;}
float Character::getDex() const{return this->dex;}
float Character::getMnd() const{return this->mnd;}
float Character::getWis() const{return this->wis;}
float Character::getRes() const{return this->res;}
float Character::getMovTime() const{return this->movTime;}
float Character::getActTime() const{return this->actTime;}
std::string Character::getCh() const{return this->ch;}

//----------------------------------------------------------------------------------------------------

//PLAYER SECTION
Player::Player (std::string name, unsigned int x, unsigned int y, unsigned int maxMp, unsigned int maxHP, float str, 
    float dex, float mnd, float wis, float res, 
    float movTime, float actTime, std::string playerClass, std::string ch) :
    Character(x, y, maxHP, str, dex, mnd, wis, res, movTime, actTime, ch){
        this->name = name;
        this->lvl = 1;
        this->exp = 0;
        this->gp = 0;
        this->maxMp = maxMp;
        this->mp = maxMp;
        this->keys = 0;
        this->playerClass = playerClass;
}
std::string Player::getName() const{return this->name;}
unsigned int Player::getLvl() const{return this->lvl;}
unsigned int Player::getMaxMP()const{return this->maxMp;}
int Player::getMP()const{return this->mp;}
unsigned int Player::getExp() const{return this->exp;}
unsigned int Player::getKeys() const{return this->keys;}
unsigned int Player::getGp() const{return this->gp;}
unsigned int Player::getInventorySize() const{return this->inventoryElements.size();}
std::string Player::getPlayerClass() const{return this->playerClass;}
InventoryElement Player::getInventoryElementAt(unsigned int n) const{return *(inventoryElements.at(n));}

int Player::input(std::string command){
    if(command == "w" || command == "a" || command == "s" || command == "d" || command == "W" || command == "A" || command == "S" || command == "D"){
        setMovementIntention(command);
        return 1;
    }
    return 0;
}

void Player::setMovementIntention(std::string direction){ 
    //0=no movement 1=up 2=down 3=left 4=right
    if(direction == "w" || direction == "W"){
            movementIntention = 1;
    }else if(direction == "a" || direction == "A"){
            movementIntention = 3;
    }else if(direction == "s" || direction == "S"){
            movementIntention = 2;
    }else if(direction == "d" || direction == "D"){
            movementIntention = 4;
    }
}

void Player::addInventoryElement(std::unique_ptr<InventoryElement>& element){
    element->setX(0);
    element->setY(0);
    this->inventoryElements.push_back(std::move(element));
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------

//ENEMY SECTION
Enemy::Enemy(unsigned int x, unsigned int y, unsigned int maxHP, float str, 
    float dex, float mnd, float wis, float res, 
    float movTime, float actTime, std::string attackStat, unsigned int attackRange, unsigned int sightRange, unsigned int exp, unsigned int gp, std::string label, std::string ch) : Character(x, y, maxHP, str, dex, mnd, wis, res, movTime, actTime, ch){
        this->nextActTime = 0;     
        this->attackStat = attackStat;
        this->attackRange = attackRange;
        this->sightRange = sightRange;
        this->exp = exp;
        this->gp = gp;
        this->label = label;
}

Enemy::Enemy(const Enemy& e, unsigned int x, unsigned int y) : Character(x, y, e.getMaxHP(), e.getStr(), e.getDex(), e.getMnd(), e.getWis(), e.getRes(), e.getMovTime(), e.getActTime(), e.getCh()){
    this->nextActTime = e.getNextActTime();     
    this->attackStat = e.getAttackStat();
    this->attackRange = e.getAttackRange();
    this->sightRange = e.getSightRange();
    this->exp = e.getExp();
    this->gp = e.getGp();
    this->label = e.getLabel();
}


float Enemy::getNextActTime() const{return this->nextActTime;}
void Enemy::setNextActTime(float nextActTime){this->nextActTime = nextActTime;}
std::string Enemy::getAttackStat() const{return this->attackStat;}
std::string Enemy::getLabel() const {return this->label;}
unsigned int Enemy::getAttackRange() const{return this->attackRange;}
unsigned int Enemy::getSightRange() const{return this->sightRange;}
unsigned int Enemy::getExp() const{return this->exp;}
unsigned int Enemy::getGp() const{return this->gp;}
