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
    while(gameState == 0){
        do{
            //system("cls");
            //Clear the fog around the player
            game.clearFog();
            std::cout<<"\nX:"<<game.getPlayer()->getX()<<" Y:"<<game.getPlayer()->getY()<<"\n\n";
            game.printInterface();
            cout<<endl<<"What would you like to do?\nW = move north\nS = move south\nA = move ovest\nD = move east\nEquip objectIndex = equip an object, a weapon or an armor";
            cout<<endl<<"Atk w/a/s/d = attack in the chosen direction\nUse w/a/s/d = use the equipped object in the chosen direction\nCast spellIndex w/a/s/d = cast the spell at the index spellIndex";
            cout<<endl<<"Open w/a/s/d = open the door in the chosen direction\nTake = loot the surrounding items\nDiscard objectIndex = discard the object at the index objectIndex";
            cout<<endl<<"Identify objectIndex = show the description of the object at the index objectIndex\n";
            try{
                getline(std::cin, choice);
            }catch(int a){
                std::cout<<"\nThe input is not valid\n";
            }
            std::cout<<"1";
            actionType = game.getPlayer()->input(choice);
            std::cout<<"2";
            //If the user inserted a valid action
            if(actionType != 0){
                error = 0;
                switch (actionType){
                    case 1: 
                        //Player movement
                        std::cout<<"3";
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
                        std::cout<<"4";
                        //If Player completed an action without errors...
                        if(error == 0){ 
                            //Make the time pass
                            game.lapsedTime += game.getPlayer()->getMovTime();
                            //Enemies do actions
                            game.moveEnemies();
                        }
                        game.getPlayer()->resetMovementIntention();
                        std::cout<<"5";
                        break;
                    case 2:
                        //Equip item
                        if(!game.getPlayer()->equipItem((choice[6]) - '0'))
                            error = 2;
                        else 
                            game.lapsedTime += game.getPlayer()->getActTime();
                        break;
                    case 3:
                        //Attack
                        //"Ask" the Player object the index of his weapon and its damage
                        std::cout<<"\n"<<game.getPlayer()->getEquippedWeaponAOE().back().getPot()<<"\n";
                        //Check the effects/areas of effect to find the hitted enemies

                        //Do playerDamage - enemyRes
                        if(areStringsEqual("w", std::string(1, choice[4]))){
                            //Atk up
                        }else if(areStringsEqual("a", std::string(1, choice[4]))){
                            //Atk down
                        }else if(areStringsEqual("s", std::string(1, choice[4]))){
                            //Atk left
                        }else{
                            //Atk right

                        }
                        break;
                    default:
                        break;
                }
                
            }else{
                std::cout<<"\nThe input is not valid, press enter to retry\n";
                fflush(stdin);
                cin.ignore();
            }
            if(error == 1){
                std::cout<<"You can't move in this direction. Press enter to retry";
            }else if(error == 2){
                std::cout<<"\nThe index is not valid. Press enter to retry";
            }
        }while(actionType == 0 || error != 0);
        
    }

    //Free pointers
    //delete game.getPlayer();
    
    return 0;
}