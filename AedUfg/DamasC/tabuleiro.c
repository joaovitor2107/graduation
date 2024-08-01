#include "tabuleiro.h"

void printBoard(SDL_Surface *screen, gridType grid[][8]) {
    SDL_Surface *square[8] = {NULL}, *whiteElipse = NULL, *redElipse = NULL;
    SDL_Surface *whiteKing = NULL, *redKing = NULL;
    SDL_Rect position;
    int squareColor = 1;

    for (int i = 0; i < SQUARE_NUMBERS; i++) {
        square[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 100, 32, 0, 0, 0, 0);
    }

    position.x = 0;
    position.y = 0;

    for(int i = 0; i < SQUARE_NUMBERS; i++) {
        for (int j = 0; j < SQUARE_NUMBERS; j++) {
            position.x = j * 100;
            position.y = i * 100;

            if (!square) {
                fprintf(stderr, "SDL_CreateRGBSurface failed: %s\n", SDL_GetError());
                exit(1);
            }

            if (squareColor == RED) {
                SDL_FillRect(square[i], NULL, SDL_MapRGB(square[i]->format, 255, 0, 0));
            } else {
                SDL_FillRect(square[i], NULL, SDL_MapRGB(square[i]->format, 0, 0, 0));
            }

            SDL_BlitSurface(square[i], NULL, screen, &position);
            squareColor = -squareColor;
        }
        squareColor = -squareColor;
        position.y = position.y + 100;
    }

    whiteElipse = IMG_Load("Sprites/white_elipse.png");
    redElipse = IMG_Load("Sprites/red_elipse.png");
    whiteKing = IMG_Load("Sprites/whiteKing.png");
    redKing = IMG_Load("Sprites/redKing.png");

    if (!whiteElipse || !redElipse || !whiteKing || !redKing) {
        fprintf(stderr, "IMG_Load failed: %s\n", IMG_GetError());
        exit(1);
    }

    for (int i = 0; i < SQUARE_NUMBERS; i++) {
        for (int j = 0; j < SQUARE_NUMBERS; j++) {
            position.x = j * 100;
            position.y = i * 100;

            if (grid[i][j].state == FULL && grid[i][j].color == WHITE) {
                if (grid[i][j].king == TRUE) {
                    SDL_BlitSurface(whiteKing, NULL, screen, &position);
                } else {
                    SDL_BlitSurface(whiteElipse, NULL, screen, &position);
                }
            } else if (grid[i][j].state == FULL && grid[i][j].color == RED) {
                if (grid[i][j].king == TRUE) {
                    SDL_BlitSurface(redKing, NULL, screen, &position);
                } else {
                    SDL_BlitSurface(redElipse, NULL, screen, &position);
                }
            }
        }
    }

    SDL_FreeSurface(whiteElipse);
    SDL_FreeSurface(redElipse);
    SDL_FreeSurface(whiteKing);
    SDL_FreeSurface(redKing);

    SDL_Flip(screen);
}


void initBoard(gridType grid[][8]){

    int blit = -1;

    for(int i = 0;i < SQUARE_NUMBERS;i++){
        for(int j = 0; j < SQUARE_NUMBERS; j++){
            grid[i][j].state = EMPTY;
            grid[i][j].color = UNDEFINED;
        }
    }    

    for(int i = 0;i < 3; i++){
        for(int j = 0; j < SQUARE_NUMBERS;j++){
        
            if(blit == 1){
                grid[i][j].color = WHITE;
                grid[i][j].state = FULL;
                grid[i][j].king = FALSE;
            }

            blit = -blit;
        }

        blit = -blit;
    }


    blit = 1;
    for(int i = 5;i < SQUARE_NUMBERS; i++){
        for(int j = 0; j < SQUARE_NUMBERS;j++){

            if(blit == 1){
                grid[i][j].color = RED;
                grid[i][j].state = FULL;
                grid[i][j].king = FALSE;
            }

            blit = -blit;
        }

        blit = -blit;
    }    

}