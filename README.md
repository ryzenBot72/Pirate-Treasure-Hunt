# Pirate Treasure Hunt

A terminal-based pirate adventure where you explore seas and islands, collect clues, and hunt for hidden treasure.

<hr>

## Gameplay

- You play as a pirate captain exploring a world made up of seas and islands.
- Move around the map using the arrow keys.
- Travel across the sea to discover islands and land on them to explore.
- On islands, search for hidden clues and items.
- Collected clues and items are stored in your inventory.
- Plan routes between islands and track paths while sailing.
- The goal is to find all the clues and unlock the final treasure.

---

## How to run:

#### If you have make installed, then:

```
make
./game
```

#### If not, then: 
1. Paste the following to compile : *(may take a few seconds)*

```
g++ -std=c++14 -Wall -g -lm -Icore/include core/game_session.cpp core/game_state.cpp core/main.cpp core/map.cpp core/player.cpp core/render.cpp core/text.cpp core/utils.cpp core/world.cpp -o ./game

```

followed by

```
./game
```

### **NOTE!**<br>
- C++14 or higher version required (supported by most of the devices).
- In case the display appears glitched, zoom out the terminal window until all of the content fits at once.

<hr>

## Current key bindings:

|          FUNCTION |  KEY                            |
|------------------:|:--------------------------------|
|           Move Up |  Up arrow                       |
|         Move Down |  Down arrow                     |
|         Move Left |  Left arrow                     |
|        Move Right |  Right arrow                    |
|          Interact |  Numbers (1 - 9)                |
|Toggle search mode |  f / F (only in Island view)    |
|             Paths |  p / P (only in Sea view)       |
|             Clues |  c / C                          |
|         Inventory |  i / I                          |
|             Close |  e / E (press twice to exit)    |

<hr>

## Future Additions Planned

- Restore player progress using a save and load system
- Introduce enemy ships with combat mechanics
- Add dynamic sea events such as storms and hazards that can cause energy loss
- Reward victories with bonus energy, coins, and items
- Introduce basic mini-games (e.g., unscramble the word) to acquire clues
- Enhance the user interface using the Simple and Fast Multimedia Library (SFML)