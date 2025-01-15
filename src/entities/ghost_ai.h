//
// Created by kali on 1/11/25.
//

#ifndef GHOST_AI_H
#define GHOST_AI_H

#include "entity.h"
#include "limits.h"


#define INKY_RANDOMNESS 3  // 1 chance sur 3 de se déplacer aléatoirement
#define BLINKY_RANDOMNESS 4



Coord * getPotentialDirections(const char ** level, const MovingEntity* ghost, int * nbDir);
void handleDeadEnd(MovingEntity *ghost);


int getStep(const int start, const int end);
bool hasLineOfSight(const char **level, const MovingEntity *pinky, const MovingEntity *pacman);
Coord getPacmanNextIntersec(const char **level, const MovingEntity *pacman);



void sendGhostToCenter(MovingEntity *ghost);
void updateGhostState(MovingEntity *ghosts, const Textures *textures);


void clydeMove(MovingEntity *clyde, const char ** level);
void pinkyMove(MovingEntity *pinky, const MovingEntity *pacman, const char **level);
void blinkyMove(MovingEntity *inky, const MovingEntity* pacman, const char **level);
void inkyMove(MovingEntity *inky, const MovingEntity* pacman, const char **level, int randomness);
void specificGhostMovement(MovingEntity *ghost, const MovingEntity *pacman, const char **level);



#endif //GHOST_AI_H
