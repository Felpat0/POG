#ifndef _ELEMENTS_H
#define _ELEMENTS_H
#include "Characters.h"


class Door{
    public:
    std::string roomLabel;
    int x;
    int y;
    bool locked;
    std::string chUnlocked;
    std::string chLocked;

    Door(int x, int y);
};

class Room{
    public:
    std::string label;
    int x;
    int y;
    int w;
    int h;
    std::string chWall;
    std::string chFloor;
    std::unique_ptr<Door> door;
    //public:

    Room();
    Room(int width, int height, int newX, int newY);
};



class Game{
    //private:
    public:
    int w;
    int h;
    int exitX;
    int exitY;
    float lapsedTime;
    char m[MAX_MATRIX_HEIGHT][MAX_MATRIX_WIDTH];

    std::vector<std::unique_ptr<Room>> rooms;
    std::vector<std::unique_ptr<Enemy>> enemies;
    Player* player;
    std::string chExit;
    std::string chPath;

    Game();
    //~Game();
    void printBoard();
    public: bool isWalkable(int x, int y);
    void addRoom(Room& room);
    void addRoom();
    int isColliding(Room& room1, Room& room2);
    bool createPath(Room& room1, Room& room2);
    bool linkRooms();

    bool spawnPlayer(std::string playerClass);
    void spawnEnemy(std::string enemyType);
    void moveEnemies();
};
#endif