
# Cub3D

## Overview

Cub3D is a raycasting project written in C, designed to provide an introduction to raycasting techniques and the underlying mathematics. The project features player movement, a minimap, animated sprites, and textures that vary based on the player's viewing angle, as well as detailed floor and ceiling textures.

## Features

- **Real-Time Player Movement:** Allows the player to navigate the 3D environment with responsive controls.
- **Minimap:** Provides an overhead view to help the player stay oriented.
- **Animated Sprites:** Adds dynamic visual elements with animated sprite support.
- **Angle-Based Textures:** Enhances realism with textures that change based on the player's viewing angle.
- **Floor and Ceiling Textures:** Adds depth and immersion with detailed textures for the floor and ceiling.

## Introduction to Raycasting

Raycasting is a rendering technique used to create a 3D perspective from a 2D map by casting rays from the player's point of view. Each ray calculates the distance to the nearest wall, allowing the program to draw vertical lines that represent the walls, creating a 3D effect.

### Math Library

The custom math library in Cub3D handles essential operations such as vector mathematics, angle calculations, and collision detection. This library is critical for implementing the raycasting algorithm and ensuring accurate and efficient rendering.

### Algorithms

Cub3D employs several key algorithms:
- **Raycasting Algorithm:** Projects rays from the player's position to determine the distance to walls and render the scene.
- **Collision Detection:** Ensures the player cannot move through walls by detecting potential collisions.
- **Sprite Animation:** Manages animated sprites, adding dynamic elements to the game.
- **Texture Mapping:** Applies textures to walls, floors, and ceilings, adjusting based on the player's viewing angle.

## Compilation and Usage

### Compilation

To compile the project, use the provided `Makefile`:
```sh
make

### Usage

Run the compiled program with a map file ending in `.cub`:
```sh
./cub3d [map argument ended in .cub]
```

### Example

```sh
./cub3d example_map.cub
```
