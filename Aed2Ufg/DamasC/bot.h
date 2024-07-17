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

    Move bestMove(gridType grid[][8], int turn);

    // Minimax algorithm function
    int minimax(gridType grid[][8], int depth, int maximizingPlayer);

    // Function to evaluate the board state
    int evaluate(gridType grid[][8]);

    void movePiece(gridType grid[][8], Positions from, Positions to);

#endif