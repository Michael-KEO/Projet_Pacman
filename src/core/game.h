//
// Created by kali on 1/11/25.
//

#ifndef GAME_H
#define GAME_H
#include "main.h"

// Fonctions principales
void initializeGame(RendererParameters *params, Textures *textures, char ***level);
void verifyClosingGame(int *running);
void handleEvents(MovingEntity *pacman, Coord *pendingDir, const char** level, int *running);
void updateEntitiesTextures(MovingEntity *entity, const Textures *textures);
void renderGame(RendererParameters *params, Textures *textures, char **level, MovingEntity *entities);
void cleanupGame(const RendererParameters *params, char **level);

int isWalkable(char **level, int x, int y);
bool win(const char **level);




#endif //GAME_H
