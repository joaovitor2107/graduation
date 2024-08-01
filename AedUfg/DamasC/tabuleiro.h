#ifndef gameIterface
#define gameInterface

    #include <stdlib.h>
    #include <stdio.h>
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>
    #include "constantes.h"
    
    void printBoard(SDL_Surface *screen, gridType grid[][8]);
    
    //inicializa o estado do tabuleiro
    void initBoard(gridType grid[][8]);

#endif