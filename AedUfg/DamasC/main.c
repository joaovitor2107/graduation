#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "jogo.h" 
//the checkers game is from MARVEL-PROJECTS/Checkers-Game on github, with a few changes(like adding a king) and correcting some details

#include "bot.h"
//the bot code is totally mine and the implementation aswell

void pause();

int main(int argc, char *agrv[]){

    SDL_Surface *screen = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetCaption("DAMAS ", NULL);

    screen = SDL_SetVideoMode(1000, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (screen == NULL){
        fprintf(stderr, "Initialisation SDL error! %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    initGame(screen);
    SDL_Quit();

    return 0;    
}