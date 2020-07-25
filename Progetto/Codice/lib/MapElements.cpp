#include "MapElements.h"


//DOOR SECTION
//Door constructor
Door::Door(int id, int x, int y, int connectedDoorId, int connectedRoomId, bool locked, std::string chUnlocked, std::string chLocked){
    this->id = id;
    this->x = x;
    this->y = y;
    this->connectedDoorId = connectedDoorId;
    this->connectedRoomId = connectedRoomId;
    this->locked = locked;
    this->chUnlocked = chUnlocked;
    this->chLocked = chLocked;
}

Door::Door(int id, int x, int y, bool locked, std::string chUnlocked, std::string chLocked){
    this->id = id;
    this->x = x;
    this->y = y;
    this->locked = locked;
    this->chUnlocked = chUnlocked;
    this->chLocked = chLocked;
    this->connectedDoorId = 0;
    this->connectedRoomId = 0;
}


unsigned int Door::getId()const{return this->id;}
unsigned int Door::getX()const{return this->x;}
unsigned int Door::getY()const{return this->y;}
unsigned int Door::getConnectedDoorId() const{return this->connectedDoorId;}
unsigned int Door::getConnectedRoomId() const{return this->connectedRoomId;}
bool Door::isLocked() const{return this->locked;}
std::string Door::getChUnlocked() const{return this->chUnlocked;}
std::string Door::getChLocked() const{return this->chLocked;}
void Door::setConnectedDoorId(unsigned int id){this->connectedDoorId = id;}
void Door::setConnectedRoomId(unsigned int id){this->connectedRoomId = id;}
void Door::setLocked(bool input){this->locked = input;}

//----------------------------------------------------------------------------------------------------

//ROOM SECTION
//Room constructor
Room::Room(int id, std::string chWall, std::string chFloor){
    w = MAX_ROOM_WIDTH - rand() % (MAX_ROOM_WIDTH - 5);
    h = MAX_ROOM_HEIGHT - rand() % (MAX_ROOM_HEIGHT - 5);
    x = (MAX_X_VALUE - rand() % MAX_X_VALUE);
    y = (MAX_Y_VALUE - rand() % MAX_Y_VALUE);
    this->id = id;
    this->chWall = chWall;
    this->chFloor = chFloor;
}

Room::Room(int id, int newX, int newY, int width, int height, std::string chWall, std::string chFloor) : id(id), w(width), h(height), x(newX), y(newY), chWall(chWall), chFloor(chFloor){}
bool Room::addDoor(std::unique_ptr<Door>& door){
    this->doors.push_back(std::move(door));
    this->chWall = chWall;
    this->chFloor = chFloor;
    return true;
}

unsigned int Room::getId() const{return id;}
std::string Room::getLabel() const{return label;}
unsigned int Room::getX() const{return x;}
unsigned int Room::getY() const{return y;}
unsigned int Room::getWidth() const{return w;}
unsigned int Room::getHeight() const{return h;}
std::string Room::getChWall() const{return chWall;}
std::string Room::getChFloor() const{return chFloor;}

//----------------------------------------------------------------------------------------------------

//GAME SECTION
//Game constructor
Game::Game(){
    lapsedTime = 0;
    //Init matrix
    for (int i = 0; i != MAX_MATRIX_HEIGHT -1; i++) {
		for (int j = 0; j != MAX_MATRIX_WIDTH -1; j++) {
            m[i][j] = 0;
            fogMatrix[i][j] = false;
		}
	}

}

//Game destructor
/*Game::~Game(){
    delete player;
}
*/

//Game functions

Player* Game::getPlayer() const{return this->player;}
unsigned int Game::getExitX() const{return this->exitX;}
unsigned int Game::getExitY() const{return this->exitY;}

void Game::generateMap(){
    this->chExit = "0x00BB";
    this->chPath = "0x0023";
    this->chFog = "0x003F";

    for(int counter = 0; counter != ROOMS_NUMBER; counter ++){
        addRoom(counter + 4, "0x2593", "0x00B7");
    }
    linkRooms();
    exportMap();
}

void Game::initMap(){
    using namespace rapidxml;
    using namespace std;
    xml_document<> doc;
	xml_node<> * root_node;
    ifstream xmlFile ("xml/map.xml"); 
    

    //Indicate start and end of the stream
    vector<char> buffer((istreambuf_iterator<char>(xmlFile)), istreambuf_iterator<char>());
    //Add the "end file character" at the end of the file
	buffer.push_back('\0');
	//Parse the buffer using the xml file parsing library into doc, now the xml_document is ready
	doc.parse<0>(&buffer[0]);
	//Assign the root node to root_node (the method returns and address)
	root_node = doc.first_node("Game");
    exitX = atoi(root_node->first_attribute("exitX")->value());
    exitY = atoi(root_node->first_attribute("exitY")->value());
    chExit = root_node->first_attribute("chExit")->value();
    chPath = root_node->first_attribute("chPath")->value();
    chFog = root_node->first_attribute("chFog")->value();
    root_node = root_node->first_node("Rooms");
    
    for (xml_node<> * roomNode = root_node->first_node("Room"); roomNode; roomNode = roomNode->next_sibling()){
	    std::unique_ptr<Room> temp = std::unique_ptr<Room>(new Room(atoi(roomNode->first_attribute("id")->value()), atoi(roomNode->first_attribute("x")->value()), atoi(roomNode->first_attribute("y")->value()), atoi(roomNode->first_attribute("width")->value()),
                                                                    atoi(roomNode->first_attribute("height")->value()), (roomNode->first_attribute("chWall")->value()), roomNode->first_attribute("chFloor")->value()));
        std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
        bool ok = true;
        for (std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin(); it != end; it++ ){
            if(isColliding(*temp, **it) == 1)
                ok = false;
        }
        //If temp does not collide wrongly with other rooms
        if(ok){
            addRoom(temp);
            //Add doors
            for(xml_node<> * doorNode = roomNode->first_node("Doors")->first_node("Door"); doorNode; doorNode = doorNode->next_sibling()){
                if(std::string(doorNode->name()) == "Door"){
                    std::unique_ptr<Door> tempDoor = std::unique_ptr<Door>(new Door(atoi(doorNode->first_attribute("id")->value()), atoi(doorNode->first_attribute("x")->value()), atoi(doorNode->first_attribute("y")->value()), atoi(doorNode->first_attribute("connectedDoorId")->value()), atoi(doorNode->first_attribute("connectedRoomId")->value()), (bool)(atoi(doorNode->first_attribute("locked")->value())), doorNode->first_attribute("chOpen")->value(), doorNode->first_attribute("chLocked")->value()));
                    m[tempDoor->getY()][tempDoor->getX()] = -1*(rooms.back()->getId());
                    rooms.back()->addDoor(tempDoor);
                }
            }

            //Add Enemies
            for(xml_node<> * enemyNode = roomNode->first_node("Enemies")->first_node("Enemy"); enemyNode; enemyNode = enemyNode->next_sibling()){
                //Iterate over the bestiary to find the right enemy
                std::vector<std::unique_ptr<Enemy>>::iterator enemyEnd = bestiaryEnemies.end();
                for (std::vector<std::unique_ptr<Enemy>>::iterator enemyIt = bestiaryEnemies.begin(); enemyIt != enemyEnd; enemyIt++){
                    if(areStringsEqual((**enemyIt).getLabel(), enemyNode->first_attribute("label")->value())){
                        std::unique_ptr<Enemy> enemy;
                        enemy = std::unique_ptr<Enemy>(new Enemy(**enemyIt, atoi(enemyNode->first_attribute("x")->value()), atoi(enemyNode->first_attribute("y")->value())));
                        enemies.push_back(std::move(enemy));
                    }
                }
            }
            //Add items
            for(xml_node<> * itemNode = roomNode->first_node("Loots")->first_node("Loot"); itemNode; itemNode = itemNode->next_sibling()){
                //Check if it's a weapon or not
                if(areStringsEqual(itemNode->first_attribute("type")->value(), "weapon")){
                    //It's a weapon
                    std::vector<Weapon>::iterator wEnd = inventoryWeapons.end();
                    for (std::vector<Weapon>::iterator wIt = inventoryWeapons.begin(); wIt != wEnd; wIt++){
                        if(areStringsEqual((*wIt).getLabel(), itemNode->first_attribute("label")->value())){
                            std::unique_ptr<Weapon> weapon;
                            weapon = std::unique_ptr<Weapon>(new Weapon(*wIt, atoi(itemNode->first_attribute("x")->value()), atoi(itemNode->first_attribute("y")->value())));
                            weapons.push_back(std::move(weapon));
                        }
                    }
                }else{
                    //It's an item
                    if(areStringsEqual("key", itemNode->first_attribute("type")->value())){
                        //Key
                        std::unique_ptr<InventoryElement> item = std::unique_ptr<InventoryElement>(new InventoryElement(atoi(itemNode->first_attribute("x")->value()), atoi(itemNode->first_attribute("y")->value()), itemNode->first_attribute("label")->value(), "key", "0x00BF"));
                        items.push_back(std::move(item));
                    }else if(areStringsEqual("gp", itemNode->first_attribute("type")->value())){
                        //GP
                        std::unique_ptr<InventoryElement> item = std::unique_ptr<InventoryElement>(new InventoryElement(atoi(itemNode->first_attribute("x")->value()), atoi(itemNode->first_attribute("y")->value()), itemNode->first_attribute("label")->value(), "gp", "0x00BF"));
                        items.push_back(std::move(item));
                    }else{
                        std::vector<InventoryElement>::iterator iEnd = inventoryItems.end();
                        for (std::vector<InventoryElement>::iterator iIt = inventoryItems.begin(); iIt != iEnd; iIt++){
                            if(areStringsEqual((*iIt).getLabel(), itemNode->first_attribute("label")->value())){
                                std::unique_ptr<InventoryElement> item = std::unique_ptr<InventoryElement>(new InventoryElement(*iIt, atoi(itemNode->first_attribute("x")->value()), atoi(itemNode->first_attribute("y")->value())));
                                items.push_back(std::move(item));
                            }
                        }
                    }
                }
            }

            //Add chests
            //Check if the room has chests
            if(roomNode->first_node("treasureChests") != nullptr){
                for(xml_node<> * itemNode = roomNode->first_node("treasureChests")->first_node(); itemNode; itemNode = itemNode->next_sibling()){
                    std::unique_ptr<InventoryElement> item;
                    item = std::unique_ptr<InventoryElement>(new InventoryElement(atoi(itemNode->first_attribute("x")->value()), atoi(itemNode->first_attribute("y")->value()), itemNode->first_attribute("label")->value(), itemNode->first_attribute("type")->value(), "0x00A9"));
                    item->setChest(true);
                    items.push_back(std::move(item));
                }
            }
        }
	}
}

