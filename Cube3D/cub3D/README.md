# cub3D - My first RayCaster with miniLibX

*This project has been created as part of the 42 curriculum by `sam`.*

## Description

**cub3D** is a 3D graphics project that implements a ray-casting engine inspired by Wolfenstein 3D, the first-person shooter from 1992. The goal is to create a "realistic" 3D graphical representation of the inside of a maze from a first-person perspective using ray-casting principles.

This project covers:
- Ray-casting algorithm implementation
- Window management with miniLibX
- Texture mapping on walls
- Dynamic view rendering with variable colors
- Real-time keyboard input handling
- Map parsing from `.cub` configuration files

## Features

### Mandatory Part
- ✅ Ray-casting engine rendering 3D maze from first-person perspective
- ✅ Window management with smooth transitions
- ✅ Wall texture display (North, South, East, West faces)
- ✅ Floor and ceiling color settings
- ✅ Keyboard controls:
  - **Arrow Left/Right**: Look left/right
  - **W/A/S/D**: Move forward/left/backward/right
  - **ESC**: Close and exit cleanly
  - **Window X button**: Close and exit cleanly
- ✅ Map parsing from `.cub` files with validation
- ✅ Player spawn position and orientation (N/S/E/W)

### Bonus Features (Optional)
- Wall collision detection
- Minimap system
- Doors (open/close mechanics)
- Animated sprites  
- Mouse rotation controls

## Instructions

### Compilation

```bash
make              # Compile the project
make clean        # Remove object files
make fclean       # Remove object files and executable
make re           # Recompile from scratch
```

### Running

```bash
./cub3D maps/example.cub
```

The program requires a valid `.cub` map file as a command-line argument.

### Map File Format (*.cub)

The `.cub` file must contain:

**Textures (in any order):**
```
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture
```

**Colors (in any order):**
```
F 220,100,0      # Floor color (R,G,B)
C 225,30,0       # Ceiling color (R,G,B)
```

**Map (must be last):**
- `0` = empty space
- `1` = wall
- `N/S/E/W` = player spawn position and direction

Example:
```
111111
100101
101001
1100N1
111111
```

## Technical Details

- **Language**: C (C99 standard)
- **Graphics Library**: miniLibX
- **Compilation Flags**: `-Wall -Wextra -Werror`
- **Math Library**: `-lm` (mathematics functions)
- **Window Resolution**: 1920x1080 (customizable)
- **Field of View (FOV)**: 66 degrees
- **Ray-Casting Method**: DDA (Digital Differential Analyzer) algorithm

## Resources

### Ray-Casting References
- [Ray-Casting 101](https://en.wikipedia.org/wiki/Ray_casting)
- [Wolfenstein 3D Ray-Casting Explanation](https://en.wikipedia.org/wiki/Wolfenstein_3D#Legacy)
- [Game Engine Black Book - Wolfenstein 3D](https://fabiensanglard.net/gebbwolf3d/)

### miniLibX Documentation
- [miniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx/overview.html)
- [miniLibX Events](https://harm-smits.github.io/42docs/libs/minilibx/events.html)

### Mathematics
- DDA (Digital Differential Analyzer) algorithm for ray-casting
- Trigonometry for angle calculations and perspective projection

## AI Usage

AI was used to:
1. **Code structure organization**: Helped design modular file organization and function decomposition
2. **Debugging**: Assisted in identifying common ray-casting mathematical issues
3. **Documentation**: Generated initial framework for comments and function signatures
4. **Algorithm reference**: Provided pseudocode for DDA and other ray-casting implementations

All code has been reviewed, understood, and manually implemented with custom logic and optimizations.

## Evaluation

This project is evaluated on:
1. **Functionality**: Proper rendering and controls
2. **Code Quality**: Norm compliance, memory management, no leaks
3. **Robustness**: Proper error handling and edge cases
4. **Bonus Implementation**: Additional features beyond mandatory requirements

Good luck! 🎮
