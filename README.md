# so_long

A 2D game project built with MiniLibX, where the player must collect all coins and reach the exit. This project focuses on graphics programming, event handling, and game logic.

<img src="https://raw.githubusercontent.com/cremedekiwi/c_so_long/refs/heads/main/animation.gif" alt="animation">

## 📋 Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Map Format](#map-format)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Map Validation](#map-validation)
- [Technical Details](#technical-details)

## ✨ Features

- **2D Graphics**: Pixel-perfect sprite rendering using XPM textures
- **Map Validation**: Comprehensive map checking for valid game states
- **Movement System**: WASD controls with collision detection
- **Win Condition**: Player must collect all coins before exiting
- **Move Counter**: Tracks and displays the number of moves
- **Path Validation**: Ensures the map has a valid solution using flood fill algorithm
- **Error Handling**: Robust error checking for invalid maps and system failures

## 🚀 Installation

### Prerequisites
- GCC compiler
- Make
- MiniLibX library
- X11 development libraries (Linux)

### Clone and Build
```bash
# Clone the repository
git clone <repository-url>
cd so_long

# Build the project
make

# Clean object files
make clean

# Clean everything including executable
make fclean

# Rebuild everything
make re
```

## 📖 Usage

```bash
./so_long maps/map_name.ber
```

### Examples
```bash
# Play with a small map
./so_long maps_valid/map0_small.ber

# Play with a medium-sized map
./so_long maps_valid/map1_medium.ber

# Play with a large map
./so_long maps_valid/map2_big.ber
```

## 🗺️ Map Format

Maps must be saved with the `.ber` extension and contain the following elements:

| Character | Description |
|-----------|-------------|
| `1` | Wall |
| `0` | Empty space (floor) |
| `P` | Player starting position |
| `C` | Coin/Collectible |
| `E` | Exit |

### Map Rules
- Map must be rectangular
- Map must be surrounded by walls (`1`)
- Must contain exactly one player (`P`) and one exit (`E`)
- Must contain at least one coin (`C`)
- Must have a valid path from player to all coins and the exit

### Valid Map Example
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

## 🎮 Controls

| Key | Action |
|-----|--------|
| `W` or `w` | Move Up |
| `S` or `s` | Move Down |
| `A` or `a` | Move Left |
| `D` or `d` | Move Right |
| `ESC` | Exit Game |
| `X` (close button) | Exit Game |

## 📁 Project Structure

```
so_long/
├── Makefile              # Build configuration
├── includes/
│   └── so_long.h        # Main header file
├── srcs/                # Source files
│   ├── main.c          # Entry point and game initialization
│   ├── check_map.c     # Map validation (characters, duplicates)
│   ├── check_map2.c    # Map validation (rectangle, borders, coins)
│   ├── create_map.c    # Map parsing and rendering
│   ├── flood_fill.c    # Path validation algorithm
│   ├── movement.c      # Player movement and game logic
│   ├── read.c          # File reading utilities
│   ├── utils.c         # Utility functions and MLX initialization
│   └── cleanup.c       # Memory management and cleanup
├── textures/           # Game sprites (XPM format)
│   ├── wall.xpm
│   ├── floor.xpm
│   ├── player.xpm
│   ├── coin.xpm
│   └── exit.xpm
├── maps_valid/         # Valid test maps
├── maps_invalid/       # Invalid test maps for testing
└── libft/             # Custom C library
```

## 🔍 Map Validation

The game performs comprehensive map validation:

### Character Validation
- ✅ Contains all required characters (1, 0, P, C, E)
- ✅ No invalid characters
- ✅ Exactly one player and one exit
- ✅ At least one coin

### Structure Validation
- ✅ Rectangular shape (all rows same length)
- ✅ Surrounded by walls
- ✅ No empty lines

### Path Validation
- ✅ Player can reach all coins
- ✅ Player can reach exit after collecting all coins
- ✅ Uses flood fill algorithm for path finding

### Error Messages
```bash
Error
Invalid char                    # Unknown character in map
Map must contain all req. char  # Missing required elements
Duplicate player or exit        # Multiple P or E characters
Map is not a rectangle         # Inconsistent row lengths
Map is not surrounded by walls # Missing border walls
No valid path                  # Impossible to complete
Window size is too large       # Map too big for screen
```

## 🔧 Technical Details

### Libraries Used
- **MiniLibX**: Graphics library for window management and rendering
- **libft**: Custom C library with utility functions
- **ft_printf**: Custom printf implementation
- **get_next_line**: Line-by-line file reading

### Key Algorithms
- **Flood Fill**: Used for path validation to ensure map is solvable
- **Collision Detection**: Prevents player from moving into walls
- **State Management**: Tracks game state, coin count, and win conditions

### Memory Management
- Proper allocation and deallocation of map data
- Image cleanup on exit
- Protection against memory leaks

### Performance Considerations
- Tile-based rendering (42x42 pixel tiles)
- Efficient map parsing and validation
- Window size validation to prevent oversized maps

## 🐛 Debugging

### Common Issues
1. **"Error Opening file"**: Check if the map file exists and has correct permissions
2. **"Map is not a rectangle"**: Ensure all rows have the same length
3. **"No valid path"**: Make sure player can reach all coins and the exit
4. **"Window size is too large"**: Map dimensions exceed screen size