void Game::exportMap(){ 
    using namespace rapidxml;
    using namespace std;
    xml_document<> wdoc;
	
	xml_node<> *declaration = wdoc.allocate_node( node_declaration);
	declaration->append_attribute(wdoc.allocate_attribute("version","1.0"));
	declaration->append_attribute(wdoc.allocate_attribute("encoding","utf-8"));
	wdoc.append_node(declaration);	
	
	string node_name = wdoc.allocate_string("Game");
	xml_node<> *wroot = wdoc.allocate_node(node_element, node_name.c_str());
	wdoc.append_node( wroot );
	
    xml_attribute<> *attr = wdoc.allocate_attribute("w", to_string(MAX_MATRIX_WIDTH).c_str());
	wroot->append_attribute(attr);
    attr = wdoc.allocate_attribute("h", to_string(MAX_MATRIX_HEIGHT).c_str());
	wroot->append_attribute(attr);
    attr = wdoc.allocate_attribute("exitX", to_string(this->exitX).c_str());
	wroot->append_attribute(attr);
    attr = wdoc.allocate_attribute("exitY", to_string(this->exitY).c_str());
	wroot->append_attribute(attr);
    attr = wdoc.allocate_attribute("chExit", (this->chExit).c_str());
	wroot->append_attribute(attr);
    attr = wdoc.allocate_attribute("chPath", (this->chPath).c_str());
	wroot->append_attribute(attr);
    attr = wdoc.allocate_attribute("chFog", (this->chFog).c_str());
	wroot->append_attribute(attr);
	xml_node<> *roomsNode = wdoc.allocate_node( node_element,  wdoc.allocate_string("Rooms") );
    wroot->append_node(roomsNode);
    //Add rooms
	xml_node<> *room;
    std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
    std::vector<std::unique_ptr<Room>>::iterator it;
    for(it = rooms.begin(); it != end; it++){
        room = wdoc.allocate_node( node_element,  wdoc.allocate_string("Room") );
        roomsNode->append_node(room);

        attr = wdoc.allocate_attribute("id", wdoc.allocate_string(to_string((**it).getId()).c_str()));
        room->append_attribute(attr);
        attr = wdoc.allocate_attribute("label", wdoc.allocate_string((**it).getLabel().c_str()));
        room->append_attribute(attr);
        attr = wdoc.allocate_attribute("x", wdoc.allocate_string(to_string((**it).getX()).c_str()));
        room->append_attribute(attr);
        attr = wdoc.allocate_attribute("y", wdoc.allocate_string(wdoc.allocate_string(to_string((**it).getY()).c_str())));
        room->append_attribute(attr);
        attr = wdoc.allocate_attribute("width", wdoc.allocate_string(to_string((**it).getWidth()).c_str()));
        room->append_attribute(attr);
        attr = wdoc.allocate_attribute("height", wdoc.allocate_string(to_string((**it).getHeight()).c_str()));
        room->append_attribute(attr);
        attr = wdoc.allocate_attribute("chWall", wdoc.allocate_string((**it).getChWall().c_str()));
        room->append_attribute(attr);
        attr = wdoc.allocate_attribute("chFloor", wdoc.allocate_string((**it).getChFloor().c_str()));
        room->append_attribute(attr);

        //Add doors
        xml_node<> *doors = wdoc.allocate_node( node_element,  wdoc.allocate_string("Doors") );
        room->append_node(doors);
        xml_node<> *door;
        std::vector<std::unique_ptr<Door>>::iterator doorsEnd = (**it).doors.end();
        std::vector<std::unique_ptr<Door>>::iterator doorsIt = (**it).doors.begin();
    
        for(doorsIt; doorsIt != doorsEnd; doorsIt++){
            door = wdoc.allocate_node(node_element, wdoc.allocate_string("Door") );
            attr = wdoc.allocate_attribute("id", wdoc.allocate_string(to_string((**doorsIt).getId()).c_str()));
            door->append_attribute(attr);
            attr = wdoc.allocate_attribute("connectedDoorId", wdoc.allocate_string(to_string((**doorsIt).getConnectedDoorId()).c_str()));
            door->append_attribute(attr);
            attr = wdoc.allocate_attribute("connectedRoomId", wdoc.allocate_string(to_string((**doorsIt).getConnectedRoomId()).c_str()));
            door->append_attribute(attr);
            attr = wdoc.allocate_attribute("x", wdoc.allocate_string(to_string((**doorsIt).getX()).c_str()));
            door->append_attribute(attr);
            attr = wdoc.allocate_attribute("y", wdoc.allocate_string(to_string((**doorsIt).getY()).c_str()));
            door->append_attribute(attr);
            attr = wdoc.allocate_attribute("room", wdoc.allocate_string((**it).getLabel().c_str()));
            door->append_attribute(attr);
            attr = wdoc.allocate_attribute("locked", wdoc.allocate_string(to_string(int((**doorsIt).isLocked())).c_str()));
            door->append_attribute(attr);
            attr = wdoc.allocate_attribute("chOpen", wdoc.allocate_string((**doorsIt).getChUnlocked().c_str()));
            door->append_attribute(attr);
            attr = wdoc.allocate_attribute("chLocked", wdoc.allocate_string((**doorsIt).getChLocked().c_str()));
            door->append_attribute(attr);
            doors->append_node(door);
        }
        int tempX;
        int tempY;
        //Generate and add enemies
        xml_node<> *enemiesNode = wdoc.allocate_node( node_element,  wdoc.allocate_string("Enemies") );
        room->append_node(enemiesNode);
        unsigned int random = (rand() % (MAX_ENEMIES_NUMBER + 1 - MIN_ENEMIES_NUMBER)) + MIN_ENEMIES_NUMBER;
        for(int i = 0; i != random; i++){
            //Decide what type of enemy will it be (basing on the bestiary)
            unsigned int enemyIndex = rand() % bestiaryEnemies.size();
            do{
                tempX = rand()%((**it).getX() + (**it).getWidth() - (**it).getX() - 2) + (**it).getX() + 1;
                tempY = rand()%((**it).getY() + (**it).getHeight() - (**it).getY() - 2) + (**it).getY() + 1;
            }while(getElementType(tempY, tempX) != 2);
            m[tempY][tempX] = 3;
            xml_node<> *enemy;
            enemy = wdoc.allocate_node(node_element, wdoc.allocate_string("Enemy") );
            attr = wdoc.allocate_attribute("label", wdoc.allocate_string(bestiaryEnemies.at(enemyIndex)->getLabel().c_str()));
            enemy->append_attribute(attr);
            attr = wdoc.allocate_attribute("x", wdoc.allocate_string(to_string(tempX).c_str()));
            enemy->append_attribute(attr);
            attr = wdoc.allocate_attribute("y", wdoc.allocate_string(to_string(tempY).c_str()));
            enemy->append_attribute(attr);

            enemiesNode->append_node(enemy);
        }

        //Generate and add items
        xml_node<> *loots = wdoc.allocate_node( node_element,  wdoc.allocate_string("Loots") );
        room->append_node(loots);
        random = (rand() % (MAX_ITEMS_NUMBER + 1 - MIN_ITEMS_NUMBER)) + MIN_ITEMS_NUMBER;
        for(int i = 0; i != random; i++){
            do{
                tempX = rand()%((**it).getX() + (**it).getWidth() - (**it).getX() - 2) + (**it).getX() + 1;
                tempY = rand()%((**it).getY() + (**it).getHeight() - (**it).getY() - 2) + (**it).getY() + 1;
            }while(getElementType(tempY, tempX) != 2);
            m[tempY][tempX] = 3;
            xml_node<> *item;
            item = wdoc.allocate_node(node_element, wdoc.allocate_string("Loot") );
            attr = wdoc.allocate_attribute("x", wdoc.allocate_string(to_string(tempX).c_str()));
            item->append_attribute(attr);
            attr = wdoc.allocate_attribute("y", wdoc.allocate_string(to_string(tempY).c_str()));
            item->append_attribute(attr);

            //Decide randomly if the items is a weapon, an item, GP or a key
            int random = rand()%5;
            if(random == 0){
                //It's a weapon
                if(inventoryWeapons.size() > 0){
                    attr = wdoc.allocate_attribute("type", wdoc.allocate_string("weapon"));
                    item->append_attribute(attr);
                    //Decide randomly what weapon the item is
                    int itemIndex = rand() % inventoryWeapons.size();
                    attr = wdoc.allocate_attribute("label", wdoc.allocate_string(inventoryWeapons.at(itemIndex).getLabel().c_str()));
                    item->append_attribute(attr);
                }
            }else if(random == 1){
                //It's a scroll
                if(inventoryScrolls.size() > 0){
                    attr = wdoc.allocate_attribute("type", wdoc.allocate_string("scroll"));
                    item->append_attribute(attr);
                    //Decide randomly what weapon the item is
                    int itemIndex = rand() % inventoryScrolls.size();
                    attr = wdoc.allocate_attribute("label", wdoc.allocate_string(inventoryScrolls.at(itemIndex).getLabel().c_str()));
                    item->append_attribute(attr);
                }
            }else if(random == 2){
                //It's an item
                if(inventoryItems.size() > 0){
                    //Decide randomly what item it is
                    int itemIndex = rand() % inventoryItems.size();
                    attr = wdoc.allocate_attribute("type", wdoc.allocate_string(inventoryItems.at(itemIndex).getType().c_str()));
                    item->append_attribute(attr);
                    attr = wdoc.allocate_attribute("label", wdoc.allocate_string(inventoryItems.at(itemIndex).getLabel().c_str()));
                    item->append_attribute(attr);
                }
            }else if(random == 3){
                //It's GP
                attr = wdoc.allocate_attribute("type", wdoc.allocate_string("gp"));
                item->append_attribute(attr);
                attr = wdoc.allocate_attribute("label", wdoc.allocate_string(to_string((rand()%MAX_GP_LOOT_NUMBER - MIN_GP_LOOT_NUMBER + 1) + MIN_GP_LOOT_NUMBER).c_str()));
                item->append_attribute(attr);
            }else if(random == 4){
                //It's a key
                attr = wdoc.allocate_attribute("type", wdoc.allocate_string("key"));
                item->append_attribute(attr);
                attr = wdoc.allocate_attribute("label", wdoc.allocate_string(to_string((rand()%MAX_KEYS_LOOT_NUMBER - MIN_KEYS_LOOT_NUMBER + 1) + MIN_KEYS_LOOT_NUMBER).c_str()));
                item->append_attribute(attr);
            }
            loots->append_node(item);
        }
        //Generate and add chests
        if(rand()%CHESTS_CHANCE == 0){
            xml_node<> *chests = wdoc.allocate_node( node_element,  wdoc.allocate_string("treasureChests") );
            room->append_node(chests);
            random = (rand() % (MAX_CHESTS_NUMBER + 1 - MIN_CHESTS_NUMBER)) + MIN_CHESTS_NUMBER;
            for(int i = 0; i != random; i++){
                do{
                    tempX = rand()%((**it).getX() + (**it).getWidth() - (**it).getX() - 2) + (**it).getX() + 1;
                    tempY = rand()%((**it).getY() + (**it).getHeight() - (**it).getY() - 2) + (**it).getY() + 1;
                }while(getElementType(tempY, tempX) != 2);
                m[tempY][tempX] = 3;

                xml_node<> *chest;
                chest = wdoc.allocate_node(node_element, wdoc.allocate_string("Chest") );
                attr = wdoc.allocate_attribute("x", wdoc.allocate_string(to_string(tempX).c_str()));
                chest->append_attribute(attr);
                attr = wdoc.allocate_attribute("y", wdoc.allocate_string(to_string(tempY).c_str()));
                chest->append_attribute(attr);
                //Decide what will the chest contain
                switch (rand() % 2)
                {
                case 0:
                    //GP
                    attr = wdoc.allocate_attribute("type", wdoc.allocate_string("gp"));
                    chest->append_attribute(attr);
                    attr = wdoc.allocate_attribute("label", wdoc.allocate_string(to_string((rand()%MAX_CHEST_GOLD - MIN_CHEST_GOLD + 1) + MIN_CHEST_GOLD).c_str()));
                    chest->append_attribute(attr);
                    break;
                case 1:
                    //Keys
                    attr = wdoc.allocate_attribute("type", wdoc.allocate_string("key"));
                    chest->append_attribute(attr);
                    attr = wdoc.allocate_attribute("label", wdoc.allocate_string(to_string((rand()%MAX_CHEST_KEYS - MIN_CHEST_KEYS + 1) + MIN_CHEST_KEYS).c_str()));
                    chest->append_attribute(attr);
                    break;
                default:
                    break;
                }
                chests->append_node(chest);
            }
        }
    }
    
    
	  
	//cout << wdoc;
	 
	ofstream outfile; 
	outfile.open("xml/map.xml"); 
	outfile << wdoc;
	outfile.close();
    
}

