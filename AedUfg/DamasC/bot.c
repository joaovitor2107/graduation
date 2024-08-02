#include "bot.h"
#include "jogo.h"

void copy(gridType copyGrid[][8],gridType originalGrid[][8]){
    
    for(int i = 0;i < SQUARE_NUMBERS;i++){
        for(int j = 0; j < SQUARE_NUMBERS; j++){
            copyGrid[i][j].color = originalGrid[i][j].color;
            copyGrid[i][j].king = originalGrid[i][j].king;
            copyGrid[i][j].state = originalGrid[i][j].state;
        }
    }

}

int evaluate(gridType grid[][8]){
    int red_pieces = 0;
    int white_pieces = 0;

    for(int i = 0;i < SQUARE_NUMBERS;i++){
        for(int j = 0; j < SQUARE_NUMBERS; j++){
            if(grid[i][j].color == RED){
                red_pieces++;
                if(grid[i][j].king == TRUE){
                    red_pieces += 0.5;
                }
            }
            else if(grid[i][j].color == WHITE){
                white_pieces++;
                if(grid[i][j].king == TRUE){
                    white_pieces += 0.5;
                }
            }
        }
    }

    return white_pieces - red_pieces;
}

int possibleMoves(gridType grid[][8], Move moves[], int player){

    Positions from;
    Positions dest;
    int index = 0;

    for(int i = 0;i < SQUARE_NUMBERS;i++){
        for(int j = 0; j < SQUARE_NUMBERS; j++){

            if(grid[i][j].state == FULL && grid[i][j].color == player){
                
                from.x = i; 
                from.y = j;

                dest.x = from.x + 1;
                dest.y = from.y + 1;
                if ((dest.x <= 7) && (dest.x >= 0) && (dest.y <= 7) && (dest.y >= 0)) {
                    if (validDestPiece(player, grid, from, dest)) {
                        moves[index].from.x = from.x;
                        moves[index].from.y = from.y;
                        moves[index].dest.x = dest.x;
                        moves[index].dest.y = dest.y;
                        index++;
                    }
                }

                dest.x = from.x + 1;
                dest.y = from.y - 1;
                if ((dest.x <= 7) && (dest.x >= 0) && (dest.y <= 7) && (dest.y >= 0)) {
                    if (validDestPiece(player, grid, from, dest)) {
                        moves[index].from.x = from.x;
                        moves[index].from.y = from.y;
                        moves[index].dest.x = dest.x;
                        moves[index].dest.y = dest.y;
                        index++;
                    }
                }

                dest.x = from.x - 1;
                dest.y = from.y + 1;
                if ((dest.x <= 7) && (dest.x >= 0) && (dest.y <= 7) && (dest.y >= 0)) {
                    if (validDestPiece(player, grid, from, dest)) {
                        moves[index].from.x = from.x;
                        moves[index].from.y = from.y;
                        moves[index].dest.x = dest.x;
                        moves[index].dest.y = dest.y;
                        index++;
                    }
                }

                dest.x = from.x - 1;
                dest.y = from.y - 1;
                if ((dest.x <= 7) && (dest.x >= 0) && (dest.y <= 7) && (dest.y >= 0)) {
                    if (validDestPiece(player, grid, from, dest)) {
                        moves[index].from.x = from.x;
                        moves[index].from.y = from.y;
                        moves[index].dest.x = dest.x;
                        moves[index].dest.y = dest.y;
                        index++;
                    }
                }

                dest.x = from.x - 2;
                dest.y = from.y - 2;
                if ((dest.x <= 7) && (dest.x >= 0) && (dest.y <= 7) && (dest.y >= 0)) {
                    if (takePiece(player, grid, from, dest) != 0) {
                        moves[index].from.x = from.x;
                        moves[index].from.y = from.y;
                        moves[index].dest.x = dest.x;
                        moves[index].dest.y = dest.y;
                        index++;
                    }
                }

                dest.x = from.x + 2;
                dest.y = from.y - 2;
                if ((dest.x <= 7) && (dest.x >= 0) && (dest.y <= 7) && (dest.y >= 0)) {
                    if (takePiece(player, grid, from, dest) != 0) {
                        moves[index].from.x = from.x;
                        moves[index].from.y = from.y;
                        moves[index].dest.x = dest.x;
                        moves[index].dest.y = dest.y;
                        index++;
                    }
                }

                dest.x = from.x - 2;
                dest.y = from.y + 2;
                if ((dest.x <= 7) && (dest.x >= 0) && (dest.y <= 7) && (dest.y >= 0)) {
                    if (takePiece(player, grid, from, dest) != 0) {
                        moves[index].from.x = from.x;
                        moves[index].from.y = from.y;
                        moves[index].dest.x = dest.x;
                        moves[index].dest.y = dest.y;
                        index++;
                    }
                }

                dest.x = from.x + 2;
                dest.y = from.y + 2;
                if ((dest.x <= 7) && (dest.x >= 0) && (dest.y <= 7) && (dest.y >= 0)) {
                    if (takePiece(player, grid, from, dest) != 0) {
                        moves[index].from.x = from.x;
                        moves[index].from.y = from.y;
                        moves[index].dest.x = dest.x;
                        moves[index].dest.y = dest.y;
                        index++;
                    }
                }

            }      

        }
    }

    return index;
}

