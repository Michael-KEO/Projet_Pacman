//
// Created by kali on 1/11/25.
//

#include "game.h"

void initializeGame(RendererParameters *params, Textures *textures, char ***level) {
    initWindowed(params, textures, HEIGHT, WIDTH);
    loadFirstLevel(level);
}

void verifyClosingGame(int *running) {
    SDL_Event e;
    const int event = getInput();

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            *running = 0;
        }
    }
    if (event == SDLK_ESCAPE) *running = 0;
}

void handleEvents(MovingEntity * pacman, Coord *pendingDir, const char** level, int *running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *running = 0;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    *running = 0;
                break;
                case SDLK_UP:
                    *pendingDir = (Coord){0, -1};  // Haut
                break;
                case SDLK_DOWN:
                    *pendingDir = (Coord){0, 1};   // Bas
                break;
                case SDLK_LEFT:
                    *pendingDir = (Coord){-1, 0};  // Gauche
                break;
                case SDLK_RIGHT:
                    *pendingDir = (Coord){1, 0};   // Droite
                break;
                default:
                    break;
            }
        }
    }
    moveEntity(pacman, pendingDir, (const char**)level);
}

void updateTexture_test(RendererParameters *params, MovingEntity *entities, const Textures *textures) {
    for (int i = 0; i < NUM_ENTITIES; i++) {
        // Mettre à jour la texture selon la direction
        updateEntitiesTextures(&entities[i], textures);

        // Dessiner l'entité avec sa texture mise à jour
        drawSpriteOnGrid(entities[i].texture, entities[i].pos.x, entities[i].pos.y, 0, params);
    }
}


void renderGame(RendererParameters *params, Textures *textures, char **level, MovingEntity *entities) {
    // Nettoyer l'affichage à l'écran
    SDL_RenderClear(params->renderer);

    // Dessiner le niveau
    drawLevel(level, HEIGHT, WIDTH, params, textures);

    // Appeler la nouvelle fonction pour gérer l'affichage des entités
    updateTexture_test(params, entities, textures);

    // Mettre à jour l'affichage
    update(params);
}


void cleanupGame(const RendererParameters *params, char **level) {
    for (int i = 0; i < HEIGHT; i++) {
        free(level[i]);
    }
    free(level);

    SDL_DestroyRenderer(params->renderer);
    SDL_DestroyWindow(params->window);
    SDL_Quit();
}


int isWalkable(char **level, int x, int y) {
    return (level[y][x] != 'H');
}

bool win(const char **level) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (level[y][x] == '.') {
                return false;
            }
        }
    }
    return true;
}



void updateEntitiesTextures(MovingEntity *entity, const Textures *textures) {
    if (entity->isBlue) entity->texture = textures->textureBLue;
    else {
        switch (entity->name) {
        case BLINKY:
            if (entity->dir.x == 0 && entity->dir.y == -1) {
                entity->texture = textures->textureBlinkyU;  // Haut
            } else if (entity->dir.x == 0 && entity->dir.y == 1) {
                entity->texture = textures->textureBlinkyD;  // Bas
            } else if (entity->dir.x == -1 && entity->dir.y == 0) {
                entity->texture = textures->textureBlinkyL;  // Gauche
            } else if (entity->dir.x == 1 && entity->dir.y == 0) {
                entity->texture = textures->textureBlinky;  // Droite
            }
        break;
            case PINKY:
            if (entity->dir.x == 0 && entity->dir.y == -1) {
                entity->texture = textures->texturePinkyU;
            } else if (entity->dir.x == 0 && entity->dir.y == 1) {
                entity->texture = textures->texturePinkyD;
            } else if (entity->dir.x == -1 && entity->dir.y == 0) {
                entity->texture = textures->texturePinkyL;
            } else if (entity->dir.x == 1 && entity->dir.y == 0) {
                entity->texture = textures->texturePinky;
            }
            break;

        case INKY:
            if (entity->dir.x == 0 && entity->dir.y == -1) {
                entity->texture = textures->textureInkyU;
            } else if (entity->dir.x == 0 && entity->dir.y == 1) {
                entity->texture = textures->textureInkyD;
            } else if (entity->dir.x == -1 && entity->dir.y == 0) {
                entity->texture = textures->textureInkyL;
            } else if (entity->dir.x == 1 && entity->dir.y == 0) {
                entity->texture = textures->textureInky;
            }
            break;

        case CLYDE:
            if (entity->dir.x == 0 && entity->dir.y == -1) {
                entity->texture = textures->textureClydeU;
            } else if (entity->dir.x == 0 && entity->dir.y == 1) {
                entity->texture = textures->textureClydeD;
            } else if (entity->dir.x == -1 && entity->dir.y == 0) {
                entity->texture = textures->textureClydeL;
            } else if (entity->dir.x == 1 && entity->dir.y == 0) {
                entity->texture = textures->textureClyde;
            }
            break;

        default:
            break;
        }
    }
}