void Game::printInterface(){
    int y = 0;
    for (int i = player->getY() - (MAP_HEIGHT/2); i != player->getY() + (MAP_HEIGHT/2) +1; i++) {
        y++;
		for (int j = player->getX() - (MAP_WIDTH/2); j != player->getX() + (MAP_WIDTH/2) +1; j++) {
            if(j < 0 || i < 0 || j > MAX_MATRIX_WIDTH || i > MAX_MATRIX_HEIGHT){
                std::cout<<" ";
            }else{
                //Check if Player is in this position
                if(player->getY() == i && player->getX() == j)
                    printUnicode(player->getCh(), 1);
                else if(fogMatrix[i][j] == true){
                    //Check if an enemy is in this position
                    std::vector<std::unique_ptr<Enemy>>::iterator end = enemies.end();
                    bool written = false;
                    for (std::vector<std::unique_ptr<Enemy>>::iterator it = enemies.begin(); it != end; it++ ){
                        if((**it).getY() == i && (**it).getX() == j){
                            written = true;
                            if(((*it)->getHP() * 100)/((*it)->getMaxHP()) >= 75)
                                printUnicode((*it)->getCh(), 2);
                            else if (((*it)->getHP() * 100)/((*it)->getMaxHP()) >= 50)
                                printUnicode((*it)->getCh(), 3);
                            else if (((*it)->getHP() * 100)/((*it)->getMaxHP()) >= 25)
                                printUnicode((*it)->getCh(), 4);
                            else
                                printUnicode((*it)->getCh(), 5);
                        }
                    }
                    //Check if an item is in this position
                    std::vector<std::unique_ptr<InventoryElement>>::iterator end2 = items.end();
                    for (std::vector<std::unique_ptr<InventoryElement>>::iterator it = items.begin(); it != end2; it++ ){
                        if((**it).getY() == i && (**it).getX() == j){
                            written = true;
                            printUnicode((*it)->getCh(), 0);
                        }
                    }
                    //Check if a weapon is in this position
                    std::vector<std::unique_ptr<Weapon>>::iterator end3 = weapons.end();
                    for (std::vector<std::unique_ptr<Weapon>>::iterator it = weapons.begin(); it != end3; it++){
                        if((**it).getY() == i && (**it).getX() == j){
                            written = true;
                            printUnicode((*it)->getCh(), 0);
                        }
                    }

                    //Check if a scroll is in this position
                    std::vector<std::unique_ptr<Scroll>>::iterator end4 = scrolls.end();
                    for (std::vector<std::unique_ptr<Scroll>>::iterator it = scrolls.begin(); it != end4; it++){
                        if((**it).getY() == i && (**it).getX() == j){
                            written = true;
                            printUnicode((*it)->getCh(), 0);
                        }
                    }

                    //Check if it's a map element
                    if(!written){
                        switch (getElementType(i, j)){
                            case 0:
                            //Nothing
                                std::cout<<" ";
                                break;
                            case 1:
                                //Door
                                {
                                    std::vector<std::unique_ptr<Door>>::iterator end = rooms.at(abs(m[i][j]) - 4)->doors.end();
                                    std::vector<std::unique_ptr<Door>>::iterator it = rooms.at(abs(m[i][j]) - 4)->doors.begin();
                                    //Iterate over every door of the connected room to check if it is the right one
                                    for (it; it != end; it++){
                                        if((**it).getY() == i && (**it).getX() == j){
                                            if((**it).isLocked())
                                                printUnicode((**it).getChLocked(), 0);
                                            else
                                                printUnicode((**it).getChUnlocked(), 0);
                                            break;
                                        }
                                    }
                                }
                                break;
                            case 2:
                                //Floor
                                printUnicode(rooms.at(abs(m[i][j]) - 4)->getChFloor(), 0);
                                break;
                            case 3:
                                //Path
                                printUnicode(chPath, 0);
                                break;
                            case 4:
                                //Wall
                                printUnicode(rooms.at(abs(m[i][j]) - 4)->getChWall(), 0);
                                break;
                            case 8:
                                //Exit
                                printUnicode(this->chExit, 0);
                                break;
                            default:
                                break;
                        }
                    }
                }else{
                    //It's int the fog
                    printUnicode(chFog, 0);
                }
            }
                          
		}
        std::cout<<"   ";
        switch (y){
                case 1:
                    std::cout<<"Name: "<<player->getLabel();
                    break;
                case 2:
                    std::cout<<"Class: "<<player->getPlayerClass();
                    break;
                case 3:
                    std::cout<<"Level: "<<player->getLvl();
                    break;
                case 4:
                    if((player->getHP() * 100)/(player->getMaxHP()) >= 75)
                        std::cout<<"HP: "<<termcolor::green<<player->getHP()<<"/"<<player->getMaxHP();
                    else if((player->getHP() * 100)/(player->getMaxHP()) >= 50)
                        std::cout<<"HP: "<<termcolor::yellow<<player->getHP()<<"/"<<player->getMaxHP();
                    else if((player->getHP() * 100)/(player->getMaxHP()) >= 25)
                        std::cout<<"HP: "<<termcolor::magenta<<player->getHP()<<"/"<<player->getMaxHP();
                    else
                        std::cout<<"HP: "<<termcolor::red<<player->getHP()<<"/"<<player->getMaxHP();
                    
                    std::cout<<"    ";
                    std::cout<<termcolor::reset;
                    if(player->getMaxMP()){
                        if((player->getMP() * 100)/(player->getMaxMP()) >= 75)
                            std::cout<<"MP: "<<termcolor::blue<<player->getMP()<<"/"<<player->getMaxMP();
                        else if((player->getMP() * 100)/(player->getMaxMP()) >= 50)
                            std::cout<<"MP: "<<termcolor::yellow<<player->getMP()<<"/"<<player->getMaxMP();
                        else if((player->getMP() * 100)/(player->getMaxMP()) >= 25)
                            std::cout<<"MP: "<<termcolor::magenta<<player->getMP()<<"/"<<player->getMaxMP();
                        else
                            std::cout<<"MP: "<<termcolor::red<<player->getMP()<<"/"<<player->getMaxMP();
                    }else{
                        std::cout<<"MP: "<<termcolor::red<<"0/0";
                    }
                    std::cout<<termcolor::reset;
                    break;
                case 5:
                    std::cout<<"STR: "<<player->getStr();
                    std::cout<<"    ";
                    std::cout<<"DEX: "<<player->getDex();
                    std::cout<<"    ";
                    std::cout<<"MND: "<<player->getMnd();
                    std::cout<<"    ";
                    std::cout<<"WIS: "<<player->getWis();
                    break;
                case 6:
                    std::cout<<"ActTime: "<<player->getActTime();
                    std::cout<<"    ";
                    std::cout<<"MovTime: "<<player->getMovTime();
                    std::cout<<"    ";
                    std::cout<<"Res: "<<player->getRes();
                    break;
                case 7:
                    std::cout<<"Exp: "<<player->getExp()<<"/"<<player->getLvl()*100;
                    break;
                case 8:
                    std::cout<<"GP: "<<player->getGp();
                    std::cout<<"    ";
                    std::cout<<"Keys: "<<player->getKeys();
                    break;
                case 9:
                    std::cout<<"LapsedTime: "<<lapsedTime;
                    break;
                case 11:
                    std::cout<<"Inventory";
                    break;
            default:
                if(y >= 12 && y <= 21){
                    std::cout<<y-12;
                    if(y-12 < player->getInventorySize()){
                        if(player->getInventoryElementAt(y-12).getIsEquipped()){
                            std::cout<<termcolor::yellow<<" E : ";
                        }else
                            std::cout<<"   : ";
                        if(player->getInventoryElementAt(y-12).getIsIdentified()){
                            if(areStringsEqual(player->getInventoryElementAt(y-12).getType(), "herb"))
                                std::cout<<termcolor::green<<player->getInventoryElementAt(y-12).getLabel();
                            else if(areStringsEqual(player->getInventoryElementAt(y-12).getType(), "potion"))
                                std::cout<<termcolor::blue<<player->getInventoryElementAt(y-12).getLabel();
                            else if(areStringsEqual(player->getInventoryElementAt(y-12).getType(), "weapon"))
                                std::cout<<termcolor::yellow<<player->getInventoryElementAt(y-12).getLabel();
                            else if(areStringsEqual(player->getInventoryElementAt(y-12).getType(), "protection"))
                                std::cout<<termcolor::white<<player->getInventoryElementAt(y-12).getLabel();
                            else if(areStringsEqual(player->getInventoryElementAt(y-12).getType(), "scroll"))
                                std::cout<<termcolor::magenta<<player->getInventoryElementAt(y-12).getLabel();
                        }else if(areStringsEqual(player->getInventoryElementAt(y-12).getType(), "herb"))
                            std::cout<<termcolor::green<<"Unidentified herb";
                        else
                            std::cout<<"???";
                    }else
                        std::cout<<"   : ";
                    std::cout<<termcolor::reset;
                }
                break;
            }
		std::cout << std::endl;
	}
    for(int t = 0; t != 120; t++)
        std::cout<<"-";
    std::cout<<history<<"\n";
    for(int t = 0; t != 120; t++)
        std::cout<<"-";
    std::cout<<"\n";
    
    history = "";
    if(this->player->getHP() > 0){
        std::cout<<std::endl<<"What would you like to do?\nW = move north\nS = move south\nA = move ovest\nD = move east\nEquip objectIndex = equip an object, a weapon or an armor";
        std::cout<<std::endl<<"Atk w/a/s/d = attack in the chosen direction\nUse w/a/s/d = use the equipped object in the chosen direction\nCast spellIndex w/a/s/d = cast the spell at the index spellIndex";
        std::cout<<std::endl<<"Open w/a/s/d = open the door in the chosen direction\nTake = loot the surrounding items\nDiscard objectIndex = discard the object at the index objectIndex";
        std::cout<<std::endl<<"Identify objectIndex = show the description of the object at the index objectIndex\n";
    }
}

bool Game::isWalkable(int x, int y){
    //If it's a wall or a player, return false
    if((m[y][x] >= 0) || (y == player->getY() && x == player->getX()))
        return false;
    //If it's an enemy, return false
    std::vector<std::unique_ptr<Enemy>>::iterator end = enemies.end();
    bool written = false;
    for (std::vector<std::unique_ptr<Enemy>>::iterator it = enemies.begin(); it != end; it++ ){
        if((**it).getX() == x && (**it).getY() == y)
            return false;
    }
    //If it's an item, return false
    std::vector<std::unique_ptr<InventoryElement>>::iterator end2 = items.end();
    for (std::vector<std::unique_ptr<InventoryElement>>::iterator it = items.begin(); it != end2; it++ ){
        if((**it).getX() == x && (**it).getY() == y)
            return false;
    }
    //If it's a weapon, return false
    std::vector<std::unique_ptr<Weapon>>::iterator end3 = weapons.end();
    for (std::vector<std::unique_ptr<Weapon>>::iterator it = weapons.begin(); it != end3; it++ ){
        if((**it).getX() == x && (**it).getY() == y)
            return false;
    }

    //If it's a scroll, return false
    std::vector<std::unique_ptr<Scroll>>::iterator end4 = scrolls.end();
    for (std::vector<std::unique_ptr<Scroll>>::iterator it = scrolls.begin(); it != end4; it++ ){
        if((**it).getX() == x && (**it).getY() == y)
            return false;
    }
    //If it's a closed door, return false
    std::vector<std::unique_ptr<Door>>::iterator end5 = rooms.at(abs(m[y][x])-4)->doors.end();
        for (std::vector<std::unique_ptr<Door>>::iterator it = rooms.at(abs(m[y][x])-4)->doors.begin(); it != end5; it++ ){
            if((**it).getY() == y && (**it).getX() == x && (**it).isLocked()){
                return false;
            }
        }
    return true;
}

bool Game::isWalkableForPlayer(int x, int y){
    //If it's a wall or nothing, return false
    if(m[y][x] >= 0){
        return false;
    }
    //If there is an enemy, return false
    std::vector<std::unique_ptr<Enemy>>::iterator end = enemies.end();
    for (std::vector<std::unique_ptr<Enemy>>::iterator it = enemies.begin(); it != end; it++ ){
        if((**it).getX() == x && (**it).getY() == y){
            return false;
        }
    }
    //If it's a closed door, return false
    std::vector<std::unique_ptr<Door>>::iterator end2 = rooms.at(abs(m[y][x])-4)->doors.end();
    for (std::vector<std::unique_ptr<Door>>::iterator it = rooms.at(abs(m[y][x])-4)->doors.begin(); it != end2; it++ ){
        if((**it).getY() == y && (**it).getX() == x && (**it).isLocked()){
            return false;
        }
    }
    return true;
}

int Game::getElementType(int i, int j){
    //0 = nothing
    //1 = door
    //2 = floor
    //3 = path
    //4 = wall
    //5 = enemy
    //6 = loot
    //7 = chest
    //8 = exit
    //std::cout<<"\n\n"<<i<<","<<j<<"   "<<exitY<<","<<exitX<<"\n";
    if(m[i][j] == 0)
        return 0;
    else if(this->exitY == i && this->exitX == j)
        return 8;
    else if(m[i][j] < -3){
        //Check if enemy
        std::vector<std::unique_ptr<Enemy>>::iterator enemiesEnd = enemies.end();
        for (std::vector<std::unique_ptr<Enemy>>::iterator it = enemies.begin(); it != enemiesEnd;  it++ ){
            if((**it).getX() == j && (**it).getY() == i)
                return 5;
        }
        //Check if loot or chest
        std::vector<std::unique_ptr<InventoryElement>>::iterator itemsEnd = items.end();
        for (std::vector<std::unique_ptr<InventoryElement>>::iterator it = items.begin(); it != itemsEnd;  it++ ){
            if((**it).getX() == j && (**it).getY() == i){
                if((**it).getIsChest())
                    return 7;
                else
                    return 6;
            }
        }
        //Check if door
        std::vector<std::unique_ptr<Door>>::iterator end = rooms.at(abs(m[i][j])-4)->doors.end();
        for (std::vector<std::unique_ptr<Door>>::iterator it = rooms.at(abs(m[i][j])-4)->doors.begin(); it != end; it++ ){
            if((**it).getY() == i && (**it).getX() == j){
                return 1;
            }
        }

        //Check if floor/path
        if(i >= rooms.at(abs(m[i][j]) - 4)->getY() && i <= rooms.at(abs(m[i][j]) - 4)->getY() + rooms.at(abs(m[i][j]) - 4)->getHeight() -1
             && j >= rooms.at(abs(m[i][j]) - 4)->getX() && j <= rooms.at(abs(m[i][j]) - 4)->getX() + rooms.at(abs(m[i][j]) - 4)->getWidth() -1){
            //It's floor
            return 2;
        }else{
            //It's path
            return 3;
        }
    }
    else if(m[i][j] > 3){ 
        //Wall
        return 4;
    }
}

void Game::addRoom(std::unique_ptr<Room>& room){
    bool isCorner = false;
    std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
    //Write room
    for(int i = room->getY(); i != room->getY() + room->getHeight(); i++){
        for(int j = room->getX(); j != room->getX() + room->getWidth(); j++){
            isCorner = false;
            for (std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin(); it != end; it++ ){
                if((i == (**it).getY() && j == (**it).getX()) || (i == (**it).getY() + (**it).getHeight() -1 && j == (**it).getX()) || (i == (**it).getY() && j == (**it).getX() + (**it).getWidth() -1) || (i == (**it).getY() + (**it).getHeight() -1 && j == (**it).getX() + (**it).getWidth() -1)){
                    isCorner = true;
                }
            }
            if((i == room->getY() && j == room->getX()) || (i == room->getY() + room->getHeight() -1 && j == room->getX()) || (i == room->getY() && j == room->getX() + room->getWidth() -1) || (i == room->getY() + room->getHeight() -1 && j == room->getX() + room->getWidth() -1)){
                isCorner = true;
            }
            if((j != room->getX() && i != room->getY()) && (j != room->getX() + room->getWidth() -1 && i != room->getY() + room->getHeight() -1))
                m[i][j] = -1*room->getId();
            else if((m[i][j] >= 4 || m[i][j] <= -4) && !isCorner){
                m[i][j] = -1*room->getId();
            }
            else
                m[i][j] = room->getId();
        }
    }
    rooms.push_back(std::move(room));
}

