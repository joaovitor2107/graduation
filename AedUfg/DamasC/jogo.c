
#include "jogo.h"
#include "bot.h"

    void initGame(SDL_Surface *screen){

        gridType grid[8][8];
        Positions destPositions;
        Positions fromPositions;
        Positions click;
        int gameover = 0;
        int turn = RED;
        int valid;
        gridType copyGrid[8][8];
        Move bestMove;
        
        initBoard(grid);

        while (!gameover) {
        
        printBoard(screen, grid);
        int movechoosed = 0;

            if(turn == WHITE){ //bot turn
                copy(copyGrid, grid);
                minimax(20, copyGrid, WHITE, &bestMove, INT16_MIN, INT16_MAX);
                fromPositions = bestMove.from;
                destPositions = bestMove.dest;
                
                if((bestMove.from.x - 2) == bestMove.dest.x || (bestMove.from.x + 2) == bestMove.dest.x || 
                (bestMove.from.y - 2 == bestMove.dest.y) || (bestMove.from.y + 2 == bestMove.dest.y)){
                    int tempX, tempY;

                    tempX = (bestMove.from.x + bestMove.dest.x)/2;
                    tempY = (bestMove.from.y + bestMove.dest.y)/2;

                    grid[tempX][tempY].state = EMPTY;
                    grid[tempX][tempY].color = UNDEFINED;
                    grid[tempX][tempY].king = FALSE;
                }
            }
            else{
                while (!movechoosed) {

                    click = getClick(screen);   

                    if ((click.x > 7) || (click.x < 0) || (click.y > 7) || (click.y < 0)) {
                        exit(0);
                    } else if (validFromPiece(turn, grid, click)) {
                        fromPositions = click;
                        printBoard(screen, grid);
                    }else if (validDestPiece(turn, grid, fromPositions, click)) {
                        destPositions = click;
                        movechoosed = 1;
                    } else if (takePiece(turn, grid, fromPositions, click) == WHITE_LEFT) {
                        destPositions = click;
                        grid[fromPositions.x + 1][fromPositions.y - 1].color = UNDEFINED;
                        grid[fromPositions.x + 1][fromPositions.y - 1].state = EMPTY;
                        movechoosed = 1;
                    } else if (takePiece(turn, grid, fromPositions, click) == WHITE_RIGHT) {
                        destPositions = click;
                        grid[fromPositions.x + 1][fromPositions.y + 1].color = UNDEFINED;
                        grid[fromPositions.x + 1][fromPositions.y + 1].state = EMPTY;
                        movechoosed = 1;
                    } else if (takePiece(turn, grid, fromPositions, click) == RED_LEFT) {
                        destPositions = click;
                        grid[fromPositions.x - 1][fromPositions.y - 1].color = UNDEFINED;
                        grid[fromPositions.x - 1][fromPositions.y - 1].state = EMPTY;
                        movechoosed = 1;
                    } else if (takePiece(turn, grid, fromPositions, click) == RED_RIGHT) {
                        destPositions = click;
                        grid[fromPositions.x - 1][fromPositions.y + 1].color = UNDEFINED;
                        grid[fromPositions.x - 1][fromPositions.y + 1].state = EMPTY;
                        movechoosed = 1;
                    }
                }
            }

        refreshBoard(turn, grid, fromPositions, destPositions);


        if (win(grid) == WHITE) {
            printf("THE WINNER IS THE WHITE PLAYER\n");
            gameover = 1;
        } else if (win(grid) == RED) {
            printf("THE WINNER IS THE RED PLAYER\n");
            gameover = 1;
        }

        turn = -turn;
    }

    exit(0);
}



    Positions getClick(SDL_Surface *screen){

        Positions mousePosition;
        SDL_Event event;
        int wait = 1;

        while(wait){

            SDL_Flip(screen);
            SDL_WaitEvent(&event);

            switch (event.type)
            {
                case SDL_QUIT:
                    wait = 0;
                    mousePosition.x = -1;
                    mousePosition.y = -1;
                    return mousePosition;


                case SDL_MOUSEBUTTONDOWN:
                    mousePosition.x = event.button.y;
                    mousePosition.y = event.button.x;


                    if((mousePosition.x / 100 < 8) && (mousePosition.y / 100 < 8)){
                        mousePosition.x = mousePosition.x/100;
                        mousePosition.y = mousePosition.y/100;
                        return mousePosition;
                    }    

                    break;
            
            }
        }
    }


    int validFromPiece(int turn, gridType grid[][8], Positions fromPositions){

        if(grid[fromPositions.x][fromPositions.y].state == FULL && grid[fromPositions.x][fromPositions.y].color == turn){
            return 1;
        }

        return 0;
    }
   

    int validDestPiece(int turn, gridType grid[][8], Positions from, Positions dest){

        if((turn == WHITE) && (grid[dest.x][dest.y].state == EMPTY) && (dest.x == from.x + 1) && (dest.y == from.y + 1)){
            return 1;
        }//direita
        else if((turn == WHITE) && (grid[dest.x][dest.y].state == EMPTY) && (dest.x == from.x + 1) && (dest.y == from.y - 1)){
            return 1;
        }//esquerda;
        else if((turn == WHITE) && (grid[dest.x][dest.y].state == EMPTY) && (grid[from.x][from.y].king == TRUE) && (dest.x == from.x - 1) && (dest.y == from.y + 1)){
            return 1;
        }//direita branco  pra tras rei 
        else if((turn == WHITE) && (grid[dest.x][dest.y].state == EMPTY) && (grid[from.x][from.y].king == TRUE) && (dest.x == from.x - 1) && (dest.y == from.y - 1)){
            return 1;
        }//esquerda branco pra tras rei 
        else if((turn == RED) && (grid[dest.x][dest.y].state == EMPTY) && (dest.x == from.x - 1) && (dest.y == from.y + 1)){
            return 1;
        }//direita
        else if((turn == RED) && (grid[dest.x][dest.y].state == EMPTY) && (dest.x == from.x - 1) && (dest.y == from.y - 1)){
            return 1;
        }//esquerda
        else if((turn == RED) && (grid[dest.x][dest.y].state == EMPTY) && (grid[from.x][from.y].king == TRUE) && (dest.x == from.x + 1) && (dest.y == from.y + 1)){
            return 1;
        }//direita vermelha pra tras rei
        else if((turn == RED) && (grid[dest.x][dest.y].state == EMPTY) && (grid[from.x][from.y].king == TRUE) && (dest.x == from.x + 1) && (dest.y == from.y - 1)){
            return 1;
        }//esquerda vermelha pra tras rei

        return 0;
    }


    void refreshBoard(int turn, gridType grid[][8], Positions from, Positions dest){
    grid[dest.x][dest.y].king = grid[from.x][from.y].king;
    
    grid[from.x][from.y].state = EMPTY;
    grid[from.x][from.y].color = UNDEFINED;
    grid[from.x][from.y].king = FALSE;

    grid[dest.x][dest.y].state = FULL;
    grid[dest.x][dest.y].color = turn;
  

    if ((grid[dest.x][dest.y].color == WHITE && dest.x == 7) || (grid[dest.x][dest.y].color == RED && dest.x == 0)) {
        grid[dest.x][dest.y].king = TRUE;
    }

    }


   int takePiece(int turn, gridType grid[][8], Positions from, Positions dest) {
        if (turn == WHITE) {
            if (dest.x == from.x + 2 && dest.y == from.y - 2) {
                if (from.y >= 2 && grid[from.x + 1][from.y - 1].color == RED && grid[from.x + 1][from.y - 1].state == FULL && grid[dest.x][dest.y].state == EMPTY) {
                    return WHITE_LEFT;
                }
            } else if (dest.x == from.x + 2 && dest.y == from.y + 2) {
                if (from.y <= 5 && grid[from.x + 1][from.y + 1].color == RED && grid[from.x + 1][from.y + 1].state == FULL && grid[dest.x][dest.y].state == EMPTY) {
                    return WHITE_RIGHT;
                }
            } else if (dest.x == from.x - 2 && dest.y == from.y - 2) {
                if (from.y >= 2 && grid[from.x - 1][from.y - 1].color == RED && grid[from.x - 1][from.y - 1].state == FULL && grid[dest.x][dest.y].state == EMPTY && grid[from.x][from.y].king == TRUE) {
                    return RED_LEFT;
                }
            } else if (dest.x == from.x - 2 && dest.y == from.y + 2) {
                if (from.y <= 5 && grid[from.x - 1][from.y + 1].color == RED && grid[from.x - 1][from.y + 1].state == FULL && grid[dest.x][dest.y].state == EMPTY && grid[from.x][from.y].king == TRUE) {
                    return RED_RIGHT;
                }
            }
        } else if (turn == RED) {
            if (dest.x == from.x - 2 && dest.y == from.y - 2) {
                if (from.y >= 2 && grid[from.x - 1][from.y - 1].color == WHITE && grid[from.x - 1][from.y - 1].state == FULL && grid[dest.x][dest.y].state == EMPTY) {
                    return RED_LEFT;
                }
            } else if (dest.x == from.x - 2 && dest.y == from.y + 2) {
                if (from.y <= 5 && grid[from.x - 1][from.y + 1].color == WHITE && grid[from.x - 1][from.y + 1].state == FULL && grid[dest.x][dest.y].state == EMPTY) {
                    return RED_RIGHT;
                }
            } else if (dest.x == from.x + 2 && dest.y == from.y - 2) {
                if (from.y >= 2 && grid[from.x + 1][from.y - 1].color == WHITE && grid[from.x + 1][from.y - 1].state == FULL && grid[dest.x][dest.y].state == EMPTY && grid[from.x][from.y].king == TRUE) {
                    return WHITE_LEFT;
                }
            } else if (dest.x == from.x + 2 && dest.y == from.y + 2) {
                if (from.y <= 5 && grid[from.x + 1][from.y + 1].color == WHITE && grid[from.x + 1][from.y + 1].state == FULL && grid[dest.x][dest.y].state == EMPTY && grid[from.x][from.y].king == TRUE) {
                    return WHITE_RIGHT;
                }
            }
        }   
        return 0;
    }



    int win(gridType grid[][8]){
        int redPieces = 0, whitePieces = 0;

        for(int i = 0; i < SQUARE_NUMBERS; i++){
            for(int j = 0; j < SQUARE_NUMBERS;j++){

                if(grid[i][j].color == RED){
                    redPieces++;
                }
                else if(grid[i][j].color == WHITE){
                    whitePieces++;
                }

            }
        }

        if(redPieces == 0){
            return WHITE;
        }
        else if(whitePieces == 0){
            return RED;
        }

        return 0;

    }