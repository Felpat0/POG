#include "Lib/MapElements.h"
#include <Windows.h>


unsigned int gameState;
using namespace std;
int main(){
    SetConsoleOutputCP(65001);
    srand(time(NULL));
    Game game = Game();
    game.getBestiary();
    game.getItems();
    int a = 0;
    while(a != 1 && a != 2){
        cout<<"1.Generate map\n2.Import map and play\n";
        cin>>a;
        if(a != 1 && a != 2)
            std::cout<<"\nInsert a valid input\n";
    }
    if(a == 1){
        game.generateMap();
        return 0;
    }else if(a == 2){
        game.initMap();
        game.linkRoomsByDoors();
        game.chooseClass();
    }


    //Game loop
    gameState = 0; //1=lost, 2=won
    int error = 0;
    string choice;
    unsigned int actionType;
    //system("cls");
    while(gameState == 0){
        do{
            //Clear the fog around the player
            game.clearFog();
            std::cout<<"\nI:"<<game.getPlayer()->getY()<<" J:"<<game.getPlayer()->getX()<<"\n\n";
            game.printInterface();
            try{
                getline(std::cin, choice);
            }catch(int a){
                std::cout<<"\nThe input is not valid\n";
            }
            //system("cls");
            actionType = game.getPlayer()->input(choice);
            //If the user inserted a valid action
            if(actionType != 0){
                error = 0;
                switch (actionType){
                    case 1: 
                        //Player movement
                        switch (game.getPlayer()->getMovementIntention()){
                            case 1: //Up
                                if(game.isWalkable(game.getPlayer()->getX(), game.getPlayer()->getY() - 1))
                                    game.getPlayer()->setCoordinates(game.getPlayer()->getX(), game.getPlayer()->getY() - 1);
                                else
                                    error = 1;
                                break;
                            case 2: //Down
                                if(game.isWalkable(game.getPlayer()->getX(), game.getPlayer()->getY() + 1))
                                    game.getPlayer()->setCoordinates(game.getPlayer()->getX(), game.getPlayer()->getY() + 1);
                                else
                                    error = 1;
                                break;
                            case 3: //Left
                                if(game.isWalkable(game.getPlayer()->getX() - 1, game.getPlayer()->getY()))
                                    game.getPlayer()->setCoordinates(game.getPlayer()->getX() - 1, game.getPlayer()->getY());
                                else
                                    error = 1;
                                break;
                            case 4: //Right
                                if(game.isWalkable(game.getPlayer()->getX() + 1, game.getPlayer()->getY())){
                                    game.getPlayer()->setCoordinates(game.getPlayer()->getX() + 1, game.getPlayer()->getY());
                                }else
                                    error = 1;
                                break;
                        }
                        if(error == 0)
                            game.lapsedTime += game.getPlayer()->getMovTime();
                        game.getPlayer()->resetMovementIntention();
                        break;
                    case 2:
                        //Equip item
                        if(game.getPlayer()->equipItem((choice[6]) - '0'))
                            game.lapsedTime += game.getPlayer()->getActTime();
                        break;
                    case 3:
                        //Attack
                        game.playerAttack(choice[4]); //Even if player hits none, time passes
                        game.lapsedTime += game.getPlayer()->getActTime();
                        break;
                    case 4:
                        //Cast spell
                        if(game.playerCastSpell(choice[7], choice[5] - '0'))
                            game.lapsedTime += game.getPlayer()->getActTime();
                        break;
                    case 5:
                        //Use item
                        if(game.playerUse(choice[4] - '0'))
                            game.lapsedTime += game.getPlayer()->getActTime();
                       break;
                    case 6:
                        //Loot items
                        if(game.getPlayer()->getInventorySize() == 10){
                            std::cout<<"\nYour inventory is full, you can't loot more items.";
                            std::cin.ignore();
                        }else{
                            game.playerLoot();
                            game.lapsedTime += game.getPlayer()->getActTime();
                        }
                        break;
                    case 7:
                        //Discard item
                        if(game.getPlayer()->discardItem(choice[8] - '0'))
                            game.lapsedTime += game.getPlayer()->getActTime();
                        break;
                    case 8:
                        //Identify item
                        if(game.getPlayer()->identifyItem(choice[9] - '0'))
                            game.lapsedTime += game.getPlayer()->getActTime();
                        break;
                    case 9:
                        //Open door/chest
                        if(game.playerOpen(choice[5]))
                            game.lapsedTime += game.getPlayer()->getActTime();
                        break;
                    default:
                        break;
                }
                
            }else{
                std::cout<<"\nThe input is not valid. Press enter to retry.\n";
                fflush(stdin);
                cin.ignore();
            }
            if(error == 1){
                std::cout<<"\nYou can't move in this direction. Press enter to retry.\n";
                fflush(stdin);
                cin.ignore();
            }else if(error == 2){
                std::cout<<"\nThe index is not valid. Press enter to retry.\n";
                fflush(stdin);
                cin.ignore();
            }else if(error == 3){
                std::cout<<"\nThe chosen item is not equipped. Press enter to continue.\n";
                fflush(stdin);
                cin.ignore();
            }else if(error == 4){
                std::cout<<"\nThe chosen item has not been identified yet. Press enter to continue.\n";
                fflush(stdin);
                cin.ignore();
            }
        }while(actionType == 0 || error != 0);
        //Check if player died because of an ability check
        if(game.getPlayer()->getHP() == 0){
            gameState = 1;
            break;
        }
        //Move enemies
        if(game.getPlayer()->getX() == game.getExitX() &&  game.getPlayer()->getY() == game.getExitY()){
            gameState = 2;
            break;
        }
        game.moveEnemies();
        //Check if the player died after the enemy moves
        if(game.getPlayer()->getHP() == 0){
            gameState = 1;
            break;
        }
    }

    if(gameState == 2){
        system("cls");
        int score = 0;
        for(int i = 1; i != game.getPlayer()->getLvl(); i++){
            score += 100 * i;
        }
        score += 25 * game.getPlayer()->getGp() + game.getPlayer()->getExp();
        std::cout<<"\n\n\n                         \\(*-*)/ Congratulations! You won with a score of "<<score<<" \\(*-*)/\n\n\n";
    }else{
        game.printInterface();
        fflush(stdin);
        cin.ignore();
        system("cls");
        std::cout<<"\n\n\n                          /(-.-)\\ You lost... Better luck next time! /(-.-)\\\n\n\n";
    }
    //Free pointers
    delete game.getPlayer();
    
    return 0;
}