void Game::addRoom(int id, std::string chWall, std::string chFloor){
    bool ok = false;
    std::unique_ptr<Room> room;
    while(!ok){
        ok = true;
        room = std::unique_ptr<Room>(new Room(id, chWall, chFloor));
        std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
        for (std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin(); it != end; it++ ){
            if(isColliding(*room, **it) == 1)
                ok = false;
        }
    }
    bool isCorner = false;
    std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
    //Write room
    for(int i = room->getY(); i != room->getY() + room->getHeight(); i++){
        for(int j = room->getX(); j != room->getX() + room->getWidth(); j++){
            isCorner = false;
            for (std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin(); it != end; it++ ){
                if((i == (**it).getY() && j == (**it).getX()) || (i == (**it).getY() + (**it).getHeight() -1 && j == (**it).getX()) || (i == (**it).getY() && j == (**it).getX() + (**it).getWidth() -1) || (i == (**it).getY() + (**it).getHeight() -1 && j == (**it).getX() + (**it).getWidth() -1)){
                    isCorner = true;
                }
            }
            if((i == room->getY() && j == room->getX()) || (i == room->getY() + room->getHeight() -1 && j == room->getX()) || (i == room->getY() && j == room->getX() + room->getWidth() -1) || (i == room->getY() + room->getHeight() -1 && j == room->getX() + room->getWidth() -1)){
                isCorner = true;
            }
            if((j != room->getX() && i != room->getY()) && (j != room->getX() + room->getWidth() -1 && i != room->getY() + room->getHeight() -1))
                m[i][j] = -1*room->getId();
            else if((m[i][j] >= 4 || m[i][j] <= -4) && !isCorner){
                m[i][j] = -1*room->getId();
            }
            else
                m[i][j] = room->getId();
        }
    }

    //If there is no game exit, generate it
    if(this->exitX == 0 && this->exitY == 0){
        this->exitX = (rand() % (room->getWidth() - 1)) + room->getX() + 1;
        this->exitY = (rand() % (room->getHeight() - 1)) + room->getY() + 1;
        m[exitY][exitX] = 3;
    }
    
    rooms.push_back(std::move(room));
}

int Game::isColliding(Room& room1, Room& room2){
    int collision = 0;
    if((room1.getX() < room2.getX() + room2.getWidth() - 2 && room1.getX() > room2.getX() + 2 || room1.getX() + room1.getWidth() < room2.getX() + room2.getWidth() - 2 && room1.getX() + room1.getWidth() > room2.getX() + 2) || (room2.getX() < room1.getX() + room1.getWidth() - 2 && room2.getX() > room1.getX() + 2 || room2.getX() + room2.getWidth() < room1.getX() + room1.getWidth() - 2 && room2.getX() + room2.getWidth() > room1.getX() + 2)){
		//Room1's upper wall colliding
        if(room1.getY() == room2.getY() + room2.getHeight() - 1){
            collision = 2;
        }
        //Room1's lower wall colliding
        if(room1.getY() + room1.getHeight() -1 == room2.getY()){
            collision = 3;
        }
	}

    if((room1.getY() < room2.getY() + room2.getHeight() - 2 && room1.getY() > room2.getY() + 2 || room1.getY() + room1.getHeight() < room2.getY() + room2.getHeight() - 2 && room1.getY() + room1.getHeight() > room2.getY() + 2) || (room2.getY() < room1.getY() + room1.getHeight() -2 && room2.getY() > room1.getY() + 2 || room2.getY() + room2.getHeight() < room1.getY() + room1.getHeight() - 2 && room2.getY() + room2.getHeight() > room1.getY() + 2)){
        //Room1's left wall colliding
        if(room1.getX() == room2.getX() + room2.getWidth() - 1){
            if(collision == 0)
                collision = 4;
            else
                collision = 1;
        }
        //Room1's right wall colliding
        if(room1.getX() + room1.getWidth() - 1 == room2.getX()){
            if(collision == 0)
                collision = 5;
            else
                collision = 1;
        }
	}
    if(collision == 0){
        if((room1.getX() <= room2.getX() + room2.getWidth() && room1.getX() >= room2.getX() || room1.getX() + room1.getWidth() <= room2.getX() + room2.getWidth() && room1.getX() + room1.getWidth() >= room2.getX()) || (room2.getX() <= room1.getX() + room1.getWidth() && room2.getX() >= room1.getX() || room2.getX() + room2.getWidth() <= room1.getX() + room1.getWidth() && room2.getX() + room2.getWidth() >= room1.getX())){
                //Then if y coordinates match
                if((room1.getY() <= room2.getY() + room2.getHeight() && room1.getY() >= room2.getY() || room1.getY() + room1.getHeight() <= room2.getY() + room2.getHeight() && room1.getY() + room1.getHeight() >= room2.getY()) || (room2.getY() <= room1.getY() + room1.getHeight() && room2.getY() >= room1.getY() || room2.getY() + room2.getHeight() <= room1.getY() + room1.getHeight() && room2.getY() + room2.getHeight() >= room1.getY())){
                    collision = 1;
                }
        }
    }
    
    return collision;
}

bool Game::linkRooms(){
    std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
    std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin();
    //Check if every room is fused
    int counter = 0;
    it++;
    for (it; it != end; it++){
        if(isColliding(**it, *(rooms.at(0))) != 0)
            counter ++;
    }
    //If not every room is fused
    if(counter < rooms.size()-1){
        int doorsCounter = 0;
        it = rooms.begin();
        for (it; it != end; it++){
            int otherIndex = rand() % rooms.size();
            int counter = 0;
            while(otherIndex == it - rooms.begin() && isColliding(**it, *(rooms.at(otherIndex))) != 0){
                otherIndex = rand() % rooms.size();
                counter ++;
            }
            createPath(**it, *(rooms.at(otherIndex)), doorsCounter);
        }
    }
}

bool Game::linkRoomsByDoors(){
    std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
    std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin();
    //Iterate over every room
    for (it; it != end; it++){
        std::vector<std::unique_ptr<Door>>::iterator end2 = (**it).doors.end();
        std::vector<std::unique_ptr<Door>>::iterator it2 = (**it).doors.begin();
        
        //Iterate over every room's door
        for (it2; it2 != end2; it2++){
            //If the door is connected to another door (and the path starts from it)...
            if((**it2).getConnectedDoorId() != 0){
                std::vector<std::unique_ptr<Door>>::iterator end3 = rooms.at((**it2).getConnectedRoomId() - 4)->doors.end();
                std::vector<std::unique_ptr<Door>>::iterator it3 = rooms.at((**it2).getConnectedRoomId() - 4)->doors.begin();
                //Iterate over every door of the connected room to check if it is the right one
                for (it3; it3 != end3; it3++){
                    if((**it3).getId() == (**it2).getConnectedDoorId()){ 
                        createPathByDoors(**it2, **it3, (**it).getId()); 
                        break;
                    }
                }
            }
        }
    }

}

bool Game::createPath(Room& room1, Room& room2, int& doorsCounter){
    //check if there is a possible straight line
    int straightX = 0;
    int straightY = 0;

    int x;
    int y;
    int oldY;
    int oldX;
    int inc;
    int previousRoomId = 0;
    int cycleEnd;
    int doors = 0; //Doors added by this function call
    //check if is vertical straight
    //Iterate over the room1's X
    for(x = room1.getX() + 1; x != room1.getX() + room1.getWidth() -1; x ++){
        bool ok = true;
        std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
        std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin();
        //Iterate over rooms to do a check
        for(it = rooms.begin(); it != end; it++){
            //Check if the path would go on a wall
            if(x == (**it).getX() || x == (**it).getX() + (**it).getWidth() - 1){
                ok = false;
                break;
            }
        }
        if(ok){
            //Check if between this possibile door and room2 the would be another door
            //Find the Y coordinate
            if(room1.getY() > room2.getY() + room2.getHeight() - 1){
                //Room 1 is under room2
                y = room1.getY();
                inc = -1;
                cycleEnd = room2.getY() + room2.getHeight() - 1;
            }else if(room1.getY() + room1.getHeight() - 1 < room2.getY()){
                //Room 1 is over room2
                y = room1.getY() + room1.getHeight() - 1;
                inc = 1;
                cycleEnd = room2.getY();
            }else{
                ok = false;
            }
            
            if(ok){
                //Check if the door is found
                oldY = y;
                for(y; y != cycleEnd + inc; y += inc){
                    if(getElementType(y, x) == 1){
                        ok = false;
                        break;
                    }
                }
            }
        }
        y = oldY;
        if(x > room2.getX() && x < room2.getX() + room2.getWidth() -1 && ok){
            straightX = x;
            //std::cout<<"VERTICAL STRAIGHT\n\n";
            //Write the path
            for(y; y != cycleEnd + inc; y += inc){
                if(getElementType(y, straightX) == 4){
                    doorsCounter ++;
                    doors ++;
                    bool locked = rand()%2;
                    std::unique_ptr<Door> tempDoor = std::unique_ptr<Door>(new Door(doorsCounter, straightX, y, locked, "0x004F", "0x00D8"));
                    rooms.at(abs(m[y][straightX]) - 4)->addDoor(tempDoor);
                    if(doors > 1 && previousRoomId != abs(m[y][straightX]) - 4){
                            rooms.at(previousRoomId)->doors.back()->setConnectedDoorId(doorsCounter);
                            rooms.at(previousRoomId)->doors.back()->setConnectedRoomId(abs(m[y][straightX]));
                        }
                    m[y][straightX] = m[y][straightX]*-1;
                    previousRoomId = abs(m[y][straightX]) - 4;
                }else if(getElementType(y, straightX) == 0)
                    m[y][straightX] = room1.getId()*-1;
            }
            break;
        }
    }
    //check if horizontal straight
    if(straightX == 0){
        for(y = room1.getY() + 1; y != room1.getY() + room1.getHeight() -1; y ++){
            bool ok = true;
            std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
            std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin();
            for(it = rooms.begin(); it != end; it++){
                if(y == (**it).getY() || y == (**it).getY() + (**it).getHeight() - 1){
                    ok = false;
                    break;
                }
            }
            if(ok){
                //Check if between this possibile door and room2 the would be another door
                //Find the X coordinate
                if(room1.getX() > room2.getX() + room2.getWidth() - 1){
                    //Room 1 is under room2
                    x = room1.getX();
                    inc = -1;
                    cycleEnd = room2.getX() + room2.getWidth() - 1;
                }else if(room1.getX() + room1.getWidth() -1 < room2.getX()){
                    //Room 1 is over room2
                    x = room1.getX() + room1.getWidth() - 1;
                    inc = 1;
                    cycleEnd = room2.getX(); 
                }else{
                    ok = false;
                }

                if(ok){
                    //Check if the door is found
                    oldX = x;
                    for(x; x != cycleEnd + inc; x += inc){
                        if(getElementType(y, x) == 1){
                            ok = false;
                            break;
                        }
                    }
                }
            }
            x = oldX;
            if(y > room2.getY() && y < room2.getY() + room2.getHeight() -1 && ok){
                straightY = y;
                //std::cout<<"HORIZONTAL STRAIGHT\n\n";
                //If there is already a door, change path
                if(getElementType(straightY, x) == 1)
                    return false;
                //Write the path
                for(x; x != cycleEnd + inc; x += inc){
                    //std::cout<<getElementType(straightY, x);
                    //If it's a room's wall, create a door
                    if(getElementType(straightY, x) == 4){
                        doorsCounter ++;
                        doors ++;
                        bool locked = rand()%2;
                        std::unique_ptr<Door> tempDoor = std::unique_ptr<Door>(new Door(doorsCounter, x, straightY, locked, "0x004F", "0x00D8"));
                        rooms.at(abs(m[straightY][x]) - 4)->addDoor(tempDoor);
                        //Prendere la scorsa porta e darle come connected id quello della nuova
                        if(doors > 1 && previousRoomId != abs(m[straightY][x]) - 4){
                            rooms.at(previousRoomId)->doors.back()->setConnectedDoorId(doorsCounter);
                            //std::cout<<"\nDoor "<<rooms.at(previousRoomId)->doors.back()->getId()<<" connected to door "<<doorsCounter<<"\n";
                            rooms.at(previousRoomId)->doors.back()->setConnectedRoomId(abs(m[straightY][x]));
                            //std::cout<<"\n"<<previousRoomId<<"  "<<abs(m[straightY][x]) - 4;
                        }
                        m[straightY][x] = m[straightY][x] * -1;
                        previousRoomId = abs(m[straightY][x]) - 4;
                    }else if(getElementType(straightY, x) == 0)
                        m[straightY][x] = room1.getId()*-1;
                }
                break;
            }
        }
    }
    //If the path is not straight
    if(straightX == 0 && straightY == 0){
        //First write an horizontal path, then a vertical
        int x = room1.getX() - 1;
        int inc = 1;
        
        if(room2.getX() + (room2.getWidth()/2) > room1.getX() + (room1.getWidth()/2)){
            x += room1.getWidth() + 1;
        }
        
        //Decide increment direction based on initial wall
        if(x <= room2.getX())
            inc = 1;
        else if(x >= room2.getX() + room2.getWidth() -1)
            inc = -1;
        bool ok;
        do{
            y = (room1.getY() + room1.getHeight() -2) - rand() % (room1.getHeight() -2);
            std::vector<std::unique_ptr<Room>>::iterator end = rooms.end();
            std::vector<std::unique_ptr<Room>>::iterator it = rooms.begin();
            ok = true;
            for(it; it != end; it++){
                if((y == (**it).getY() || y == (**it).getY() + (**it).getHeight() - 1)){
                    ok = false;
                }
            }

            //Check if the path woul go on a door
            for(int k = x; (k <= room2.getX() || k >= room2.getX() + room2.getWidth() -1); k += inc){
                if(getElementType(y, k) == 1){
                    ok = false;
                    break;
                }
            }
        }while(!ok);

        int startingPoint[] = {y, x};
        //Add door at the start of the path
        doorsCounter ++;
        doors ++;
        if(x == room1.getX() - 1){
            m[y][x + 1] = room1.getId() * -1; //Door
            bool locked = rand()%2;
            std::unique_ptr<Door> tempDoor = std::unique_ptr<Door>(new Door(doorsCounter, x + 1, y, locked, "0x004F", "0x00D8"));
            room1.addDoor(tempDoor);
            previousRoomId = room1.getId() - 4;
        }else{
            m[y][x - 1] = room1.getId() * -1; //Door
            bool locked = rand()%2;
            std::unique_ptr<Door> tempDoor = std::unique_ptr<Door>(new Door(doorsCounter, x - 1, y, locked, "0x004F", "0x00D8"));
            room1.addDoor(tempDoor);
            previousRoomId = room1.getId() - 4;
        }
        int k;

        //Horizontal writing
        ok = true;
        for(k = startingPoint[1]; (k <= room2.getX() || k >= room2.getX() + room2.getWidth() -1); k += inc){
            if(m[y][k] == 0)
                m[y][k] = room1.getId() * -1; //Path
            else if(getElementType(y, k) == 4){
                doorsCounter ++;
                doors ++;
                bool locked = rand()%2;
                std::unique_ptr<Door> tempDoor = std::unique_ptr<Door>(new Door(doorsCounter, k, y, locked, "0x004F", "0x00D8"));
                rooms.at(abs(m[y][k]) - 4)->addDoor(tempDoor);
                if(previousRoomId != abs(m[y][k]) - 4){
                    rooms.at(previousRoomId)->doors.back()->setConnectedDoorId(doorsCounter);
                    //std::cout<<"\nDoor "<<rooms.at(previousRoomId)->doors.back()->getId()<<" connected to door "<<doorsCounter<<"\n";
                    rooms.at(previousRoomId)->doors.back()->setConnectedRoomId(abs(m[y][k]));
                    //std::cout<<"\n"<<previousRoomId<<"  "<<(abs(m[y][k]));
                }
                previousRoomId = abs(m[y][k]) - 4;
                m[y][k] = m[y][k] * -1; //Door
            }
            //printInterface();
        }
        if(k == startingPoint[1]){
            if(m[y][k] == 0)
                m[y][k] = rooms.at(previousRoomId)->getId() * -1; //Path
            k = startingPoint[1] - inc;
        }
        //std::cout<<"\n\nfine\n\n";


        //Vertical
            m[y][k] = rooms.at(previousRoomId)->getId() * -1; //Path
            int oldInc = inc;
            inc = -1;
            if(startingPoint[0] <= room2.getY())
                inc = 1;
            int wallsCounter = 0;
            int c;
            int t = 0;
            //Count how many walls in a row would the path collide (to understand if it is going on a room edge)
            do{
                c = 0;
                //std::cout<<std::endl;
                do{
                    //std::cout<<(m[k + t*oldInc][x + c*inc]);
                    if(getElementType(y + c*inc, k + t*oldInc) ==  4 || getElementType(y + c*inc, k + t*oldInc) ==  1) //Door
                        wallsCounter ++;
                    else
                        wallsCounter = 0;
                    if(wallsCounter > 1)
                        break;
                    c++;
                }while((y + c*inc <= MAX_MATRIX_HEIGHT -1 && y + c*inc > -1) && (y + c*inc <= room2.getY() || y + c*inc >= room2.getY() + room2.getHeight() -1));
                    
                //std::cout<<std::endl<<"Riga "<<k + t*oldInc<<"   Counter "<<wallsCounter<<"\n";
                if(wallsCounter < 2)
                    break;
                t++;
                wallsCounter = 0;
            }while(true);
            
            x = k + t*oldInc;

            //Vertical writing
            for(k = startingPoint[0]; (k <= room2.getY() || k >= room2.getY() + room2.getHeight() -1); k += inc){
                if(m[k][x] == 0)
                    m[k][x] = rooms.at(previousRoomId)->getId() * -1; //Path
                else if(getElementType(k, x) == 4){
                    doorsCounter ++;
                    bool locked = rand()%2;
                    std::unique_ptr<Door> tempDoor = std::unique_ptr<Door>(new Door(doorsCounter, x, k, locked, "0x004F", "0x00D8"));
                    rooms.at(abs(m[k][x]) - 4)->addDoor(tempDoor);
                    if(previousRoomId != abs(m[k][x]) - 4){
                        rooms.at(previousRoomId)->doors.back()->setConnectedDoorId(doorsCounter);
                        //std::cout<<"\nDoor "<<rooms.at(previousRoomId)->doors.back()->getId()<<" connected to door "<<doorsCounter<<"\n";
                        rooms.at(previousRoomId)->doors.back()->setConnectedRoomId(abs(m[k][x]));
                        //std::cout<<"\n"<<previousRoomId<<"  "<<abs(m[k][x]) - 4;
                    }
                    previousRoomId = abs(m[k][x]) - 4;
                    m[k][x] = rooms.at(previousRoomId)->getId() * -1; //Door
                }
            }
        

        //std::cout<<"\nfine 2\n";
    }
    
}

