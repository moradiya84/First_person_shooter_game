# First Person Shooter (ASCII Version) 🎯

### *A simple yet thrilling ASCII shooter adventure...* 

You wake up in a cold, dark corridor. The air is still, but you hear faint noises in the distance. You don’t remember how you got here, but one thing is certain—**you need to get out**. The walls are closing in, and danger could be around any corner. **Will you escape or be trapped forever?**

## Features 🚀
- **ASCII-based 3D world** using ray-casting
- **Smooth player movement** (`WASD` controls)
- **Collision detection** to prevent walking through walls
- **Dynamic shading & depth effects** for better visuals
- **Optimized frame rate** for smooth gameplay

## Controls 🎮
| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Look left |
| `D` | Look right |

## How to Play ▶️
1. **Clone the repository**  
   ```sh
   git clone https://github.com/moradiya84/First_person_shooter_game.git
   cd First_person_shooter_game
   ```
2. **Compile the game (Windows only)**  
   ```sh
   g++ First_Person_Shooter.cpp -o FPS_Game -static -std=c++17 -mwindows
   ```
3. **Run the game**  
   ```sh
   FPS_Game.exe
   ```

## Game Environment 🏚️
The game world is a **16x16 grid**, representing an old abandoned facility. Walls (`#`) block your way, and open paths (`.`) let you move around. **Be careful—something might be lurking in the dark...**

Example Map:
```
################
#..............#
#..............#
#...##.........#
#..............#
#.......#####..#
#.......#####..#
#.......#####..#
#..............#
#....#.........#
#..............#
################
```

## Future Plans ✨
- **Add shooting mechanics 🔫** – Defend yourself!
- **Enemy AI 🤖** – Something is watching...
- **ASCII textures 🎨** – Improve the environment
- **Minimap 🗺️** – See where you're going

## License 📜
This project is **open-source**. Feel free to modify and improve it! 🚀

---
**Created by Om Moradiya**
