//
// Created by kali on 1/11/25.
//

#include "ghost_ai.h"
#include "../core/main.h"




Coord * getPotentialDirections(const char ** level, const MovingEntity* ghost, int * nbDir) {
    Coord * possibleDir = malloc(sizeof(Coord) * 4);
    *nbDir = 0;

    if (possibleDir == NULL) {
        printf("Error: Memory allocation failed for directions.\n");
        return NULL;
    }

    const Coord possibleMoves[4] = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };

    for (int i = 0; i < 4; i++) {
        const int newX = ghost->pos.x + possibleMoves[i].x;
        const int newY = ghost->pos.y + possibleMoves[i].y;

        // Vérifie si la case est valide et évite les demi-tours
        if (isWalkable((char **)level, newX, newY) &&
            !(possibleMoves[i].x == -ghost->dir.x && possibleMoves[i].y == -ghost->dir.y)) {
            possibleDir[*nbDir] = possibleMoves[i];
            (*nbDir)++;
            }
    }

    // Si aucune direction possible, retourne NULL
    if (*nbDir == 0) {
        free(possibleDir);
        return NULL;
    }

    return possibleDir;
}

void handleDeadEnd(MovingEntity *ghost) {
    ghost->dir.x = -ghost->dir.x;
    ghost->dir.y = -ghost->dir.y;
}

int getStep(const int start, const int end) {
    if (start == end) return 0;     // Pas de déplacement
    return (start < end) ? 1 : -1; // Déplacement à gauche ou à droite
}

bool hasLineOfSight(const char **level, const MovingEntity *pinky, const MovingEntity *pacman) {
    // Vérifier si Pinky et Pacman sont alignés
    if (pinky->pos.x == pacman->pos.x || pinky->pos.y == pacman->pos.y) {
        int stepX = getStep(pinky->pos.x, pacman->pos.x);
        int stepY = getStep(pinky->pos.y, pacman->pos.y);

        // Parcourir dans la direction alignée (ligne ou colonne)
        int x = pinky->pos.x + stepX;
        int y = pinky->pos.y + stepY;

        while (x != pacman->pos.x|| y != pacman->pos.y) {
            if (!isWalkable((char **)level, x, y)) // Vérifie chaque case
                return false;

            x += stepX; // Avance dans la direction X
            y += stepY; // Avance dans la direction Y
        }
        return true; // Aucun mur rencontré
    }
    return false; // Pas alignés
}

Coord getPacmanNextIntersec(const char **level, const MovingEntity *pacman) {
    // Si Pacman ne bouge pas, retourne sa position actuelle
    if (pacman->dir.x == 0 && pacman->dir.y == 0) {
        //printf("position de pacman:(%d, %d)\n", pacman->pos.x, pacman->pos.y );
        //printf("target: (%d, %d)\n", pacman->pos.x, pacman->pos.y);
        return pacman->pos;
    }

    // Vérifier si la position actuelle est une intersection
    int nbDir = 0;
    MovingEntity tempEntity = {pacman->pos, pacman->dir};
    Coord *currentDirs = getPotentialDirections(level, &tempEntity, &nbDir);
    if (currentDirs) {
        if (nbDir > 1) {
            free(currentDirs);
            //printf("position de pacman:(%d, %d)\n", pacman->pos.x, pacman->pos.y );
            //printf("target: (%d, %d)\n", pacman->pos.x, pacman->pos.y);
            return pacman->pos;  // Déjà sur une intersection
        }
        free(currentDirs);
    }

    Coord currentPos = pacman->pos;
    Coord currentDir = pacman->dir;

    // Limiter le nombre d'itérations pour éviter une boucle infinie
    int maxIterations = WIDTH * HEIGHT; // Maximum possible de cases
    int iterations = 0;

    while (iterations < maxIterations) {
        int nextX = currentPos.x + currentDir.x;
        int nextY = currentPos.y + currentDir.y;

        // Vérifier les limites et si la case est marchable
        if (nextX < 0 || nextY < 0 || nextX >= WIDTH || nextY >= HEIGHT ||
            !isWalkable((char **)level, nextX, nextY)) {
            //printf("position de pacman:(%d, %d)\n", pacman->pos.x, pacman->pos.y );
            //printf("target: (%d, %d)\n", currentPos.x, currentPos.y);
            return currentPos;
            }

        currentPos.x = nextX;
        currentPos.y = nextY;

        // Vérifier si c'est une intersection
        tempEntity = (MovingEntity){currentPos, currentDir};
        nbDir = 0;
        Coord *directions = getPotentialDirections(level, &tempEntity, &nbDir);

        if (directions) {
            if (nbDir > 1) {
                free(directions);
                //printf("position de pacman:(%d, %d)\n", pacman->pos.x, pacman->pos.y );
                //printf("target: (%d, %d)\n", currentPos.x, currentPos.y);
                return currentPos;
            }
            free(directions);
        }

        iterations++;
    }

    // Si on atteint le maximum d'itérations, retourner la position actuelle
    //printf("position de pacman:(%d, %d)\n", pacman->pos.x, pacman->pos.y );
    //printf("target: (%d, %d)\n", currentPos.x, currentPos.y);
    return pacman->pos;
}