bool Game::createPathByDoors(Door& door1, Door& door2, int roomId){
    //Check if there is a possible straight line
    int straightX = 0;
    int straightY = 0;
    int inc = 1;

    //Check if is vertical straight
    if(door1.getX() == door2.getX()){
        straightX = door1.getX();
        if(door1.getY() > door2.getY())
            inc = -1;
        for(int i = door1.getY() + inc; i != door2.getY(); i += inc){
            m[i][straightX] = -1*roomId;
        }
        return true;
    }
    //Check if horizontal straight
    else if(straightX == 0 && door1.getY() == door2.getY()){
        straightY = door1.getY();
        if(door1.getX() > door2.getX())
            inc = -1;
        for(int j = door1.getX() + inc; j != door2.getX(); j += inc){
            m[straightY][j] = -1*roomId;
        }
        return true;
    }else{
        int y;
        int j;
        //If the door to be reached is on the left, then Increment is negative
        if(door1.getX() > door2.getX())
            inc = -1;

        //Horizontal path writing
        for(j = door1.getX() + inc; j != door2.getX(); j += inc){
            m[door1.getY()][j] = -1*roomId;
        }

        //If the door to be reached is on the upper side, then Increment is negative
        if(door1.getY() > door2.getY())
            inc = -1;
        else
            inc = 1;
        //Vertical path writing
        for(int i = door1.getY(); i != door2.getY(); i += inc){
            m[i][j] = -1*roomId;
        }
        
    }
}

void Game::chooseClass(){
    std::cout<<"\nChoose your class:";
    //Import classes and tell the user what they do
    using namespace rapidxml;
    using namespace std;
    xml_document<> doc;
	xml_node<> * root_node;
    ifstream xmlFile ("xml/classes.xml"); 

    //Indicate start and end of the stream
    vector<char> buffer((istreambuf_iterator<char>(xmlFile)), istreambuf_iterator<char>());
    //Add the "end file character" at the end of the file
	buffer.push_back('\0');
	//Parse the buffer using the xml file parsing library into doc, now the xml_document is ready
	doc.parse<0>(&buffer[0]);
	//Assign the root node to root_node (the method returns and address)
	root_node = doc.first_node("classes");
    for (xml_node<> * classNode = root_node->first_node("heroClass"); classNode; classNode = classNode->next_sibling()){
        std::cout<<"\n\n- "<<classNode->first_attribute("label")->value();
	    std::cout<<"\nHP: "<<classNode->first_node("baseStats")->first_attribute("hpMax")->value();
        std::cout<<"  MP:"<<classNode->first_node("baseStats")->first_attribute("mpMax")->value();
        std::cout<<"\nSTR: "<<classNode->first_node("baseStats")->first_attribute("str")->value();
        std::cout<<"  DEX:"<<classNode->first_node("baseStats")->first_attribute("dex")->value();
        std::cout<<"  MND:"<<classNode->first_node("baseStats")->first_attribute("mnd")->value();
        std::cout<<"  WIS:"<<classNode->first_node("baseStats")->first_attribute("wis")->value();
        std::cout<<"  RES:"<<classNode->first_node("baseStats")->first_attribute("res")->value();
        
        std::cout<<"\nStarting items:";
        xml_node<> *equipNode = classNode->first_node("startingEquipment");
        for (equipNode = equipNode->first_node(); equipNode; equipNode = equipNode->next_sibling()){
            std::cout<<"\n"<<equipNode->first_attribute("label")->value()<<" - "<<equipNode->name();
        }
	}
    std::string temp;
    std::cout<<"\n\nWhat class do you choose? ";
    std::cin>>temp;

    for (xml_node<> * classNode = root_node->first_node("heroClass"); classNode; classNode = classNode->next_sibling()){
        if(areStringsEqual(temp, classNode->first_attribute("label")->value())){
            std::string name;
            fflush(stdin);
            std::cout<<"\nYou are a "<<temp<<", what is your name? ";
            getline(std::cin, name);
            
            //Spawn player
            unsigned int tempX;
            unsigned int tempY;
            do{
                unsigned int tempRoomIndex = rand() % ROOMS_NUMBER;
                tempX = rooms[tempRoomIndex]->getX() + rooms[tempRoomIndex]->getWidth() -2 - rand() % (rooms[tempRoomIndex]->getWidth() -2);
                tempY = rooms[tempRoomIndex]->getY() + rooms[tempRoomIndex]->getHeight() -2 - rand() % (rooms[tempRoomIndex]->getHeight() -2);
            }while(getElementType(tempY, tempX) != 2 || getDistance(this->player->getX(), this->player->getY(), exitX, exitY) < 100);
            //Cycle goes on if the player is too close to the exit

            player = new Player(name, tempX, tempY, atoi(classNode->first_node("baseStats")->first_attribute("mpMax")->value()), 
            stof(classNode->first_node("baseStats")->first_attribute("hpMax")->value()), stof(classNode->first_node("baseStats")->first_attribute("str")->value()), 
            stof(classNode->first_node("baseStats")->first_attribute("dex")->value()), stof(classNode->first_node("baseStats")->first_attribute("mnd")->value()), 
            stof(classNode->first_node("baseStats")->first_attribute("wis")->value()), stof(classNode->first_node("baseStats")->first_attribute("res")->value()), 
            stof(classNode->first_node("baseStats")->first_attribute("movT")->value()), stof(classNode->first_node("baseStats")->first_attribute("actT")->value()), 
            temp, "0x0050");
            //Set level up stats
            player->setUpHpMax(stof(classNode->first_node("levelUpStats")->first_attribute("hpMax")->value()));
            player->setUpMpMax(stof(classNode->first_node("levelUpStats")->first_attribute("mpMax")->value()));
            player->setUpStr(stof(classNode->first_node("levelUpStats")->first_attribute("str")->value()));
            player->setUpDex(stof(classNode->first_node("levelUpStats")->first_attribute("dex")->value()));
            player->setUpMnd(stof(classNode->first_node("levelUpStats")->first_attribute("mnd")->value()));
            player->setUpWis(stof(classNode->first_node("levelUpStats")->first_attribute("wis")->value()));
            player->setUpRes(stof(classNode->first_node("levelUpStats")->first_attribute("res")->value()));
            player->setUpMovT(stof(classNode->first_node("levelUpStats")->first_attribute("movT")->value()));
            player->setUpActT(stof(classNode->first_node("levelUpStats")->first_attribute("actT")->value()));
            
            
            for(xml_node<>* equipNode = classNode->first_node("startingEquipment")->first_node(); equipNode; equipNode = equipNode->next_sibling()){
                //Give player his starting weapons
                std::vector<Weapon>::iterator it = inventoryWeapons.begin();
                std::vector<Weapon>::iterator end = inventoryWeapons.end();
                for(it; it != end; it++){
                    if(areStringsEqual(equipNode->first_attribute("label")->value(), it->getLabel())){
                        unique_ptr<InventoryElement> a (new Weapon(*it, 0, 0));
                        a->setIdentified(true);
                        player->addInventoryElement(a, false);
                    }
                }
                //Give player his starting scrolls
                std::vector<Scroll>::iterator it2 = inventoryScrolls.begin();
                std::vector<Scroll>::iterator end2 = inventoryScrolls.end();
                for(it2; it2 != end2; it2++){
                    if(areStringsEqual(equipNode->first_attribute("label")->value(), it2->getLabel())){
                        unique_ptr<InventoryElement> a (new Scroll(*it2, 0, 0));
                        a->setIdentified(true);
                        player->addInventoryElement(a, false);
                    }
                }
                //Give player his starting items
                std::vector<InventoryElement>::iterator it3 = inventoryItems.begin();
                std::vector<InventoryElement>::iterator end3 = inventoryItems.end();
                for(it3; it3 != end3; it3++){
                    if(areStringsEqual(equipNode->first_attribute("label")->value(), it3->getLabel())){
                        unique_ptr<InventoryElement> a (new InventoryElement(*it3));
                        a->setIdentified(true);
                        player->addInventoryElement(a, false);
                    }
                }
            }
            
            std::cout<<"\n\n"<<name<<", press enter to begin your adventure!\n";
            cin.ignore();
        }
    }
}

void Game::clearFog(){
    for(int i = player->getY() - PLAYER_SIGHT; i != player->getY() + PLAYER_SIGHT +1; i++){
        for(int j = player->getX() - PLAYER_SIGHT; j != player->getX() + PLAYER_SIGHT +1; j++){
            fogMatrix[i][j] = true;
        }
    }
}

void Game::moveEnemies(){
    int direction;
    int tempX;
    int tempY;
    std::vector<std::unique_ptr<Enemy>>::iterator end = enemies.end();
    for (std::vector<std::unique_ptr<Enemy>>::iterator it = enemies.begin(); it != end; it++ ){
        if((**it).getNextActTime() <= lapsedTime){
            //If player is in attack range, attack it
            if(getDistance((**it), *player) <= (**it).getAttackRange()){
                this->player->takeDamage((**it).getLabel(), (**it).getAtkDamage());
                std::cout<<"\n\n"<<(**it).getY()<<"  "<<(**it).getX()<<"  "<<(**it).getAttackRange()<< "   "<<getDistance((**it), *player);
            }
            //If player is in sight range, move towards him
            else if(getDistance((**it), *player) <= (**it).getSightRange()){
                walkShortestPath(**it, this->player->getX(), this->player->getY());
                (**it).setNextActTime(this->lapsedTime + (**it).getMovTime());
            }
            //If none, just move randomly
            else{
                do{
                    direction = 1 + (rand() % 4);
                    switch (direction)
                    {
                    case 1: //Up
                        tempX = (**it).getX();
                        tempY = (**it).getY() - 1;
                        break;
                    case 2: //Down
                        tempX = (**it).getX();
                        tempY = (**it).getY() + 1;
                        break;
                    case 3: //Left
                        tempX = (**it).getX() - 1;
                        tempY = (**it).getY();
                        break;
                    case 4: //Right
                        tempX = (**it).getX() + 1;
                        tempY = (**it).getY();
                        break;
                    }
                }while(!isWalkable(tempX, tempY));
                (**it).setCoordinates(tempX, tempY);
                (**it).setNextActTime(this->lapsedTime + (**it).getMovTime());
            }
        }
    }
}

