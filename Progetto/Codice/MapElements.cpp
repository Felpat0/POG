#include "MapElements.h"
//GAME SECTION
//Game constructor
Game::Game(){
    for (int i = 0; i != MAX_MATRIX_HEIGHT -1; i++) {
		for (int j = 0; j != MAX_MATRIX_WIDTH -1; j++) {
            m[i][j] = ' ';
		}
	}
}


//Game functions
void Game::printBoard(){
    for (int i = 0; i != MAX_MATRIX_HEIGHT -1; i++) {
		for (int j = 0; j != MAX_MATRIX_WIDTH -1; j++) {
            std::cout<<m[i][j];
		}
		std::cout << std::endl;
	}
}

void Game::addRoom(Room& room){
    rooms.push_back(std::move(std::unique_ptr<Room>(new Room(room.w, room.h, room.x, room.y))));
    for(int i = room.y; i != room.y + room.h; i++){
        for(int j = room.x; j != room.x + room.w; j++){
            if((j != room.x && i != room.y) && (j != room.x + room.w - 1 && i != room.y + room.h -1))
                m[i][j] = ' ';
            else
                m[i][j] = 'X';
        }
    }
}

void Game::addRoom(){
    bool ok = false;
    std::unique_ptr<Room> room;
    while(!ok){
        ok = true;
        room = std::unique_ptr<Room>(new Room());
        std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
        for (std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin(); it != end; it++ ){
            if(isColliding(*room, **it) == 1)
                ok = false;
        }
    }
    bool isEdge = false;
    std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
    for(int i = (*room).y; i != (*room).y + (*room).h; i++){
        for(int j = (*room).x; j != (*room).x + (*room).w; j++){
            isEdge = false;
            for (std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin(); it != end; it++ ){
                if((i == (**it).y && j == (**it).x) || (i == (**it).y + (**it).h -1 && j == (**it).x) || (i == (**it).y && j == (**it).x + (**it).w -1) || (i == (**it).y + (**it).h -1 && j == (**it).x + (**it).w -1)){
                    isEdge = true;
                }
            }
            if((i == room->y && j == room->x) || (i == room->y + room->h -1 && j == room->x) || (i == room->y && j == room->x + room->w -1) || (i == room->y + room->h -1 && j == room->x + room->w -1)){
                isEdge = true;
            }
            if((j != (*room).x && i != (*room).y) && (j != (*room).x + (*room).w -1 && i != (*room).y + (*room).h -1))
                m[i][j] = '.';
            else if(m[i][j] == 'X' && !isEdge)
                m[i][j] = '.';
            else
                m[i][j] = 'X';
        }
    }
    rooms.push_back(std::move(room));
}

int Game::isColliding(Room& room1, Room& room2){
    int collision = 0;
    if((room1.x < room2.x + room2.w - 2 && room1.x > room2.x + 2 || room1.x + room1.w < room2.x + room2.w - 2 && room1.x + room1.w > room2.x + 2) || (room2.x < room1.x + room1.w - 2 && room2.x > room1.x + 2 || room2.x + room2.w < room1.x + room1.w - 2 && room2.x + room2.w > room1.x + 2)){
		//Room1's upper wall colliding
        if(room1.y == room2.y + room2.h - 1){
            collision = 2;
        }
        //Room1's lower wall colliding
        if(room1.y + room1.h -1 == room2.y){
            collision = 3;
        }
	}

    if((room1.y < room2.y + room2.h - 2 && room1.y > room2.y + 2 || room1.y + room1.h < room2.y + room2.h - 2 && room1.y + room1.h > room2.y + 2) || (room2.y < room1.y + room1.h -2 && room2.y > room1.y + 2 || room2.y + room2.h < room1.y + room1.h - 2 && room2.y + room2.h > room1.y + 2)){
        //Room1's left wall colliding
        if(room1.x == room2.x + room2.w - 1){
            if(collision == 0)
                collision = 4;
            else
                collision = 1;
        }
        //Room1's right wall colliding
        if(room1.x + room1.w - 1 == room2.x){
            if(collision == 0)
                collision = 5;
            else
                collision = 1;
        }
	}
    if(collision == 0){
        if((room1.x <= room2.x + room2.w && room1.x >= room2.x || room1.x + room1.w <= room2.x + room2.w && room1.x + room1.w >= room2.x) || (room2.x <= room1.x + room1.w && room2.x >= room1.x || room2.x + room2.w <= room1.x + room1.w && room2.x + room2.w >= room1.x)){
                //Then if y coordinates match
                if((room1.y <= room2.y + room2.h && room1.y >= room2.y || room1.y + room1.h <= room2.y + room2.h && room1.y + room1.h >= room2.y) || (room2.y <= room1.y + room1.h && room2.y >= room1.y || room2.y + room2.h <= room1.y + room1.h && room2.y + room2.h >= room1.y)){
                    collision = 1;
                }
        }
    }
    
    return collision;
}

