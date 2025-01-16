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
- **SDL2_mixer** (optionnel) : pour la gestion des sons et musiques.
- **Makefile** : pour automatiser la compilation du projet.

### Outils de Développement
- **GCC** : compilateur C.
- **Git** : outil de versionning.
- **GDB** : débogueur.

## 🛠️ Structure du Projet

```
Pacman/
├── src/               # Code source du jeu
│   ├── main.c         # Fonction principale du jeu
│   ├── game.c         # Logique du jeu (gestion des entités, collisions)
│   ├── render.c       # Fonctions d'affichage
│   └── input.c        # Gestion des entrées clavier
├── include/           # Fichiers d'en-tête
│   ├── game.h         # Déclarations des fonctions du jeu
│   ├── render.h       # Déclarations pour le rendu
│   └── input.h        # Déclarations pour les entrées utilisateur
├── assets/            # Ressources du jeu (images, sons)
│   ├── textures/      # Textures PNG/JPG
│   └── sounds/        # Fichiers audio
├── Makefile           # Script de compilation
└── README.md          # Documentation du projet
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
- **SDL2**, **SDL2_image** installés

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

- Ajout de sons et musiques d'ambiance.
- Gestion des niveaux multiples.
- Mode multijoueur local.
- IA plus avancée pour les fantômes.

## 👤 Auteur

- **Michael** - Étudiant, passionné par la cybersécurité et les réseaux.

---

✨ **Merci d'avoir consulté ce projet !** ✨


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
- **Ninja** : outil de compilation.
- **Git** : pour la gestion de versions.

## 🏗️ Structure du Projet

```
Pacman/
├── src/               # Code source du jeu
│   ├── main.c         # Fonction principale du jeu
│   ├── game.c         # Logique du jeu (gestion des entités, collisions)
│   ├── render.c       # Fonctions d'affichage
│   └── input.c        # Gestion des entrées clavier
├── include/           # Fichiers d'en-tête
│   ├── game.h         # Déclarations des fonctions du jeu
│   ├── render.h       # Déclarations pour le rendu
│   └── input.h        # Déclarations pour les entrées utilisateur
├── assets/            # Ressources du jeu (images)
│   └── textures/      # Textures PNG/JPG
├── Makefile           # Script de compilation
└── README.md          # Documentation du projet
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
- **Ninja** installé
- **SDL2**, **SDL2_image** installés

### Compilation
```bash
ninja
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

- Ajout de sons et musiques d'ambiance.
- Gestion des niveaux multiples.
- Mode multijoueur local.
- IA plus avancée pour les fantômes.

## 👤 Auteur

- **Michael** - Étudiant à l'EFREI Villejuif, passionné par la cybersécurité et les réseaux.

---

✨ **Merci d'avoir consulté ce projet !** ✨