unsigned int Game::getDistance(Character& a, Character& b) const{
    return (abs((int)(a.getX() - b.getX())) + abs(((int)(a.getY() - b.getY()))));
}

unsigned int Game::getDistance(int x1, int y1, int x2, int y2) const{
    return (abs(x1 - x2) + abs(y1 - y2));
}

int Game::getEnemyIndexAtPosition(unsigned int i, unsigned int j){
    std::vector<std::unique_ptr<Enemy>>::iterator enemyEnd = enemies.end();
    for (std::vector<std::unique_ptr<Enemy>>::iterator enemyIt = enemies.begin(); enemyIt != enemyEnd; enemyIt++){
        if((**enemyIt).getY() == i && (**enemyIt).getX() == j)
            return enemyIt - enemies.begin();
    }
    return -1;
}

int Game::getItemIndexAtPosition(unsigned int i, unsigned int j){
    //Check if it's a consumable
    std::vector<std::unique_ptr<InventoryElement>>::iterator end = items.end();
    for (std::vector<std::unique_ptr<InventoryElement>>::iterator it = items.begin(); it != end; it++){
        if((**it).getY() == i && (**it).getX() == j){
            return it - items.begin();
        }
    }
    return -1;
}

int Game::getWeaponIndexAtPosition(unsigned int i, unsigned int j){
    //Check if it's a weapon
    std::vector<std::unique_ptr<Weapon>>::iterator end3 = weapons.end();
    for (std::vector<std::unique_ptr<Weapon>>::iterator it = weapons.begin(); it != end3; it++){
        if((**it).getY() == i && (**it).getX() == j){
            return it - weapons.begin();
        }
    }
    return -1;
}

int Game::getScrollIndexAtPosition(unsigned int i, unsigned int j){
    //Check if it's a scroll
    std::vector<std::unique_ptr<Scroll>>::iterator end4 = scrolls.end();
    for (std::vector<std::unique_ptr<Scroll>>::iterator it = scrolls.begin(); it != end4; it++){
        if((**it).getY() == i && (**it).getX() == j){
            return it - scrolls.begin();
        }
    }
    return -1;
}

void Game::playerLoot(){
    for(int i = -1; i != 2; i++){
        for(int j = -1; j != 2; j++){
            if(i != 0 || j != 0){
                unsigned int tempX = player->getX() + j;
                unsigned int tempY = player->getY() + i;
                if(tempX >= 0 && tempX <= MAX_MATRIX_WIDTH - 1 && tempY >= 0 && tempY <= MAX_MATRIX_HEIGHT - 1){
                    int temp = getItemIndexAtPosition(tempY, tempX);
                    if(temp != -1 && !items.at(temp)->getIsChest()){
                        //It's a consumable
                        player->addInventoryElement(items.at(temp), true);
                        items.erase(items.begin() + temp);
                    }else{
                        temp = getWeaponIndexAtPosition(tempY, tempX);
                        if(temp != -1){
                            //It's a weapon
                            std::unique_ptr<InventoryElement> t (std::move(weapons.at(temp)));
                            weapons.erase(weapons.begin() + temp);
                            player->addInventoryElement(t, true);
                       }else{
                            temp = getScrollIndexAtPosition(tempY, tempX);
                            if(temp != -1){
                                //It's a scroll
                                std::unique_ptr<InventoryElement> t (std::move(scrolls.at(temp)));
                                scrolls.erase(scrolls.begin() + temp);
                                player->addInventoryElement(t, true);
                            }
                       }
                    }
                }
            }
        }
    }
}

bool Game::playerCastSpell(char direction, unsigned int index){
        //Check if player has enough mana
        if(this->getPlayer()->getMP() - this->getPlayer()->getScrollAt(index).getMpCost() < 0){
            std::cout<<"\nYOU HAVE NO MANA!!!";
            std::cin.ignore();
            return false;
        }
        //Decrease player's mana
        this->getPlayer()->setMp(this->getPlayer()->getMP() - this->getPlayer()->getScrollAt(index).getMpCost());
        history += "\n" + this->getPlayer()->getLabel() + " used the scroll " + this->getPlayer()->getInventoryElementAt(index).getLabel() + ".";
        unsigned int tempI = this->getPlayer()->getY();
        unsigned int tempJ = this->getPlayer()->getX();
        int iInc = 0;
        int jInc = 0;
        if(tolower(direction) == 'w')
            iInc = -1;
        else if(tolower(direction) == 's')
            iInc = 1;
        else if(tolower(direction) == 'a')
            jInc = -1;
        else
            jInc = 1;
            
        //Apply AOEs
        std::vector<Square> t = this->getPlayer()->getScrollAOEAt(index); 
        std::vector<Square>::iterator it = t.begin();
        std::vector<Square>::iterator end = t.end();
        //Iterate over weapon's AOEs
        for(it; it != end; it ++){
            playerAOE(*(it), this->getPlayer()->getAtkDamage(it->getStat(), it->getPot()), this->getPlayer()->getScrollAt(index).getRange(), iInc, jInc);
        }

        //Apply self effects
        std::vector<SelfEffect> t2 = this->getPlayer()->getScrollSelfEffectsAt(index); 
        std::vector<SelfEffect>::iterator it2 = t2.begin();
        std::vector<SelfEffect>::iterator end2 = t2.end();
        //Iterate over weapon's AOEs
        for(it2; it2 != end2; it2 ++){
            this->getPlayer()->applySelfEffect(*it2);
        }
}

void Game::playerAttack(char direction){
    int weaponIndex = this->getPlayer()->getEquippedWeaponIndex();
    unsigned int tempI = this->getPlayer()->getY();
    unsigned int tempJ = this->getPlayer()->getX();
    int iInc = 0;
    int jInc = 0;

    if(tolower(direction) == 'w')
        iInc = -1;
    else if(tolower(direction) == 's')
        iInc = 1;
    else if(tolower(direction) == 'a')
        jInc = -1;
    else
        jInc = 1;

    std::vector<Square> t = this->getPlayer()->getEquippedWeaponAOE();
    if(t.size() == 0){
        //If the weapon has no AOEs/player has no weapon equipped, just attack forward with pot=1 and scaling on STR
        Square temp = Square(1, 0, "str", 1);
        playerAOE(temp, this->getPlayer()->getAtkDamage("str", 1), 0, iInc, jInc);
    }else{
        std::vector<Square>::iterator it = t.begin();
        std::vector<Square>::iterator end = t.end();
        //Iterate over weapon's AOEs
        for(it; it != end; it ++){
            playerAOE((*(it)), this->getPlayer()->getAtkDamage(it->getStat(), it->getPot()), this->getPlayer()->getWeaponAt(weaponIndex).getRange(), iInc, jInc);
        }
        //Reduce weapon's durability
        this->getPlayer()->reduceWeaponDurability(weaponIndex);
    }

}

void Game::playerAOE(Square effect, unsigned int damage, unsigned int range, int iInc, int jInc){
    unsigned int tempI = this->getPlayer()->getY();
    unsigned int tempJ = this->getPlayer()->getX();
    //Go to the origin point
    for(int k = 0; k != range; k++){
        tempI += iInc;
        tempJ += jInc;
        if(getEnemyIndexAtPosition(tempI, tempJ) != -1)
            break;
    }
    int i = tempI;
    int j = tempJ;
    int fd;
    int rd;
    fd = effect.getFd();
    rd = effect.getRd();
    if(iInc != 0){
        //std::cout<<"\n\n\n"<<i + (iInc * fd)<<"  "<< j + rd;
        int tempIndex = getEnemyIndexAtPosition(i + (iInc * fd), j + rd);
        if(tempIndex > -1){
            if(!enemies.at(tempIndex)->takeDamage(this->getPlayer()->getLabel(), damage)){
                //Enemy died
                history += "\n" + this->getPlayer()->getLabel() + " obtained " + std::to_string(enemies.at(tempIndex)->getGp()) + " gp.";
                this->getPlayer()->addGold(enemies.at(tempIndex)->getGp());
                history += "\n" + this->getPlayer()->getLabel() + " obtained " + std::to_string(enemies.at(tempIndex)->getExp()) + " exp.";
                this->getPlayer()->addExp(enemies.at(tempIndex)->getExp());
                enemies.erase(enemies.begin() + tempIndex);
            }
        }
    }else{
        //std::cout<<"\n\n\n"<<i + rd<<"  "<< j + (jInc * fd);
        int tempIndex = getEnemyIndexAtPosition(i + rd, j + (jInc * fd));
        if(tempIndex > -1){
            if(!enemies.at(tempIndex)->takeDamage(this->getPlayer()->getLabel(), damage)){
                //Enemy died
                history += "\n" + this->getPlayer()->getLabel() + " obtained " + std::to_string(enemies.at(tempIndex)->getGp()) + " gp.";
                this->getPlayer()->addGold(enemies.at(tempIndex)->getGp());
                history += "\n" + this->getPlayer()->getLabel() + " obtained " + std::to_string(enemies.at(tempIndex)->getExp()) + " exp.";
                this->getPlayer()->addExp(enemies.at(tempIndex)->getExp());
                enemies.erase(enemies.begin() + tempIndex);
            }

        }
    }
}

bool Game::playerOpen(char direction){
    int iInc = 0;
    int jInc = 0;

    if(tolower(direction) == 'w')
        iInc = -1;
    else if(tolower(direction) == 's')
        iInc = 1;
    else if(tolower(direction) == 'a')
        jInc = -1;
    else
        jInc = 1;
    unsigned int tempI = this->player->getY() + iInc;
    unsigned int tempJ = this->player->getX() + jInc;

    if(getElementType(tempI, tempJ) == 1){
        //It's a door
        std::vector<std::unique_ptr<Door>>::iterator end = rooms.at(abs(m[tempI][tempJ])-4)->doors.end();
        for (std::vector<std::unique_ptr<Door>>::iterator it = rooms.at(abs(m[tempI][tempJ])-4)->doors.begin(); it != end; it++ ){
            if((**it).getY() == tempI && (**it).getX() == tempJ){
                if(!(**it).isLocked()){
                    std::cout<<"\nThe door is already open.";
                    std::cin.ignore();
                    return false;
                }else{
                    std::string choice;
                    while(true){
                        std::cout<<"\nDo you want to use a key or perform an ability check? key/ability check\n";
                        getline(std::cin, choice);

                        if(areStringsEqual(choice, "key")){
                            if(this->player->getKeys() > 0){
                                history += "\n" + this->player->getLabel() + " opened a door using a key.";
                                this->player->addKeys(-1);
                                (**it).setLocked(false);
                                return true;
                            }
                            std::cout<<"\nYou don't have any keys.";
                        }else if(areStringsEqual(choice, "ability check")){
                            int result = this->player->abilityCheck("str", 15);
                            if(result >= 0){
                                history += "\n" + this->player->getLabel() + " opened a door.";
                                (**it).setLocked(false);
                            }else{
                                history += "\n" + this->player->getLabel() + " failed to open a door.";
                                this->player->takeDamage("Door", abs((int)(result)/2));
                            }
                            return true;
                        }else
                            std::cout<<"\nInsert a valid input.";
                    }
                }
            }
        }
    }else if(getElementType(this->player->getY() + iInc, this->player->getX() + jInc) == 7){
        //It's a chest
        std::vector<std::unique_ptr<InventoryElement>>::iterator end = items.end();
        for (std::vector<std::unique_ptr<InventoryElement>>::iterator it = items.begin(); it != end; it++ ){
            if((**it).getY() == tempI && (**it).getX() == tempJ){
                std::string choice;
                    while(true){
                        std::cout<<"\nDo you want to use a key or perform an ability check? key/ability check\n";
                        getline(std::cin, choice);

                        if(areStringsEqual(choice, "key")){
                            if(this->player->getKeys() > 0){
                                history += "\n" + this->player->getLabel() + " opened a chest using a key.";
                                this->player->addInventoryElement(*it, true);
                                this->player->addKeys(-1);
                                items.erase(it);
                                return true;
                            }
                            std::cout<<"\nYou don't have any keys.";
                        }else if(areStringsEqual(choice, "ability check")){
                            int result = this->player->abilityCheck("dex", 15);
                            if(result >= 0){
                                history += "\n" + this->player->getLabel() + " opened a chest.";
                                this->player->addInventoryElement(*it, true);
                                items.erase(it);
                            }else{
                                history += "\n" + this->player->getLabel() + " opened a chest but also got injured.";
                                this->player->takeDamage("Chest", abs(result)/3);
                                this->player->addInventoryElement(*it, true);
                                items.erase(it);
                            }
                            items.erase(it);
                            return true;
                        }else{
                            std::cout<<"\nInsert a valid input.";
                        }
                    }
            }
            
        }
    }else{
        std::cout<<"\nThere is nothing to open in this direction.";
        std::cin.ignore();
        return false;
    }
}