bool Game::linkRooms(){
    //first check if every room is fused
    std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
    std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin();
    //Check if every room is fused
    int counter = 0;
    it++;
    for (it; it != end; it++ ){
        if(isColliding(**it, *(rooms.at(0))) != 0)
            counter ++;
    }

    if(counter < rooms.size()-1){
        it = rooms.begin();
        for (it; it != end; it++ ){
            int otherIndex = rand() % rooms.size();
            int counter = 0;
            while(otherIndex == it - rooms.begin() && isColliding(**it, *(rooms.at(otherIndex))) != 0){
                otherIndex = rand() % rooms.size();
                counter ++;
            }
            createPath(**it, *(rooms.at(otherIndex)));
        }
    }
}

bool Game::createPath(Room& room1, Room& room2){
    //int startingDirection = (rand()%2);
    int startingDirection = 0;
    std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
    std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin();
    //check if there is a possible straight line
    int straightX = 0;
    int straightY = 0;

    //check if is vertical straight
    for(int x = room1.x + 1; x != room1.x + room1.w -1; x ++){
        bool ok = true;
        for(it; it != end; it++){
            if(x == (**it).x || x == (**it).x + (**it).w - 1)
                ok = false;
        }
        if(x > room2.x && x < room2.x + room2.w -1 && ok){
            straightX = x;
            startingDirection = 1;
            std::cout<<"VERTICAL STRAIGHT\n\n";
            break;
        }
    }
    //check if horizontal straight
    if(straightX == 0){
        for(int y = room1.y + 1; y != room1.y + room1.h -1; y ++){
            bool ok = true;
            for(it; it != end; it++){
                if(y == (**it).y || y == (**it).y + (**it).h - 1)
                    ok = false;
            }
            if(y > room2.y && y < room2.y + room2.h -1 && ok){
                straightY = y;
                startingDirection = 0;
                std::cout<<"HORIZONTAL STRAIGHT\n\n";
                break;
            }
        }
    }
    //Starting horizontally
    if(startingDirection == 0){
        int y;

        if(straightY == 0){
            bool ok;
            do{
                ok = true;
                y = (room1.y + room1.h -2) - rand() % (room1.h -2);
                std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
                std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin();
                for(it; it != end; it++){
                    if((y == (**it).y || y == (**it).y + (**it).h - 1)){
                        ok = false;
                    }
                }
            }while(!ok);
        }else
            y = straightY;
        
        int x = room1.x - 1;
        int inc = 1;
        std::cout<<room1.x + (room1.w/2)<<"  "<<room2.x + (room2.w/2)<<std::endl;
        if(room2.x + (room2.w/2) > room1.x + (room1.w/2)){
            x += room1.w + 1;
        }

        int startingPoint[] = {y, x};
        if(startingPoint[1] <= room2.x)
            inc = 1;
        else if(startingPoint[1] >= room2.x + room2.w -1)
            inc = -1;
        if(x == room1.x -1 && m[y][x + 1] == 'X')
            m[y][x + 1] = 'D';
        else if(m[y][x - 1] == 'X')
            m[y][x - 1] = 'D';
        int k;

        //Horizontal writing
        bool ok = true;
        for(k = startingPoint[1]; (k <= room2.x || k >= room2.x + room2.w -1) || !ok; k += inc){
            if(m[y][k] == ' ')
                m[y][k] = 'O';
            else if(m[y][k] == 'X')
                m[y][k] = 'D';
            if((k >= room2.x && k <= room2.x + room2.w -1) && straightY == 0){
                ok = true;
                std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
                std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin();
                for(it; it != end; it++){
                    if((k == (**it).x || y == (**it).x + (**it).w - 1)){
                        ok = false;
                        std::cout<<"\nNOT OK\n";
                    }
                }
            }
            printBoard();
        }
        if(k == startingPoint[1])
            k = startingPoint[1] - inc;
        std::cout<<"\n\nfine\n\n";


        //Vertical
        //if it is a straight line
        if(straightY != 0){
            if(m[y][k - inc] == 'X')
                m[y][k - inc] = 'D';
        }else{
            if(k != startingPoint[1] - inc && m[y][k] == ' ')
                m[y][k] = 'O';
            else if(k != startingPoint[1] - inc && m[y][k] == 'X')
                m[y][k] = 'D';
            printBoard();
            k += inc;
            inc = -1;
            if(startingPoint[0] <= room2.y)
                inc = 1;
            x = k;
            //Vertical writing
            for(k = startingPoint[0]; (k <= room2.y || k >= room2.y + room2.h -1); k += inc){
                if(m[k][x] == ' ')
                    m[k][x] = 'O';
                else if(m[k][x] == 'X')
                    m[k][x] = 'D';
            printBoard();
            }
            if(m[k - inc][x] == 'X')
                m[k - inc][x] = 'D';
        }

    std::cout<<"\nfine 2\n";

    }else{ //Starting vertically
        int x;
        if(straightX == 0){
            //Check if the path would go on a wall
            bool ok;
            do{
                x = (room1.x + room1.w -2) - rand() % (room1.w -2);
                std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
                std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin();
                ok = true;
                for(it; it != end; it++){
                    if(x == (**it).x || x == (**it).x + (**it).w - 1)
                        ok = false;
                }
            }while(!ok);
        }else
            x = straightX;
        
        int y = room1.y - 1;
        int inc = 1;
        
        if(room2.y + (room2.h/2) > room1.y + (room1.h/2)){
            y += room1.h + 1;
        }
        
        int startingPoint[] = {y, x};
        if(startingPoint[0] <= room2.y)
            inc = 1;
        else if(startingPoint[0] >= room2.y + room2.h -1)
            inc = -1;
        if(y == room1.y -1 && m[y + 1][x] == 'X')
            m[y + 1][x] = 'D';
        else if(m[y - 1][x] == 'X')
            m[y - 1][x] = 'D';

        int k;
        bool ok = true;
        for(k = startingPoint[0]; (k <= room2.y || k >= room2.y + room2.h -1) || !ok; k += inc){
            if(m[k][x] == ' ')
                m[k][x] = 'O';
            else if(m[k][x] == 'X')
                m[k][x] = 'D';
            //Check if will go on a wall, if yes keep going
            if (k >= room2.y && k <= room2.y + room2.h -1 && straightX == 0){
                ok = true;
                std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
                std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin();
                for(it; it != end; it++){
                    if((k == (**it).y || k == (**it).y + (**it).h - 1)){
                        ok = false;
                        std::cout<<"\nNOT OK\n";
                    }
                }
            }
            printBoard();
        }
        
        if(k == startingPoint[0])
            k = startingPoint[0] - inc;
        std::cout<<"\n\nfine\n\n";


        //Horizontal
        //if it is a straight line
        if(straightX != 0){
            if(m[k-inc][x] == 'X')
                m[k-inc][x] = 'D';
        }else{
            if(k != startingPoint[0] - inc && m[k][x] == ' ')
                m[k][x] = 'O';
            else if(k != startingPoint[0] - inc && m[k][x] == 'X')
                m[k][x] = 'D';
            printBoard();
            k += inc;
            inc = -1;
            if(startingPoint[1] <= room2.x)
                inc = 1;
            y = k;
            for(k = startingPoint[1]; (k <= room2.x || k >= room2.x + room2.w -1); k += inc){
                if(m[y][k] == ' ')
                    m[y][k] = 'O';
                else if(m[y][k] == 'X')
                    m[y][k] = 'D';
            printBoard();
            }
            if(m[y][k - inc] == 'X')
                m[y][k - inc] = 'D';
        }
        std::cout<<"\n\nFine 2\n\n";
    }
}
//------------------------------------------------------------------

