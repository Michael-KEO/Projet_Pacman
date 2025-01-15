//
// Created by kali on 1/8/25.
//

#include "core/main.h"


Uint32 superPacgumStartTime = 0;
const Uint32 SUPER_PACGUM_DURATION_MS = 10000;  // 10 secondes

int main(int argc, char* argv[]) {
    srand(time(NULL));
    RendererParameters params;
    Textures textures;
    char **level;


    initializeGame(&params, &textures, &level);

    // Initialisation des entités
    MovingEntity *entities = initializeEntities((const char**)level, &textures);
    MovingEntity *pacman = &entities[0];
    MovingEntity *ghosts = &entities[1];
    Coord pendingDir = {0, 0};


    int running = 1;
    while (running) {

        // Gérer les événements pour Pacman
        handleEvents(pacman, &pendingDir, (const char**)level, &running);

        // Déplacement des fantômes
        for (int i = 1; i < NUM_ENTITIES; i++) {
            specificGhostMovement(&entities[i], pacman, (const char**)level);
        }

        // Gestion de la nourriture
        eat(level, pacman->pos.x, pacman->pos.y);

        eatSuperPacgum(pacman, ghosts, &textures, level);

        // Met à jour l'état des fantômes
        updateGhostState(ghosts, &textures);

        // Vérifie les collisions
        handleCollision(pacman, ghosts, (const char **)level);

        // Vérification de la victoire
        if (win((const char **)level)) {
            printf("You win!\n");
            running = 0;
        }

        //mettra à jour le rendu
        renderGame(&params, &textures, level, entities);
    }

    cleanupGame(&params, level);
    free(entities);

}






