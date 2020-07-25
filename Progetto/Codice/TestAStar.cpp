#include "Lib/MapElements.h"
#include <Windows.h>

int m[10][10];


void printUnicode(std::string character, unsigned int color){
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
unsigned int getDistance(Character& a, Character& b){
    return (abs((int)(a.getX() - b.getX())) + abs(((int)(a.getY() - b.getY()))));
}

unsigned int getDistance(int x1, int y1, int x2, int y2){
    return (abs(x1 - x2) + abs(y1 - y2));
}
bool isWalkable(int x, int y){
    if(m[y][x] > 0)
        return false;
    return true;
}
void checkBox(Box current, Box temp, std::vector<std::shared_ptr<Box>>& openList, std::vector<std::shared_ptr<Box>>& closedList, unsigned int targetX, unsigned int targetY){
            
    //Check if temp is in the closedList
    bool closed = false;
    std::vector<std::shared_ptr<Box>>::iterator it = closedList.begin();
    std::vector<std::shared_ptr<Box>>::iterator end = closedList.end();
    for(it; it != end; it ++){
        //If the square is in the closedList...
        if((**it).getX() == temp.getX() && (**it).getY() == temp.getY()){
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
            if((**it).getX() == temp.getX() && (**it).getY() == temp.getY()){
                open = true;
                unsigned int newGScore = current.getG() + 1;
                unsigned int newHScore = getDistance(temp.getX(), temp.getY(), targetX, targetY);
                if(newGScore + newHScore < (**it).getG() + (**it).getH()){
                    (**it).setG(newGScore);
                    (**it).setH(newHScore);
                    std::shared_ptr<Box> t = (current.getPreviousBox());
                    (**it).setPreviousBox(*t);
                }
            }
        }
        if(!open){
            openList.push_back(std::make_shared<Box>(temp));
        }
    }
}

void walkShortestPath(Character& c, unsigned int targetX, unsigned int targetY){
    /*NOTE:
    Se due square hanno lo stesso F, prendere quello con H minore.
    se hanno la stessa H continuare semplicemente sull'attuale percorso
    Se entrambi sono sul percorso, prenderne uno random
    */
   std::cout<<"\n\nTARGET: "<<targetY<<","<<targetX<<"\n\n";

    bool found = false;
    //Create open list
    std::vector<std::shared_ptr<Box>> openList;
    //Create closed list
    std::vector<std::shared_ptr<Box>> closedList;
    //Set the current square
    Box current = Box(c.getX(), c.getY(), 0, 0);
    unsigned int counter = 0;
    while(true){
        //TEMP INIZIO
        for (int i = 0; i != 10; i++) {
            for (int j = 0; j != 10; j++) {
                    //Check if Player is in this position
                    if(targetY == i && targetX == j)
                        printUnicode("0x0050", 1);
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
            std::cout<<std::endl;
        }

        //TEMP FINE
        counter ++;
        //Add the walkable squares to the open list if necessary
        //Upper square
        //Check if the target is in the open list
        if(current.getX() == targetX && current.getY() - 1 == targetY){
            found = true;
            break;
        }
        if(isWalkable(current.getX(), current.getY() - 1)){
            Box temp = Box(current.getX(), current.getY() - 1, current.getG() + 1, getDistance(current.getX(), current.getY() - 1, targetX, targetY));
            //Set previous box
            if(counter > 1)
                temp.setPreviousBox(current);
            std::cout<<"\n\nCORRENTE: "<<temp.getX()<<","<<temp.getY();
            std::cout<<"\nPLAYER  : "<<targetX<<","<<targetY<<"\n\n";
            
            checkBox(current, temp, openList, closedList, targetX, targetY);
            std::cout<<"\n\n\nBox 1: "<<openList.size();
        }
        //Lower square
        //Check if the target is in the open list
        if(current.getX() == targetX && current.getY() + 1 == targetY){
            found = true;
            break;
        }
        if(isWalkable(current.getX(), current.getY() + 1)){
            Box temp = Box(current.getX(), current.getY() + 1, current.getG() + 1, getDistance(current.getX(), current.getY() + 1, targetX, targetY));
            //Set previous box
            if(counter > 1)
                temp.setPreviousBox(current);
            //Check if the target is in the open list
            std::cout<<"\n\nCORRENTE: "<<temp.getX()<<","<<temp.getY();
            std::cout<<"\nPLAYER  : "<<targetX<<","<<targetY<<"\n\n";
            checkBox(current, temp, openList, closedList, targetX, targetY);
            std::cout<<"\n\n\nBox 2: "<<openList.size();
        }
        //Right square
        //Check if the target is in the open list
        if(current.getX() == targetX + 1 && current.getY() == targetY){
            found = true;
            break;
        }
        if(isWalkable(current.getX() + 1, current.getY())){
            Box temp = Box(current.getX() + 1, current.getY(), current.getG() + 1, getDistance(current.getX(), current.getY() - 1, targetX, targetY));
            //Set previous box
            if(counter > 1)
                temp.setPreviousBox(current);
            //Check if the target is in the open list
            std::cout<<"\n\nCORRENTE: "<<temp.getX()<<","<<temp.getY();
            std::cout<<"\nPLAYER  : "<<targetX<<","<<targetY<<"\n\n";
            checkBox(current, temp, openList, closedList, targetX, targetY);
            std::cout<<"\n\n\nBox 3: "<<openList.size();
        }
        //Left square
        //Check if the target is in the open list
        if(current.getX() - 1 == targetX && current.getY() == targetY){
            found = true;
            break;
        }
        if(isWalkable(current.getX() - 1, current.getY())){
            Box temp = Box(current.getX() - 1, current.getY(), current.getG() + 1, getDistance(current.getX(), current.getY() - 1, targetX, targetY));
            //Set previous box
            if(counter > 1)
                temp.setPreviousBox(current);
            //Check if the target is in the open list
            std::cout<<"\n\nCORRENTE: "<<temp.getX()<<","<<temp.getY();
            std::cout<<"\nPLAYER  : "<<targetX<<","<<targetY<<"\n\n";
            checkBox(current, temp, openList, closedList, targetX, targetY);
            std::cout<<"\n\n\nBox 4: "<<openList.size();
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
        std::cout<<"CHECK 0";
        if(openList.size() == 0)
            break;
        std::cout<<"CHECK 1";
        //Add the box with the lower F score to the closed list
        closedList.push_back(std::make_shared<Box>(Box(openList.at(minIndex)->getX(), openList.at(minIndex)->getY(), openList.at(minIndex)->getG(), openList.at(minIndex)->getH())));
        std::cout<<"CHECK 2";
        //Set the current box
        current = *closedList.back();
        std::cout<<"CHECK 3";
        //Remove the current box from the open list
        openList.erase(openList.begin() + minIndex);
    }

    //If the path has been found...
    if(found){
        //Iterate backwards to find where it started
        std::shared_ptr<Box> p = current.getPreviousBox();
        while(p->getPreviousBox() != nullptr){
            p = p->getPreviousBox();
        }
        c.setCoordinates(p->getX(), p->getY());
    }else{
        std::cout<<"\n\nNot found :(  "<<counter<<"\n\n";
    }
    //Else there is no path, the character won't move for now
}



int main(){
    for (int i = 0; i != 10; i++) {
        for (int j = 0; j != 10; j++) {
            m[i][j] = 0;
        }
    }
    Character temp = Character(0,0,0,0,0,0,0,0,0,0,"");
    walkShortestPath(temp, 5, 5);
    return 0;
}