//ROOM SECTION
//Room constructor
Room::Room(){ //Passare le altre stanze per vedere se collide
    w = MAX_ROOM_WIDTH - rand() % (MAX_ROOM_WIDTH - 5);
    h = MAX_ROOM_HEIGHT - rand() % (MAX_ROOM_HEIGHT - 5);
    x = (MAX_X_VALUE - rand() % MAX_X_VALUE);
    y = (MAX_Y_VALUE - rand() % MAX_Y_VALUE);
    /*
    switch (rand() % 4)
    {
        //Door can't be at the corner
        //Door on left wall
        case 0:
            door = std::unique_ptr<Door>(new Door(x, (y + 1 + rand() % (h-2))));
            break;
        //Door on right wall
        case 1:
            door = std::unique_ptr<Door>(new Door(x + w - 1,  (y + 1 + rand() % (h-2))));
            break;
        //Door on upper wall
        case 2:
            door = std::unique_ptr<Door>(new Door((x + 1 + rand() % (w-2)), y));
            break;
        //Door on lower wall
        case 3:
            door = std::unique_ptr<Door>(new Door((x + 1 + rand() % (w-2)), y + h - 1));
            break;
    }
    */
    //std::cout<<w<<std::endl<<h<<std::endl<<x<<std::endl<<y;
}

Room::Room(int width, int height, int newX, int newY) : w(width), h(height), x(newX), y(newY){}



//Room Functions


//------------------------------------------------------------------

//DOOR SECTION
//Door constructor
Door::Door(int x, int y){
    this->x = x;
    this->y = y;
}