void sendGhostToCenter(MovingEntity *ghost) {
    Coord center = (Coord){HEIGHT / 2, WIDTH / 2};  // Position centrale de la maison des fantômes

    ghost->pos = center;
    ghost->dir = (Coord){0, 0};  // Arrêt temporaire
}


void updateGhostState(MovingEntity *ghosts, const Textures *textures) {
    Uint32 currentTime = SDL_GetTicks();

    if (superPacgumStartTime != 0 && (currentTime - superPacgumStartTime) >  SUPER_PACGUM_DURATION_MS) {
        for (int i = 0; i < NUM_GHOSTS; i++) {
            ghosts[i].isBlue = false;

            // Réassigner la texture normale après l'effet
            switch (ghosts[i].name) {
                case BLINKY:
                    ghosts[i].texture = textures->textureBlinky;
                break;
                case PINKY:
                    ghosts[i].texture = textures->texturePinky;
                break;
                case INKY:
                    ghosts[i].texture = textures->textureInky;
                break;
                case CLYDE:
                    ghosts[i].texture = textures->textureClyde;
                break;
                default:
                    break;
            }
        }
        superPacgumStartTime = 0; //retour à 0
        printf("%s\n", "les fantômes redeviennes normaux");
    }
}


void clydeMove(MovingEntity *clyde, const char ** level) {
    // initialisation du nombre de directions
    int nbDir = 0;

    Coord * directions = getPotentialDirections(level, clyde, &nbDir);

    Coord pendingDir = {0, 0};

    if (nbDir == 0) { // Cul-de-sac : demi-tour obligatoire
        handleDeadEnd(clyde);
    }
    else {
        // Choix aléatoire parmi les directions disponibles
        int random = rand() % nbDir;
        pendingDir = directions[random];
    }

    // Mise à jour de la position de Clyde
    moveEntity(clyde, &pendingDir, level);

    free(directions);

}

void pinkyMove(MovingEntity *pinky, const MovingEntity *pacman, const char **level) {
    Coord pendingDir = {0, 0};
    int nbDir = 0;
    Coord *directions = getPotentialDirections(level, pinky, &nbDir);

    // Vérifie si Pinky a une ligne de vue directe vers Pacman
    if (hasLineOfSight(level, pinky, pacman)) {
        // Suit Pacman
        if (pinky->pos.x < pacman->pos.x) pendingDir = (Coord){1, 0}; // Droite
        else if (pinky->pos.x > pacman->pos.x) pendingDir = (Coord){-1, 0}; // Gauche
        else if (pinky->pos.y < pacman->pos.y) pendingDir = (Coord){0, 1}; // Bas
        else if (pinky->pos.y > pacman->pos.y) pendingDir = (Coord){0, -1}; // Haut

        // Vérifie si Pinky tente un demi-tour
        if (pendingDir.x == -pinky->dir.x && pendingDir.y == -pinky->dir.y) {
            if (nbDir > 0) {
                int random = rand() % nbDir;
                pendingDir = directions[random];
            }
        }
    } else {
        // Sinon, comportement aléatoire comme Clyde
        clydeMove(pinky, level);
        free(directions);  // ✅ Libération correcte de la mémoire
        return;
    }

    // Déplacement de Pinky
    moveEntity(pinky, &pendingDir, level);

    // ✅ Libération de la mémoire après déplacement
    free(directions);
}

