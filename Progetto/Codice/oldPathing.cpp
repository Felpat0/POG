int door1Position[] = {room1.x, room1.y};
    int door2Position[] = {room2.x, room2.y};
    int actualPosition[] = {door1Position[0], door1Position[1]};
    int tempPosition[2];
    int nextMove;

    bool moves[] = {false, false, false, false}; //Left, right, up, down
    //Check where can move
    //Move
    //Check if arrived
    //repeat

    /*while(true){
        bool ok = true;
        int modifier = 1;
        if(actualPosition[0] == door2Position[0]){
            if(door2Position[1] < actualPosition[1])
                modifier = -1;
            for(int i = actualPosition[1] + modifier; i != (door2Position[1]); i += modifier){
                if(m[i][actualPosition[0]] != ' '){
                    ok = false;
                    break;
                }
            }
            if(ok){
                for(int i = actualPosition[1] + modifier; i != (door2Position[1]); i += modifier)
                    m[i][actualPosition[0]] = 'H';
                break;
            }
        }else if(actualPosition[1] == door2Position[1]){
            if(door2Position[0] < actualPosition[0])
                modifier = -1;
            for(int i = actualPosition[0] + modifier; i != (door2Position[0]); i += modifier){
                if(m[actualPosition[1]][i] != ' '){
                    ok = false;
                    break;
                }
            }
            if(ok){
                for(int i = actualPosition[0] + modifier; i != (door2Position[0]); i += modifier)
                    m[actualPosition[1]][i] = 'H';
                break;
            }
        }
            //check left
            tempPosition[0] = actualPosition[0] - 1;
            tempPosition[1] = actualPosition[1];
            if(m[tempPosition[1]][tempPosition[0]] == ' ' && tempPosition[0] > -1){
                //check left, up and down
                if((m[tempPosition[1]][tempPosition[0] -1] != 'H') &&
                (m[tempPosition[1] - 1][tempPosition[0]] != 'H') &&
                (m[tempPosition[1] + 1][tempPosition[0]] != 'H'))
                    moves[0] = true;
            }
            //check right
            tempPosition[0] = actualPosition[0] + 1;
            tempPosition[1] = actualPosition[1];
            if(m[tempPosition[1]][tempPosition[0]] == ' ' && tempPosition[0] <= MAX_MATRIX_WIDTH){
                //Check right, up and down
                if((m[tempPosition[1]][tempPosition[0] +1] != 'H') &&
                (m[tempPosition[1] - 1][tempPosition[0]] != 'H') &&
                (m[tempPosition[1] + 1][tempPosition[0]] != 'H'))
                    moves[1] = true;
            }
            //check up
            tempPosition[0] = actualPosition[0];
            tempPosition[1] = actualPosition[1] -1;
            if(m[tempPosition[1]][tempPosition[0]] == ' ' && tempPosition[1]> -1){
                //Check left, right and up
                if((m[tempPosition[1]][tempPosition[0] -1] != 'H') &&
                (m[tempPosition[1]][tempPosition[0] +1] != 'H') &&
                (m[tempPosition[1] - 1][tempPosition[0]] != 'H'))
                    moves[2] = true;
            }
            //check down
            tempPosition[0] = actualPosition[0];
            tempPosition[1] = actualPosition[1] +1;
            if(m[tempPosition[1]][tempPosition[0]] == ' ' && tempPosition[1] <= MAX_MATRIX_HEIGHT){
                //Check left, right and down
                //std::cout<<"im in";
                if((m[tempPosition[1]][tempPosition[0] -1] != 'H') &&
                (m[tempPosition[1]][tempPosition[0] +1] != 'H') &&
                (m[tempPosition[1] + 1][tempPosition[0]] != 'H')){
                    moves[3] = true;
                    //std::cout<<"im supah in";
                }
            }
            //try to move
            //Si può semplificare l'algoritmo togliendo tutti i check di 
            //prima e provando direttamente a fare il random, per poi controllare se ci si
            //può muovere in quella posizione
            nextMove = rand() % 4;
            while(!moves[nextMove])
                nextMove = rand() % 4;
            switch (nextMove)
            {
                case 0:
                    actualPosition[0] --;
                    break;
                case 1:
                    actualPosition[0] ++;
                    break;
                case 2:
                    actualPosition[1] --;
                    break;
                case 3:
                    actualPosition[1] ++;
                    break;
                default:
                    break;
            }
            bool check = false;
            //reset moves
            for(int i = 0; i != 4; i++){
                if(moves[i] == true){
                    check = true;
                }
                moves[i] = false;
            }
            if(!check){ //fare il reset delle H altrimenti non può ricominciare
                actualPosition[0] = door1Position[0];
                actualPosition[1] = door1Position[1];
            }else
                m[actualPosition[1]][actualPosition[0]] = 'H';
            //printf("\n");
            //printBoard();
            //check if reached door
            if(actualPosition[0] - 1 == room2.door->x && actualPosition[1] == room2.door->y)
                break;
            if(actualPosition[0] + 1 == room2.door->x && actualPosition[1] == room2.door->y)
                break;
            if(actualPosition[0] == room2.door->x && actualPosition[1] == room2.door->y - 1)
                break;
            if(actualPosition[0] == room2.door->x && actualPosition[1] == room2.door->y + 1)
                break;
            if(!check){
                actualPosition[0] = door1Position[0];
                actualPosition[1] = door1Position[1];
            }
        }
    */
    //printBoard();
    //printf("daje");
    return true;