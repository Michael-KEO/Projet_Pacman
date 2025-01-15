//
// Created by kali on 1/11/25.
//

#include "entity.h"

#include "../core/main.h"

Coord findEntityInitialPosition(const char** level, EntityName name) {
    constexpr char entitySymbols[] = {'O', 'B', 'C', 'I', 'P'};

    const char entitySymbol = entitySymbols[name];

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (level[i][j] == entitySymbol) {
                return (Coord){ j, i};
            }
        }
    }

    printf("%p not found\n", &name);
    return (Coord){ -1, -1 };
}

MovingEntity *initializeEntities(const char **level, const Textures *textures) {
    // Allocation dynamique d'un tableau de 5 entités
    MovingEntity *entities = malloc(sizeof(MovingEntity) * NUM_ENTITIES);
    if (entities == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les entités.\n");
        exit(EXIT_FAILURE);
    }

    // Tableau des noms des entités
    EntityName names[NUM_ENTITIES] = {PACMAN, BLINKY, CLYDE, INKY, PINKY};

    for (int i = 0; i < NUM_ENTITIES; i++) {
        // Initialisation du nom
        entities[i].name = names[i];

        // Position initiale
        entities[i].pos = findEntityInitialPosition(level, entities[i].name);
        entities[i].dir = (Coord){0, 0};

        // Direction initiale et texture selon le type d'entité
        switch (entities[i].name) {
            case PACMAN:
                entities[i].texture = textures->texturePacman;     // Texture Pacman
            break;
            case BLINKY:
                entities[i].texture = textures->textureBlinky;     // Texture Blinky
            break;
            case CLYDE:
                entities[i].texture = textures->textureClyde;      // Texture Clyde
            break;
            case INKY:
                entities[i].texture = textures->textureInky;       // Texture Inky
            break;
            case PINKY:
                entities[i].texture = textures->texturePinky;      // Texture Pinky
            break;
            default:
                break;
        }
    }

    return entities;  // Retourne le tableau d'entités initialisées
}

void moveEntity(MovingEntity *entity, const Coord *pendingDir, const char **level) {

    // Vérifie si la direction en attente est valide
    Coord nextPosPending = {entity->pos.x + pendingDir->x, entity->pos.y + pendingDir->y};

    if (isWalkable((char**)level, nextPosPending.x, nextPosPending.y)) {
        // Met à jour la direction actuelle dès que possible
        entity->dir = *pendingDir;
    }

    // Calcule la position suivante selon la direction actuelle
    const Coord nextPos = {entity->pos.x + entity->dir.x, entity->pos.y + entity->dir.y};

    if (isWalkable((char **)level, nextPos.x, nextPos.y)) {
        // Déplace l'entité dans la direction actuelle
        entity->pos = nextPos;
    }

    // Gestion des limites (téléportation sur les bords)
    if (entity->pos.x < 0) entity->pos.x = WIDTH - 1;
    if (entity->pos.y < 0) entity->pos.y = HEIGHT - 1;
    if (entity->pos.x >= WIDTH) entity->pos.x = 0;
    if (entity->pos.y >= HEIGHT) entity->pos.y = 0;
}


bool checkCollision(const MovingEntity *pacman, const MovingEntity *ghost) {
     // 1️⃣ Collision directe : même position
    if (pacman->pos.x == ghost->pos.x && pacman->pos.y == ghost->pos.y) {
        return true;  // Collision détectée
    }

    // 2️⃣ Collision croisée : ils se croisent
    Coord pacmanNext = {pacman->pos.x + pacman->dir.x, pacman->pos.y + pacman->dir.y};
    Coord ghostNext = {ghost->pos.x + ghost->dir.x, ghost->pos.y + ghost->dir.y};

    if (pacmanNext.x == ghost->pos.x && pacmanNext.y == ghost->pos.y &&
        ghostNext.x == pacman->pos.x && ghostNext.y == pacman->pos.y) {
        return true;  // Collision croisée détectée
    }

    return false;  // Pas de collision   
}

bool detectCollision(const MovingEntity *entities, int numGhosts) {
    const MovingEntity *pacman = &entities[0];

    for (int i = 1; i <= numGhosts; i++) {  // Commence à 1 pour ignorer Pacman
        if (checkCollision(pacman, &entities[i])) {
            printf("Collision detected with ghost %d!\n", i);
            return true;
        }
    }
    return false;
}

void handleCollision(const MovingEntity *pacman, MovingEntity *ghosts, const char **level) {
    for (int i = 0; i < NUM_GHOSTS; i++) {
        if (checkCollision(pacman, &ghosts[i])) {
            if (ghosts[i].isBlue) {
                printf("Fantôme %d mangé ! Il retourne au centre.\n", i);
                sendGhostToCenter(&ghosts[i]);
            } else {
                printf("Pacman a perdu !\n");
                //exit(0);  // Fin de la partie
            }
        }
    }
}