void inkyMove(MovingEntity *inky, const MovingEntity* pacman, const char **level, const int randomness) {
    int nbDir = 0;
    Coord *directions = getPotentialDirections(level, inky, &nbDir);
    Coord pendingDir = {0, 0};

    // Comportement aléatoire : 1 chance sur INKY_RANDOMNESS
    if (rand() % randomness == 0 && nbDir > 0) {
        int random = rand() % nbDir;
        pendingDir = directions[random];
    } else {
        // Calculer les distances entre Inky et Pacman
        int deltaX = pacman->pos.x - inky->pos.x;
        int deltaY = pacman->pos.y - inky->pos.y;

        // Priorité à la plus grande différence
        if (abs(deltaX) > abs(deltaY)) {
            // Essayer de réduire la différence horizontale
            pendingDir = (deltaX > 0) ? (Coord){1, 0} : (Coord){-1, 0};

            // Vérifier si la direction est valide
            Coord nextPos = {inky->pos.x + pendingDir.x, inky->pos.y + pendingDir.y};
            if (!isWalkable((char **)level, nextPos.x, nextPos.y)) {
                // Sinon, essayer la direction verticale
                pendingDir = (deltaY > 0) ? (Coord){0, 1} : (Coord){0, -1};
            }
        } else {
            // Essayer de réduire la différence verticale
            pendingDir = (deltaY > 0) ? (Coord){0, 1} : (Coord){0, -1};

            // Vérifier si la direction est valide
            Coord nextPos = {inky->pos.x + pendingDir.x, inky->pos.y + pendingDir.y};
            if (!isWalkable((char **)level, nextPos.x, nextPos.y)) {
                // Sinon, essayer la direction horizontale
                pendingDir = (deltaX > 0) ? (Coord){1, 0} : (Coord){-1, 0};
            }
        }

        if (pendingDir.x == -inky->dir.x && pendingDir.y == -inky->dir.y) {
            if (nbDir > 0) {
                int random = rand() % nbDir;
                pendingDir = directions[random];
            }
        }

        // Si aucune direction ne fonctionne, choisir une direction aléatoire
        Coord nextPos = {inky->pos.x + pendingDir.x, inky->pos.y + pendingDir.y};
        if (!isWalkable((char **)level, nextPos.x, nextPos.y) && nbDir > 0) {
            int random = rand() % nbDir;
            pendingDir = directions[random];
        }
    }

    // Déplacer Inky
    moveEntity(inky, &pendingDir, level);

    // Libérer la mémoire
    free(directions);
}

void blinkyMove(MovingEntity *blinky, const MovingEntity* pacman, const char **level) {

    if (!blinky || !pacman || !level) return;

    const Coord targetIntersec = getPacmanNextIntersec(level, pacman);

    const MovingEntity targetPacman = {targetIntersec, {0, 0}};

    inkyMove(blinky, &targetPacman, level, BLINKY_RANDOMNESS);

}

void specificGhostMovement(MovingEntity *ghost, const MovingEntity *pacman, const char **level) {
    if (ghost->isBlue) {
        clydeMove(ghost, level);        //comportement de clyde
    }
    else {
        switch (ghost->name) {
            case BLINKY:
                blinkyMove(ghost, pacman, level);
                    break;
            case CLYDE:
                clydeMove(ghost, level);
            break;
            case PINKY:
                pinkyMove(ghost, pacman, level);
            break;
            case INKY:
                inkyMove(ghost, pacman, level, INKY_RANDOMNESS);
            break;
            default:
                break;
        }
    }
}