bool Game::playerUse(unsigned int index){
    //Check if the index is valid
    if(this->player->getInventorySize() > index){
        if(areStringsEqual(this->player->getInventoryElementAt(index).getType(), "herb")
        || areStringsEqual(this->player->getInventoryElementAt(index).getType(), "potion")){
            std::vector<Effect> t = this->player->getInventoryElementAt(index).getEffects();
            std::vector<Effect>::iterator it = t.begin();
            std::vector<Effect>::iterator end = t.end();
            history += "\n" + this->player->getLabel() + " used " + this->player->getInventoryElementAt(index).getLabel() + ".";
            for(it; it != end; it++){
                this->getPlayer()->applyEffect(*it);
            }
            this->player->discardItem(index);
            return true;
        }
        std::cout<<"\nYou can't use this item.";
        fflush(stdin);
        std::cin.ignore();
        return false;
    }
    std::cout<<"\nThere is no item at this index.";
    fflush(stdin);
    std::cin.ignore();
    return false;
}

void Game::getBestiary(){
    using namespace rapidxml;
    using namespace std;
    xml_document<> doc;
	xml_node<> * root_node;
    ifstream xmlFile ("xml/enemies.xml"); 

    //Indicate start and end of the stream
    vector<char> buffer((istreambuf_iterator<char>(xmlFile)), istreambuf_iterator<char>());
    //Add the "end file character" at the end of the file
	buffer.push_back('\0');
	//Parse the buffer using the xml file parsing library into doc, now the xml_document is ready
	doc.parse<0>(&buffer[0]);
	//Assign the root node to root_node (the method returns and address)
	root_node = doc.first_node("enemies");
    std::unique_ptr<Enemy> enemy;
    for (xml_node<> * enemyNode = root_node->first_node("enemy"); enemyNode; enemyNode = enemyNode->next_sibling()){
        enemy = std::unique_ptr<Enemy>(new Enemy(0, 0, stof(enemyNode->first_node("baseStats")->first_attribute("hpMax")->value()), stof(enemyNode->first_node("baseStats")->first_attribute("str")->value()),
        stof(enemyNode->first_node("baseStats")->first_attribute("dex")->value()), stof(enemyNode->first_node("baseStats")->first_attribute("mnd")->value()),
        stof(enemyNode->first_node("baseStats")->first_attribute("wis")->value()), stof(enemyNode->first_node("baseStats")->first_attribute("res")->value()),
        stof(enemyNode->first_node("baseStats")->first_attribute("movT")->value()), stof(enemyNode->first_node("baseStats")->first_attribute("actT")->value()),
        (enemyNode->first_node("enemyStats")->first_attribute("atkStat")->value()), atoi(enemyNode->first_node("enemyStats")->first_attribute("atkRange")->value()),
        atoi(enemyNode->first_node("enemyStats")->first_attribute("sight")->value()), atoi(enemyNode->first_node("enemyStats")->first_attribute("exp")->value()),
        atoi(enemyNode->first_node("enemyStats")->first_attribute("gp")->value()), enemyNode->first_attribute("label")->value(), enemyNode->first_attribute("ch")->value()));

        bestiaryEnemies.push_back(std::move(enemy));
    }
}

void Game::getItems(){
    using namespace rapidxml;
    using namespace std;
    xml_document<> doc;
	xml_node<> * root_node;
    ifstream xmlFile ("xml/items.xml"); 

    //Indicate start and end of the stream
    vector<char> buffer((istreambuf_iterator<char>(xmlFile)), istreambuf_iterator<char>());
    //Add the "end file character" at the end of the file
	buffer.push_back('\0');
	//Parse the buffer using the xml file parsing library into doc, now the xml_document is ready
	doc.parse<0>(&buffer[0]);
	//Assign the root node to root_node (the method returns and address)
	root_node = doc.first_node("items");
    for (xml_node<> * itemNode = root_node->first_node(); itemNode; itemNode = itemNode->next_sibling()){
        if(areStringsEqual(itemNode->name(), "weapon")){
            //It's a weapon
            inventoryWeapons.push_back(Weapon(0, 0, itemNode->first_attribute("label")->value(), itemNode->name(), itemNode->first_attribute("ch")->value(), atoi(itemNode->first_attribute("durability")->value()), atoi(itemNode->first_attribute("range")->value())));
            //Add effects to the weapon
            xml_node<> * tempNode = itemNode->first_node("bonusStats");
            if(tempNode != nullptr){
                for (xml_node<> * effectNode = tempNode->first_node("effect"); effectNode; effectNode = effectNode->next_sibling()){
                    inventoryWeapons.back().addEffect(Effect(effectNode->first_attribute("stat")->value(), stof(effectNode->first_attribute("value")->value())));
                }
            }
            //AreasOfEffect to the weapon
            tempNode = itemNode->first_node("areaOfEffect");
            if(tempNode != nullptr){
                for (xml_node<> * effectNode = tempNode->first_node("square"); effectNode; effectNode = effectNode->next_sibling()){
                    inventoryWeapons.back().addAreasOfEffect(Square(atoi(effectNode->first_attribute("fd")->value()), atoi(effectNode->first_attribute("rd")->value()), effectNode->first_attribute("stat")->value(), stof(effectNode->first_attribute("pot")->value())));
                }
            }
        }else if(areStringsEqual(itemNode->name(), "scroll")){
            //It's a scroll
            inventoryScrolls.push_back(Scroll(0, 0, itemNode->first_attribute("label")->value(), itemNode->name(), itemNode->first_attribute("ch")->value(), atoi(itemNode->first_attribute("range")->value()), stof(itemNode->first_attribute("mpCost")->value())));
            //Add self effects to the scroll
            xml_node<> * tempNode = itemNode->first_node("selfEffects");
            if(tempNode != nullptr){
                for (xml_node<> * effectNode = tempNode->first_node("effect"); effectNode; effectNode = effectNode->next_sibling()){
                    inventoryScrolls.back().addSelfEffect(SelfEffect(effectNode->first_attribute("stat")->value(), stof(effectNode->first_attribute("pot")->value()), effectNode->first_attribute("potStat")->value()));
                }
            }
            //Add AreasOfEffect to the scroll
            tempNode = itemNode->first_node("areaOfEffect");
            if(tempNode != nullptr){
                for (xml_node<> * effectNode = tempNode->first_node("square"); effectNode; effectNode = effectNode->next_sibling()){
                    inventoryScrolls.back().addAreasOfEffect(Square(atoi(effectNode->first_attribute("fd")->value()), atoi(effectNode->first_attribute("rd")->value()), effectNode->first_attribute("stat")->value(), stof(effectNode->first_attribute("pot")->value())));
                }
            }
        }else{
            //It's a generic item
            inventoryItems.push_back(InventoryElement(0, 0, itemNode->first_attribute("label")->value(), itemNode->name(), itemNode->first_attribute("ch")->value()));
            //Add effects to the item
            for (xml_node<> * effectNode = itemNode->first_node("effect"); effectNode; effectNode = effectNode->next_sibling()){
                inventoryItems.back().addEffect(Effect(effectNode->first_attribute("stat")->value(), stof(effectNode->first_attribute("value")->value())));
            }
        }
    }
}

void Game::printUnicode(std::string character, unsigned int color) const{
    switch (color)
    {
    case 1:
        //Player green
        std::cout<<termcolor::green;
        break;
    case 2:
        //High health enemy
        std::cout <<termcolor::blue;
        break;
    case 3:
        //Mid high health enemy
        std::cout<<termcolor::magenta;
        break;
    case 4:
        //Mid low health enemy
        std::cout<<termcolor::yellow;
        break;
    case 5:
        //Low health enemy
        std::cout<<termcolor::red;
        break;
    default:
        break;
    }
    int dec = (int)strtol(character.c_str(), NULL, 16);
    if(dec < 128){
        //1 byte
        printf("%c", dec);
    }else{
        std::string binary = "";
        int started = false;
        int n;
        //Convert to binary
        for(int i = 2; i != character.length(); i++){
            switch(toupper(character[i]))
            {
                case '0':
                    binary += "0000";
                    break;
                case '1':
                    binary += "0001";
                    break;
                case '2':
                    binary += "0010";
                    break;
                case '3':
                    binary += "0011";
                    break;
                case '4':
                    binary += "0100";
                    break;
                case '5':
                    binary += "0101";
                    break;
                case '6':
                    binary += "0110";
                    break;
                case '7':
                    binary += "0111";
                    break;
                case '8':
                    binary += "1000";
                    break;
                case '9':
                    binary += "1001";
                    break;
                case 'A':
                    binary += "1010";
                    break;
                case 'B':
                    binary += "1011";
                    break;
                case 'C':
                    binary += "1100";
                    break;
                case 'D':
                    binary += "1101";
                    break;
                case 'E':
                    binary += "1110";
                    break;
                case 'F':
                    binary += "1111";
                    break;
            }
        }
        if(dec >= 67108864){
            //6 bytes
            n = 6;            
        }else if(dec >= 2097152){
            //5 bytes
            n = 5;
        }else if(dec >= 65536){
            //2 bytes
            n = 4;
        }else if(dec >= 2048){
            //3 bytes
            n = 3;
        }else if(dec >= 128){
            //2 bytes
            n = 2;
        }
        std::string bytes[n];
        int i;
        for(i = 0; i != n; i++){
            bytes[0] += '1';
            if(i + 1 < n)
                bytes[i + 1] += "10";
        }
        bytes[0] += '0';
        //Delete the initial bytes
        for(i = 0; binary.size() > (8*n) - (n+1) - 2*(n-1); i++){
            binary.erase(binary.begin());
        }

        //Add the binary numbers to every byte
        int j = 0;
        //First byte
        for(j; j != 8 - (n+1); j++){
            bytes[0] += binary[j];
        }
        //std::cout<<"\n"<<bytes[0];
        //Other bytes
        int c;
        for(i = 1; i != n; i++){
            for(c = 0; c != 6; c++){
                bytes[i] += binary[j + c];
            } 
            j += c;
        }

        switch (n)
        {
        case 2:
            printf("%c%c", std::stoi(bytes[0], nullptr, 2), std::stoi(bytes[1], nullptr, 2));
            break;
        case 3:
            printf("%c%c%c", std::stoi(bytes[0], nullptr, 2), std::stoi(bytes[1], nullptr, 2), std::stoi(bytes[2], nullptr, 2));
            break;
        case 4:
            printf("%c%c%c%c", std::stoi(bytes[0], nullptr, 2), std::stoi(bytes[1], nullptr, 2), std::stoi(bytes[2], nullptr, 2), std::stoi(bytes[3], nullptr, 2));
            break;
        case 5:
            printf("%c%c%c%c%c", std::stoi(bytes[0], nullptr, 2), std::stoi(bytes[1], nullptr, 2), std::stoi(bytes[2], nullptr, 2), std::stoi(bytes[3], nullptr, 2), std::stoi(bytes[4], nullptr, 2));
            break;
        case 6:
            printf("%c%c%c%c%c", std::stoi(bytes[0], nullptr, 2), std::stoi(bytes[1], nullptr, 2), std::stoi(bytes[2], nullptr, 2), std::stoi(bytes[3], nullptr, 2), std::stoi(bytes[4], nullptr, 2), std::stoi(bytes[5], nullptr, 2));
            break;
        default:
            break;
        }
    }

    std::cout << termcolor::reset;
}

