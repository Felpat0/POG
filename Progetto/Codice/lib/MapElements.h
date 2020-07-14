#ifndef _ELEMENTS_H
#define _ELEMENTS_H
#include "Characters.h"


class Door{
    private:
    std::string roomLabel;
    int id;
    int x;
    int y;
    int connectedDoorId;
    int connectedRoomId;
    bool locked;
    std::string chUnlocked;
    std::string chLocked;

    public:
    Door(int id, int x, int y, int connectedDoorId, int connectedRoomId, bool locked, std::string chUnlocked, std::string chLocked);
    Door(int id, int x, int y, bool locked, std::string chUnlocked, std::string chLocked);
    
    unsigned int getId() const;
    unsigned int getX() const;
    unsigned int getY() const;
    unsigned int getConnectedDoorId() const;
    unsigned int getConnectedRoomId() const;
    bool isLocked() const;
    std::string getChUnlocked() const;
    std::string getChLocked() const;

    void setConnectedDoorId(unsigned int id);
    void setConnectedRoomId(unsigned int id);
};

class Room{
    public:
    int id;
    std::string label;
    int x;
    int y;
    int w;
    int h;
    std::string chWall;
    std::string chFloor;
    std::vector<std::unique_ptr<Door>> doors;
    //public:

    Room(int id, std::string chWall, std::string chFloor);
    Room(int id, int newX, int newY, int width, int height, std::string chWall, std::string chFloor);

    int getId() const;
    std::string getLabel() const;
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    std::string getChWall() const;
    std::string getChFloor() const;

    bool addDoor(std::unique_ptr<Door>& door);
};


class Game{
    //private:
    public:
    int w;
    int h;
    int exitX;
    int exitY;
    float lapsedTime;
    int m[MAX_MATRIX_HEIGHT][MAX_MATRIX_WIDTH];
    bool fogMatrix[MAX_MATRIX_HEIGHT][MAX_MATRIX_WIDTH];

    std::vector<std::unique_ptr<Room>> rooms;
    std::vector<std::unique_ptr<Enemy>> enemies; 
    std::vector<std::unique_ptr<Enemy>> bestiaryEnemies;//This will contain each type of enemy that is available (in single copy)
    std::vector<std::unique_ptr<InventoryElement>> items;
    std::vector<InventoryElement> inventoryItems; //This will contain each type of item that is available (in single copy)
    Player* player;
    std::vector<std::unique_ptr<Weapon>> weapons;
    std::vector<Weapon> inventoryWeapons; //This will contain each type of item that is available (in single copy)
    std::string chExit;
    std::string chPath;
    std::string chFog;

    public:
    Game();
    //~Game();

    void generateMap();
    void initMap();
    void exportMap();
    void printInterface();
    bool isWalkable(int x, int y);
    bool isWalkableForPlayer(int x, int y);
    int getElementType(int i, int j) const;
    void addRoom(std::unique_ptr<Room>& room);
    void addRoom(int id, std::string chWall, std::string chFloor);
    int isColliding(Room& room1, Room& room2);
    bool linkRooms();
    bool createPath(Room& room1, Room& room2, int& doorsCounter);
    bool linkRoomsByDoors();
    bool createPathByDoors(Door& door1, Door& door2, int roomId);

    void chooseClass();
    void clearFog();
    void moveEnemies();
    int getDistance(Character& a, Character& b) const;
    int getDistance(int x1, int y1, int x2, int y2) const;
    void getBestiary();
    void getItems();

    void printUnicode(std::string character) const;
    bool areStringsEqual(std::string a, std::string b);
};
#endif