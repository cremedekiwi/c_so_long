# so_long

## Overview
The `so_long` project is a simple 2D game created as part of an educational exercise. The project is typically developed using the **C programming language** and the **MLX graphics library**. The goal of the game is to navigate through a map, collect items, and reach the exit while avoiding obstacles.

This README provides a detailed explanation of the project, including how to set it up, build it, and play the game.

## Features

- **2D Graphics:** Utilizes the MLX library for rendering sprites and handling input.
- **Interactive Gameplay:** Players move a character through a maze-like map.
- **Objectives:** Collect all items (e.g., "collectibles") before reaching the exit.
- **Obstacles:** Avoid or navigate around walls and other impediments.
- **Custom Maps:** Supports custom maps with specific formatting.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/cremedekiwi/c_so_long.git so_long
   cd so_long
   ```

2. Build the project:
   ```bash
   make
   ```

3. Run the game:
   ```bash
   ./so_long maps_valid/map2_big.ber
   ```

## Gameplay
### Controls
- **W**: Move Up
- **A**: Move Left
- **S**: Move Down
- **D**: Move Right
- **ESC**: Quit the game

### Objectives
- Collect all collectibles (e.g., items marked with a specific symbol like `C`) before exiting.
- Reach the exit (`E`) to win the game.

### Rules
- The map must follow the required format (see **Map Format** below).
- The game ends if the player successfully collects all items and exits or if the player manually quits.

## Map Format

Maps should be designed in a `.ber` file and follow these rules:
1. **Rectangular:** All rows must have the same length.
2. **Walls:** The map should be surrounded by walls (`1`).
3. **Symbols:**
   - `0`: Walkable space
   - `1`: Wall
   - `C`: Collectible
   - `E`: Exit
   - `P`: Player's starting position
4. **Single Exit & Player:** Each map must contain exactly one `E` and one `P`.

Example of a valid map (`map.ber`):
```
111111
1P0C01
100001
1C0E11
111111
```
