#ifndef _ELEMENTS_H
#define _ELEMENTS_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <memory>


#define MAX_ROOM_HEIGHT 9
#define MAX_ROOM_WIDTH 9
#define MAX_X_VALUE 20
#define MAX_Y_VALUE 20
#define MAX_MATRIX_WIDTH 30
#define MAX_MATRIX_HEIGHT 30

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
    char m[MAX_MATRIX_HEIGHT][MAX_MATRIX_WIDTH];
    std::vector<std::unique_ptr<Room>> rooms;

    std::string chExit;
    std::string chPath;

    Game();
    void printBoard();
    void addRoom(Room& room);
    void addRoom();
    int isColliding(Room& room1, Room& room2);
    bool createPath(Room& room1, Room& room2);
    bool linkRooms();
};
#endif