//
// Created by kali on 1/11/25.
//

#ifndef PACMAN_H
#define PACMAN_H

#include "entity.h"




void eat(char **level, int x, int y);

void eatSuperPacgum(const MovingEntity *pacman, MovingEntity *ghosts, const Textures *textures, char **level);

#endif //PACMAN_H
