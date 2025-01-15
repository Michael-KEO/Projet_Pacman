cmake_minimum_required(VERSION 3.16)
project(pacman C)

set(CMAKE_C_STANDARD 23)

# Définir les fichiers sources et en-têtes
set(SRCS
        #src/main.c
        src/levels_and_framework/framework.c
        src/levels_and_framework/firstLevel.c
        src/entities/ghost_ai.c
        src/entities/pacman.c
        src/entities/entity.c
        src/core/game.c
        src/main.c
)

set(HEADERS
        #src/main.h
        src/levels_and_framework/framework.h
        src/levels_and_framework/firstLevel.h
        src/entities/ghost_ai.h
        src/entities/pacman.h
        src/entities/entity.h
        src/core/game.h
        src/core/main.h
)

# Configuration spécifique à l'OS
if(WIN32)
    # Chemins spécifiques pour Windows
    set(SDL2_DIR "C:/Users/micha/sdl2")
    include_directories(${SDL2_DIR}/include)
    link_directories(${SDL2_DIR}/lib)
    set(SDL2_LIBRARIES mingw32 SDL2main SDL2)
else()
    # Configuration pour Linux
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

# Création de l'exécutable
add_executable(pacman ${SRCS} ${HEADERS})

# Liaison des bibliothèques SDL2
if(WIN32)
    target_link_libraries(pacman ${SDL2_LIBRARIES})
else()
    target_link_libraries(pacman ${SDL2_LIBRARIES})
endif()

# Copier les ressources dans le répertoire de build
file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
