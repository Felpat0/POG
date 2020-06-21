#include "Characters.h"

//CHARACTER SECTION

Character::Character(unsigned int x, unsigned int y, unsigned int maxHP, unsigned int str, 
    unsigned int dex, unsigned int mnd, unsigned int wis, unsigned int res, 
    float movTime, float actTime){
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
}

int Character::getMovementIntention() const {return this->movementIntention;}
void Character::resetMovementIntention(){this->movementIntention = 0;}
void Character::setCoordinates(const int x, const int y){
    this->x = x;
    this->y = y;
}
int Character::getX()const{return this->x;}
int Character::getY()const{return this->y;}

//PLAYER SECTION
Player::Player (unsigned int x, unsigned int y, unsigned int MaxMp, unsigned int maxHP, unsigned int str, 
    unsigned int dex, unsigned int mnd, unsigned int wis, unsigned int res, 
    float movTime, float actTime) :
    Character(x, y, maxHP, str, dex, mnd, wis, res, movTime, actTime){
        this->lvl = 1;
        this->exp = 0;
        this->gp = 0;
        this->maxMp = maxMp;
        this->mp = maxMp;
        this->keys = 0;
}

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

//WARRIOR SECTION
Warrior::Warrior(unsigned int x, unsigned int y) : Player(x, y, 0, 20, 4, 2, 1, 2, 3, 1, 2){
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------

//ENEMY SECTION
Enemy::Enemy(unsigned int x, unsigned int y, unsigned int maxHP, unsigned int str, 
    unsigned int dex, unsigned int mnd, unsigned int wis, unsigned int res, 
    float movTime, float actTime, std::string attackStat, unsigned int attackRange, unsigned int sightRange, std::string label) : Character(x, y, maxHP, str, dex, mnd, wis, res, movTime, actTime){
        this->nextActTime = 0;     
        this->attackStat = attackStat;
        this->attackRange = attackRange;
        this->sightRange = sightRange;
        this->label = label;
}
float Enemy::getActTime() const{return this->actTime;}
float Enemy::getMovTime() const{return this->movTime;}
float Enemy::getNextActTime() const{return this->nextActTime;}
void Enemy::setNextActTime(float nextActTime){this->nextActTime = nextActTime;}

//GOBLIN SECTION
Goblin::Goblin(unsigned int x, unsigned int y) : Enemy(x, y, 6, 4, 2, 1, 1, 0, 1.5, 2.5, "str", 1, 4, "Goblin"){
    this->ch = 0x0047;
}
