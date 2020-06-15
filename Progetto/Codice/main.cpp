#include "MapElements.h"

int main(){
    srand(time(NULL));
    Game a = Game();
    for(int counter = 0; counter != 4; counter ++)
        a.addRoom();
    /*
    for(int i=0;i<256;i++){
        if(!(i%8))
            printf("\n");
        printf("%c (%03d)",i,i);
    }
    */
    //a.createPath(*(a.rooms[0]), *(a.rooms[1]));
    a.linkRooms();
    a.printBoard();
    return 0;
}