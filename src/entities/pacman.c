//
// Created by kali on 1/11/25.
//

#include "pacman.h"

#include "ghost_ai.h"
#include "stdio.h"


void eat(char **level, int x, int y) {
    if (level[y][x] == '.') level[y][x] = ' ';
}

void eatSuperPacgum(const MovingEntity *pacman, MovingEntity *ghosts, const Textures *textures, char **level) {
    if (level[pacman->pos.y][pacman->pos.x] == 'G') {  // Super Pacgum détectée
        level[pacman->pos.y][pacman->pos.x] = ' ';  // Pacman mange la Super Pacgum

        printf("Super Pacgum mangée !\n");

        for (int i = 0; i < NUM_GHOSTS; i++) {
            // Les fantômes font demi-tour
            handleDeadEnd(&ghosts[i]);


            //Activer l'état bleu
            ghosts[i].isBlue = true;
        }

        // Démarrer le compte à rebours de l'effet
        superPacgumStartTime = SDL_GetTicks();
    }
}


