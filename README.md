# Pacman - Projet de Jeu en C avec SDL2

## 📚 Description du Projet

Ce projet est une **réimplémentation du jeu classique Pacman** en langage **C**, utilisant la bibliothèque **SDL2** pour la gestion graphique. Le but est de recréer un environnement fidèle au jeu d'origine avec des fonctionnalités interactives, des ennemis (fantômes), et des mécaniques de jeu dynamiques.

### 🔍 Objectifs Principaux
- Contrôler Pacman pour collecter toutes les pastilles du labyrinthe.
- Éviter les fantômes (Blinky, Pinky, Inky, Clyde) qui poursuivent Pacman.
- Implémenter des comportements uniques pour chaque fantôme.
- Gérer les déplacements, collisions et conditions de victoire/défaite.

## 🛠️ Technologies et Outils Utilisés

### Langage de programmation
- **C** : langage principal utilisé pour développer la logique du jeu.

### Bibliothèques et Frameworks
- **SDL2 (Simple DirectMedia Layer 2)** : bibliothèque pour la gestion des fenêtres, des graphismes, des événements clavier et du rendu 2D.
- **SDL2_image** : pour charger et gérer les textures au format PNG/JPG.
- **Makefile**/**Ninja** : pour automatiser la compilation du projet.

### Outils de Développement
- **CLion** : IDE utilisé pour le développement du projet.
- **GCC** : compilateur C.
- **Git** : outil de versionning.
- **GDB** : débogueur.

## 🛠️ Structure du Projet

```
Projet_Pacman/
├── bin/                         # Fichiers binaires générés (exécutables)
├── include/                     # Fichiers d'en-tête (.h) partagés
├── lib/                         # Bibliothèques statiques et dynamiques (SDL2)
├── ressources/                  # Ressources du jeu (images, sons)
│   ├── images/                  # Textures et images du jeu (BMP, PNG)
├── src/                         # Code source du jeu
│   ├── core/                    # Logique principale du jeu
│   │   ├── game.h               # Déclarations des fonctions de gestion du jeu
│   │   ├── game.c               # Implémentation des fonctionnalités du jeu
│   │   └── main.h               # Déclarations des fonctions de démarrage
│   ├── entities/                # Gestion des entités du jeu (Pacman, fantômes)
│   │   ├── entity.h             # Déclarations des structures d'entités
│   │   ├── entity.c             # Implémentation des entités du jeu
│   │   ├── ghost_ai.h           # Déclarations de l'IA des fantômes
│   │   ├── ghost_ai.c           # Implémentation de l'IA des fantômes
│   │   ├── pacman.h             # Déclarations des fonctions spécifiques à Pacman
│   │   └── pacman.c             # Implémentation des comportements de Pacman
│   ├── levels_and_framework/    # Gestion des niveaux et du moteur du jeu
│   │   ├── first_level.h        # Déclarations pour le premier niveau
│   │   ├── first_level.c        # Implémentation du premier niveau
│   │   ├── framework.h          # Déclarations des fonctions du moteur du jeu
│   │   └── framework.c          # Implémentation du moteur du jeu
│   └── main.c                   # Point d'entrée du programme
├── Makefile                     # Script de compilation automatisée
└── README.md                    # Documentation du projet
```



## 👥 Entités du Jeu

- **Pacman** : personnage contrôlé par le joueur.
- **Fantômes** : ennemis avec des comportements distincts :
  - **Blinky** (rouge)
  - **Pinky** (rose)
  - **Inky** (bleu)
  - **Clyde** (orange)

## 📅 Instructions d'Installation et d'Exécution

### Prérequis
- **GCC** installé
- **SDL2**, **SDL2_image**

### Compilation
```bash
make
```

### Exécution
```bash
./pacman
```

## 🔧 Fonctionnalités Implémentées

- Déplacements fluides de Pacman via les touches directionnelles.
- Mouvements dynamiques des fantômes.
- Collecte des pastilles.
- Gestion des collisions.
- Condition de victoire/défaite.

## 🌟 Améliorations Futures
- Gestion des vies de Pacman
- Ajout de sons et musiques d'ambiance.
- Gestion des niveaux multiples.
- Mode multijoueur local.
- IA plus avancée pour les fantômes.

## 👤 Auteur

- **Michael KEO** - Étudiant, passionné par la cybersécurité et les réseaux.

---

✨ **Merci d'avoir consulté ce projet !** ✨

