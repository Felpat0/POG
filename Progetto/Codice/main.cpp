#include "Lib/MapElements.h"


unsigned int gameState;
using namespace std;
int main(){
    srand(time(NULL));
    Game game = Game();
    for(int counter = 0; counter != ROOMS_NUMBER; counter ++)
        game.addRoom();

    game.linkRooms();
    game.spawnPlayer("warrior");
    game.spawnEnemy("goblin");
    game.spawnEnemy("goblin");

    //Game loop
    gameState = 0; //1=lose, 2=win
    int error = 0;
    string choice;
    unsigned int actionType;
    while(gameState == 0){
        do{
            system("cls");
            game.printBoard();
            cout<<endl<<"What would you like to do?\nW = move north\nS = move south\nA = move ovest\nD = move east\nEquip objectIndex = equip an object, a weapon or an armor";
            cout<<endl<<"Atk w/a/s/d = attack in the chosen direction\nUse w/a/s/d = use the equipped object in the chosen direction\nCast spellIndex w/a/s/d = cast the spell at the index spellIndex";
            cout<<endl<<"Open w/a/s/d = open the door in the chosen direction\nTake = loot the surrounding items\nDiscard objectIndex = discard the object at the index objectIndex";
            cout<<endl<<"Identify objectIndex = show the description of the object at the index objectIndex\n";
            cin>>choice;
            actionType = game.player->input(choice);

            //If the user inserted a valid action
            if(actionType != 0){
                error = 0;
                
                switch (actionType){
                    case 1: //Player movement
                        switch (game.player->getMovementIntention()){
                            case 1: //Up
                                if(game.isWalkable(game.player->getX(), game.player->getY() - 1))
                                    game.player->setCoordinates(game.player->getX(), game.player->getY() - 1);
                                else
                                    error = 1;
                                break;
                            case 2: //Down
                                if(game.isWalkable(game.player->getX(), game.player->getY() + 1))
                                    game.player->setCoordinates(game.player->getX(), game.player->getY() + 1);
                                else
                                    error = 1;
                                break;
                            case 3: //Left
                                if(game.isWalkable(game.player->getX() - 1, game.player->getY()))
                                    game.player->setCoordinates(game.player->getX() - 1, game.player->getY());
                                else
                                    error = 1;
                                break;
                            case 4: //Right
                                if(game.isWalkable(game.player->getX() + 1, game.player->getY())){
                                    game.player->setCoordinates(game.player->getX() + 1, game.player->getY());
                                }else
                                    error = 1;
                                break;
                        }

                        //If Player completed an action without errors...
                        if(error == 0){ 
                            //Make the time pass
                            game.lapsedTime += (static_cast<Character>(*(game.player))).movTime;
                            //Enemies do actions
                            game.moveEnemies();
                        }
                        game.player->resetMovementIntention();
                        break;
                    
                    default:
                        break;
                }
                
            }
        }while(actionType == 0 || error != 0);
        
    }

    //Free pointers
    delete game.player;
    return 0;
}