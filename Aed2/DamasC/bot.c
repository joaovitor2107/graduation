#include "bot.h"



Move bestMove(gridType grid[][8], int turn) {
    int bestValue = -10000;
    Positions bestMoveFrom, bestMoveTo;

    // Loop through all white pieces and evaluate moves
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j].color == WHITE) {
                // Evaluate possible moves for this piece
                for (int di = -2; di <= 2; di += 2) {
                    for (int dj = -2; dj <= 2; dj += 2) {
                        int newX = i + di;
                        int newY = j + dj;
                        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                            if (validDestPiece(WHITE, grid, (Positions){i, j}, (Positions){newX, newY}) || takePiece(WHITE, grid, (Positions){i, j}, (Positions){newX, newY})) {
                                gridType tempGrid[8][8];
                                memcpy(tempGrid, grid, sizeof(gridType) * 8 * 8);
                                refreshBoard(WHITE, tempGrid, (Positions){i, j}, (Positions){newX, newY});
                                int boardValue = minimax(tempGrid, MAX_DEPTH, 0);
                                if (boardValue > bestValue) {
                                    bestValue = boardValue;
                                    bestMoveFrom = (Positions){i, j};
                                    bestMoveTo = (Positions){newX, newY};
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Return the best move found
    Move bestMove = {bestMoveFrom, bestMoveTo};
    return bestMove;
}



int minimax(gridType grid[][8], int depth, int maximizingPlayer) {
    int winner = win(grid);
    if (depth == 0 || winner != 0) {
        return evaluate(grid);
    }

    if (maximizingPlayer) {
        int maxEval = -10000;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (grid[i][j].color == WHITE) {
                    for (int di = -2; di <= 2; di += 2) {
                        for (int dj = -2; dj <= 2; dj += 2) {
                            int newX = i + di;
                            int newY = j + dj;
                            if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                                if (validDestPiece(WHITE, grid, (Positions){i, j}, (Positions){newX, newY}) || 
                                    takePiece(WHITE, grid, (Positions){i, j}, (Positions){newX, newY})) {
                                    gridType tempGrid[8][8];
                                    memcpy(tempGrid, grid, sizeof(gridType) * 8 * 8);
                                    refreshBoard(WHITE, tempGrid, (Positions){i, j}, (Positions){newX, newY});
                                    int eval = minimax(tempGrid, depth - 1, 0);
                                    maxEval = (eval > maxEval) ? eval : maxEval;
                                }
                            }
                        }
                    }
                }
            }
        }
        return maxEval;
    } else {
        int minEval = 10000;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (grid[i][j].color == RED) {
                    for (int di = -2; di <= 2; di += 2) {
                        for (int dj = -2; dj <= 2; dj += 2) {
                            int newX = i + di;
                            int newY = j + dj;
                            if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                                if (validDestPiece(RED, grid, (Positions){i, j}, (Positions){newX, newY}) || 
                                    takePiece(RED, grid, (Positions){i, j}, (Positions){newX, newY})) {
                                    gridType tempGrid[8][8];
                                    memcpy(tempGrid, grid, sizeof(gridType) * 8 * 8);
                                    refreshBoard(RED, tempGrid, (Positions){i, j}, (Positions){newX, newY});
                                    int eval = minimax(tempGrid, depth - 1, 1);
                                    minEval = (eval < minEval) ? eval : minEval;
                                }
                            }
                        }
                    }
                }
            }
        }
        return minEval;
    }
}



int evaluate(gridType grid[][8]) {
    int score = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j].color == WHITE) {
                score += 10;
                if (grid[i][j].king == TRUE) {
                    score += 5;
                }
            } else if (grid[i][j].color == RED) {
                score -= 10;
                if (grid[i][j].king == TRUE) {
                    score -= 5;
                }
            }
        }
    }
    return score;
}

void movePiece(gridType grid[][8], Positions from, Positions to) {
    // Move the piece from 'from' to 'to'
    grid[to.x][to.y] = grid[from.x][from.y]; // Move the piece
    grid[from.x][from.y].color = UNDEFINED; // Clear the original position
    grid[from.x][from.y].state = EMPTY; // Update state
}