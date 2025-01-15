//
// Created by kali on 1/11/25.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "../levels_and_framework/framework.h"

#define NUM_ENTITIES 5
#define NUM_GHOSTS 4

extern Uint32 superPacgumStartTime;  // Début de l'effet
extern const Uint32 SUPER_PACGUM_DURATION_MS;  // Durée de 5 secondes en millisecondes



extern int superPacgumTimer;  // ✅ Variable globale

typedef enum EntityName EntityName;
enum EntityName
{
    PACMAN,
    BLINKY,
    CLYDE,
    INKY,
    PINKY
};
// Définition des structures
typedef struct Coord Coord;
struct Coord
{
    int x;
    int y;
};

typedef struct MovingEntity MovingEntity;
struct MovingEntity
{
    Coord pos;
    Coord dir;
    EntityName name;
    SDL_Texture * texture;
    bool isBlue;
};


Coord findEntityInitialPosition(const char** level, EntityName name);
MovingEntity *initializeEntities(const char **level, const Textures *textures);
void moveEntity(MovingEntity *entity, const Coord *pendingDir, const char **level);

bool checkCollision(const MovingEntity *pacman, const MovingEntity *ghost);
bool detectCollision(const MovingEntity *entities, int numGhosts);

void handleCollision(const MovingEntity *pacman, MovingEntity *ghosts, const char **level);
#endif //ENTITY_H