void makeMove(gridType grid[][8] ,Move *move){

    grid[move->dest.x][move->dest.y].king = grid[move->from.x][move->from.y].king;
    int aux = grid[move->from.x][move->from.y].color;

    grid[move->from.x][move->from.y].state = EMPTY;
    grid[move->from.x][move->from.y].color = UNDEFINED;
    grid[move->from.x][move->from.y].king = FALSE;

    grid[move->dest.x][move->dest.y].state = FULL;
    grid[move->dest.x][move->dest.y].color = aux;

    if ((grid[move->dest.x][move->dest.y].color == WHITE && move->dest.x == 7) ||
     (grid[move->dest.x][move->dest.y].color == RED && move->dest.x == 0)){
        grid[move->dest.x][move->dest.y].king = TRUE;
    }

    if((move->from.x - 2) == move->dest.x || (move->from.x + 2) == move->dest.x ||
     (move->from.y - 2 == move->dest.y) || (move->from.y + 2 == move->dest.y)){
            int tempX, tempY;

            tempX = (move->from.x + move->dest.x)/2;
            tempY = (move->from.y + move->dest.y)/2;

            grid[tempX][tempY].state = EMPTY;
            grid[tempX][tempY].color = UNDEFINED;
            grid[tempX][tempY].king = FALSE;
        }       

}


int minimax(int depth, gridType grid[][8], int player, Move *bestMove){ 

    int result = evaluate(grid);
    if(depth <= 0){
        return result;
    }

    Move moves[96]; //suposing all pieces are kings and all pieces have all the moves possible 
    int num_moves = possibleMoves(grid, moves, player);
    if(num_moves == 0){
        return result;
    }

    int value;
    
    if(player == WHITE){
        int maxEval = INT16_MIN; 
        for(int i = 0; i < num_moves; i++){

            gridType auxGrid[8][8];
            copy(auxGrid, grid);

            makeMove(auxGrid, &moves[i]);

            value = minimax(depth - 1, auxGrid, RED, NULL);

            if(value > maxEval){
                maxEval = value;
                if(bestMove != NULL){
                    *bestMove = moves[i];                    
                }
            }
            

        }

        return maxEval;
    }
    else{ 
        int minEval = INT16_MAX;
        for (int i = 0; i < num_moves; i++){
            
            gridType auxGrid[8][8];
            copy(auxGrid, grid);

            makeMove(auxGrid, &moves[i]);

            int value = minimax(depth - 1, auxGrid, WHITE, NULL);

            if (value < minEval) {
                minEval = value;
                if (bestMove != NULL) {
                    *bestMove = moves[i];
                }
            }
        }
        return minEval;

    }

}