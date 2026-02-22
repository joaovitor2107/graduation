#ifndef Bot
#define Bot

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <ctype.h>
    #include <limits.h>

    #include "tabuleiro.h"
    #include "jogo.h"
    #include "constantes.h"

    //function to copy the original grid in an aux grid
    void copy(gridType copyGrid[][8], gridType originalGrid[][8]);

    //function to show all possible moves
    int possibleMoves(gridType grid[][8], Move moves[], int player);

    // Minimax algorithm function
    int minimax(int depth, gridType grid[][8], int player, Move *bestMove, int alpha, int beta);

    // Function to evaluate the board state 
    int evaluate(gridType grid[][8]);

    //function to make the move
    void makeMove(gridType grid[][8], Move *move);    

#endif