void Game::printRange(std::vector<Square> areasOfEffect){
    int y = 0;
    for (int i = player->getY() - (MAP_HEIGHT/2); i != player->getY() + (MAP_HEIGHT/2) +1; i++) {
        y++;
		for (int j = player->getX() - (MAP_WIDTH/2); j != player->getX() + (MAP_WIDTH/2) +1; j++) {
            if(j < 0 || i < 0 || j > MAX_MATRIX_WIDTH || i > MAX_MATRIX_HEIGHT){
                std::cout<<" ";
            }else{
                //Check if Player is in this position
                if(player->getY() == i && player->getX() == j)
                    printUnicode(player->getCh(), 1);
                else if(fogMatrix[i][j] == true){
                    //Check if an enemy is in this position
                    std::vector<std::unique_ptr<Enemy>>::iterator end = enemies.end();
                    bool written = false;
                    for (std::vector<std::unique_ptr<Enemy>>::iterator it = enemies.begin(); it != end; it++ ){
                        if((**it).getY() == i && (**it).getX() == j){
                            written = true;
                            if(((*it)->getHP() * 100)/((*it)->getMaxHP()) >= 75)
                                printUnicode((*it)->getCh(), 2);
                            else if (((*it)->getHP() * 100)/((*it)->getMaxHP()) >= 50)
                                printUnicode((*it)->getCh(), 3);
                            else if (((*it)->getHP() * 100)/((*it)->getMaxHP()) >= 25)
                                printUnicode((*it)->getCh(), 4);
                            else
                                printUnicode((*it)->getCh(), 5);
                        }
                    }
                    //Check if an item is in this position
                    std::vector<std::unique_ptr<InventoryElement>>::iterator end2 = items.end();
                    for (std::vector<std::unique_ptr<InventoryElement>>::iterator it = items.begin(); it != end2; it++ ){
                        if((**it).getY() == i && (**it).getX() == j){
                            written = true;
                            printUnicode((*it)->getCh(), 0);
                        }
                    }
                    //Check if a weapon is in this position
                    std::vector<std::unique_ptr<Weapon>>::iterator end3 = weapons.end();
                    for (std::vector<std::unique_ptr<Weapon>>::iterator it = weapons.begin(); it != end3; it++){
                        if((**it).getY() == i && (**it).getX() == j){
                            written = true;
                            printUnicode((*it)->getCh(), 0);
                        }
                    }

                    //Check if a scroll is in this position
                    std::vector<std::unique_ptr<Scroll>>::iterator end4 = scrolls.end();
                    for (std::vector<std::unique_ptr<Scroll>>::iterator it = scrolls.begin(); it != end4; it++){
                        if((**it).getY() == i && (**it).getX() == j){
                            written = true;
                            printUnicode((*it)->getCh(), 0);
                        }
                    }

                    //Check if it's a map element
                    if(!written){
                        switch (getElementType(i, j)){
                            case 0:
                            //Nothing
                                std::cout<<" ";
                                break;
                            case 1:
                                //Door
                                {
                                    std::vector<std::unique_ptr<Door>>::iterator end = rooms.at(abs(m[i][j]) - 4)->doors.end();
                                    std::vector<std::unique_ptr<Door>>::iterator it = rooms.at(abs(m[i][j]) - 4)->doors.begin();
                                    //Iterate over every door of the connected room to check if it is the right one
                                    for (it; it != end; it++){
                                        if((**it).getY() == i && (**it).getX() == j){
                                            if((**it).isLocked())
                                                printUnicode((**it).getChLocked(), 0);
                                            else
                                                printUnicode((**it).getChUnlocked(), 0);
                                            break;
                                        }
                                    }
                                }
                                break;
                            case 2:
                                //Floor
                                printUnicode(rooms.at(abs(m[i][j]) - 4)->getChFloor(), 0);
                                break;
                            case 3:
                                //Path
                                printUnicode(chPath, 0);
                                break;
                            case 4:
                                //Wall
                                printUnicode(rooms.at(abs(m[i][j]) - 4)->getChWall(), 0);
                                break;
                            case 8:
                                //Exit
                                printUnicode(this->chExit, 0);
                                break;
                            default:
                                break;
                        }
                    }
                }else{
                    //It's int the fog
                    printUnicode(chFog, 0);
                }
            }
                          
		}
        std::cout<<"   ";
        switch (y){
                case 1:
                    std::cout<<"Name: "<<player->getLabel();
                    break;
                case 2:
                    std::cout<<"Class: "<<player->getPlayerClass();
                    break;
                case 3:
                    std::cout<<"Level: "<<player->getLvl();
                    break;
                case 4:
                    std::cout<<"HP: "<<player->getHP()<<"/"<<player->getMaxHP();
                    std::cout<<"    ";
                    std::cout<<"MP: "<<player->getMP()<<"/"<<player->getMaxMP();
                    break;
                case 5:
                    std::cout<<"STR: "<<player->getStr();
                    std::cout<<"    ";
                    std::cout<<"DEX: "<<player->getDex();
                    std::cout<<"    ";
                    std::cout<<"MND: "<<player->getMnd();
                    std::cout<<"    ";
                    std::cout<<"WIS: "<<player->getWis();
                    break;
                case 6:
                    std::cout<<"ActTime: "<<player->getActTime();
                    std::cout<<"    ";
                    std::cout<<"MovTime: "<<player->getMovTime();
                    std::cout<<"    ";
                    std::cout<<"Res: "<<player->getRes();
                    break;
                case 7:
                    std::cout<<"Exp: "<<player->getExp()<<"/"<<player->getLvl()*100;
                    break;
                case 8:
                    std::cout<<"GP: "<<player->getGp();
                    std::cout<<"    ";
                    std::cout<<"Keys: "<<player->getKeys();
                    break;
                case 9:
                    std::cout<<"LapsedTime: "<<lapsedTime;
                    break;
                case 11:
                    std::cout<<"Inventory";
                    break;
            default:
                if(y >= 12 && y <= 21){
                    std::cout<<y-12;
                    if(y-12 < player->getInventorySize()){
                        if(player->getInventoryElementAt(y-12).getIsEquipped())
                            std::cout<<" E : ";
                        else
                            std::cout<<"   : ";
                        if(player->getInventoryElementAt(y-12).getIsIdentified())
                            std::cout<<player->getInventoryElementAt(y-12).getLabel();
                        else if(areStringsEqual(player->getInventoryElementAt(y-12).getType(), "herb"))
                            std::cout<<"Unidentified herb";
                        else
                            std::cout<<"???";
                    }else
                        std::cout<<"   : ";
                }
                break;
            }
		std::cout << std::endl;
	}
}

void Game::checkBox(std::shared_ptr<Box> current, std::shared_ptr<Box> temp, std::vector<std::shared_ptr<Box>>& openList, std::vector<std::shared_ptr<Box>>& closedList, unsigned int targetX, unsigned int targetY){
    //Check if temp is in the closedList
    bool closed = false;
    std::vector<std::shared_ptr<Box>>::iterator it = closedList.begin();
    std::vector<std::shared_ptr<Box>>::iterator end = closedList.end();
    for(it; it != end; it ++){
        //If the square is in the closedList...
        if((**it).getX() == temp->getX() && (**it).getY() == temp->getY()){
             //Don't add it to the openList
            closed = true;
        }
    }

    if(!closed){
        //Check if temp is in the openList
        bool open = false;
        it = openList.begin();
        end = openList.end();
        for(it; it != end; it ++){
            //If the square is in the openList...
            if((**it).getX() == temp->getX() && (**it).getY() == temp->getY()){
                open = true;
                unsigned int newGScore = current->getG() + 1;
                unsigned int newHScore = getDistance(temp->getX(), temp->getY(), targetX, targetY);
                if(newGScore + newHScore < (**it).getG() + (**it).getH()){
                    (**it).setG(newGScore);
                    (**it).setH(newHScore);
                    std::shared_ptr<Box> t = (current->getPreviousBox()); 
                    (**it).setPreviousBox(t); 
                }
            }
        }
        if(!open){
            openList.push_back(temp);
        }
    }
}

void Game::walkShortestPath(Character& c, unsigned int targetX, unsigned int targetY){
    bool found = false;
    //Create open list
    std::vector<std::shared_ptr<Box>> openList;
    //Create closed list
    std::vector<std::shared_ptr<Box>> closedList;
    //Set the current square
    std::shared_ptr<Box> current = std::make_shared<Box> (Box(c.getX(), c.getY(), 0, 0));
    while(true){
        //TEMP INIZIO
        /*for (int i = player->getY() - (MAP_HEIGHT/2); i != player->getY() + (MAP_HEIGHT/2) +1; i++) {
            for (int j = player->getX() - (MAP_WIDTH/2); j != player->getX() + (MAP_WIDTH/2) +1; j++) {
                if(j < 0 || i < 0 || j > MAX_MATRIX_WIDTH || i > MAX_MATRIX_HEIGHT){
                    std::cout<<" ";
                }else{
                    //Check if Player is in this position
                    if(player->getY() == i && player->getX() == j)
                        printUnicode(player->getCh(), 1);
                    else if(!isWalkable(j, i))
                        std::cout<<"X";
                    else{
                        std::vector<std::shared_ptr<Box>>::iterator it = openList.begin();
                        std::vector<std::shared_ptr<Box>>::iterator end = openList.end();
                        bool written = false;
                        for(it; it != end; it ++){
                            if((**it).getX() == j && (**it).getY() == i){
                                written = true;
                                std::cout<<termcolor::green<<"."<<termcolor::reset;
                            }
                        }
                        it = closedList.begin();
                        end = closedList.end();
                        for(it; it != end; it ++){
                            if((**it).getX() == j && (**it).getY() == i){
                                written = true;
                                std::cout<<termcolor::red<<"."<<termcolor::reset;
                            }
                        }
                        
                        
                        if(!written)
                            std::cout<<".";
                    }
                }
            }
            std::cout<<std::endl;
        }
        */
        //TEMP FINE
        //Add the walkable squares to the open list if necessary
        //Upper square
        //Check if the target is in the open list
        //std::cout<<"\n\nROSSO: "<<current->getX()<<"   "<<current->getY();
        //std::cout<<"\n\nCURRENT: "<<current->getX()<<"   "<<current->getY() - 1;
        //std::cout<<"\nTARGET: "<<targetX<<","<<targetY<<"\n\n";
        if(current->getX() == targetX && current->getY() - 1 == targetY){
            found = true;
            //std::cout<<"eccolo";
            break;
        }
        if(isWalkable(current->getX(), current->getY() - 1)){
            std::shared_ptr<Box> temp = std::make_shared<Box>(Box(current->getX(), current->getY() - 1, current->getG() + 1, getDistance(current->getX(), current->getY() - 1, targetX, targetY)));
            //Set previous box
            temp->setPreviousBox(current);
            //std::cout<<"\n\n"<<temp->getPreviousBox()->getX();
            
            checkBox(current, temp, openList, closedList, targetX, targetY);
        }
        //Lower square
        //Check if the target is in the open list
        //std::cout<<"\n\nCURRENT: "<<current->getX()<<"   "<<current->getY() + 1;
        //std::cout<<"\nTARGET: "<<targetX<<","<<targetY<<"\n\n";
        if(current->getX() == targetX && current->getY() + 1 == targetY){
            found = true;
            //std::cout<<"eccolo";
            break;
        }
        if(isWalkable(current->getX(), current->getY() + 1)){
            std::shared_ptr<Box> temp = std::make_shared<Box>(Box(current->getX(), current->getY() + 1, current->getG() + 1, getDistance(current->getX(), current->getY() + 1, targetX, targetY)));
            //Set previous box
            temp->setPreviousBox(current);
            //std::cout<<"\n\n"<<temp->getPreviousBox()->getX();
            //Check if the target is in the open list
            checkBox(current, temp, openList, closedList, targetX, targetY);
        }
        //Right square
        //Check if the target is in the open list
        //std::cout<<"\n\nCURRENT: "<<current->getX() + 1<<"   "<<current->getY();
        //std::cout<<"\nTARGET: "<<targetX<<","<<targetY<<"\n\n";
        if(current->getX() + 1 == targetX && current->getY() == targetY){
            found = true;
            //std::cout<<"eccolo";
            break;
        }
        if(isWalkable(current->getX() + 1, current->getY())){
            std::shared_ptr<Box> temp = std::make_shared<Box>(Box(current->getX() + 1, current->getY(), current->getG() + 1, getDistance(current->getX() + 1, current->getY(), targetX, targetY)));
            //Set previous box
            temp->setPreviousBox(current);
            //std::cout<<"\n\n"<<temp->getPreviousBox()->getX();
            //Check if the target is in the open list
            checkBox(current, temp, openList, closedList, targetX, targetY);
        }
        //Left square
        //Check if the target is in the open list
        //std::cout<<"\n\nCURRENT: "<<current->getX() - 1<<"   "<<current->getY();
        //std::cout<<"\nTARGET: "<<targetX<<","<<targetY<<"\n\n";
        if(current->getX() - 1 == targetX && current->getY() == targetY){
            found = true;
            //std::cout<<"eccolo";
            break;
        }
        if(isWalkable(current->getX() - 1, current->getY())){
            std::shared_ptr<Box> temp = std::make_shared<Box>(Box(current->getX() - 1, current->getY(), current->getG() + 1, getDistance(current->getX() - 1, current->getY(), targetX, targetY)));
            //Set previous box
            temp->setPreviousBox(current);
            //Check if the target is in the open list
            checkBox(current, temp, openList, closedList, targetX, targetY);
        }

        //Find the box with the lower F score
        std::vector<std::shared_ptr<Box>>::iterator it = openList.begin();
        std::vector<std::shared_ptr<Box>>::iterator end = openList.end();
        unsigned int minG = (**it).getG();
        unsigned int minH = (**it).getH();
        unsigned int minIndex = 0;
        for(it; it != end; it ++){
            //If the F score of the current element is lower...
            if((**it).getG() + (**it).getH() < minG + minH){
                minG = (**it).getG();
                minH = (**it).getH();
                minIndex = it - openList.begin();
            }else if((**it).getG() + (**it).getH() == minG + minH){
                if((**it).getH() < minH){
                    minG = (**it).getG();
                    minH = (**it).getH();
                    minIndex = it - openList.begin();
                }
            }
        }
        if(openList.size() == 0)
            break;
        //Add the box with the lower F score to the closed list
        closedList.push_back(std::make_shared<Box>(Box(openList.at(minIndex)->getX(), openList.at(minIndex)->getY(), openList.at(minIndex)->getG(), openList.at(minIndex)->getH())));
        closedList.back()->setPreviousBox(openList.at(minIndex)->getPreviousBox());
        //Set the current box
        current = closedList.back();
        //Remove the current box from the open list
        openList.erase(openList.begin() + minIndex);
    }

    //If the path has been found...
    if(found){
        //Iterate backwards to find where it started
        std::shared_ptr<Box> p = current->getPreviousBox();
        while(p->getPreviousBox()->getPreviousBox() != nullptr){
            p = p->getPreviousBox();
        }
        c.setCoordinates(p->getX(), p->getY());
    }else{
        //Else there is no path, the character won't move for now
        std::cout<<"\n\nNot found :(\n\n";
    }
}


//----------------------------------------------------------------------------------------------------

//BOX SECTION
Box::Box(unsigned int x, unsigned int y, unsigned int g, unsigned int h){
    this->x = x;
    this->y = y;
    this->g = g;
    this->h = h;
}

unsigned int Box::getX() const{return this->x;}
unsigned int Box::getY() const{return this->y;}
unsigned int Box::getG() const{return this->g;}
unsigned int Box::getH() const{return this->h;}
std::shared_ptr<Box> Box::getPreviousBox() const{return this->previousBox;}

void Box::setG(unsigned int g){this->g = g;}
void Box::setH(unsigned int h){this->h = h;}
void Box::setPreviousBox(std::shared_ptr<Box> pBox){this->previousBox = pBox;}