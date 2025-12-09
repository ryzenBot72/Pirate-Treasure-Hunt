# Pirate Treasure Hunt
<!-- <br> -->
<hr>

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
- May **not** compile for some devices.
- In case the display appears glitched, zoom out the terminal window until all of the content fits at once.

<hr>

## Current key bindings:

|          FUNCTION |  KEY                            |
|------------------:|:--------------------------------|
|           Move Up |  Up arrow                       |
|         Move Down |  Down arrow                     |
|         Move Left |  Left arrow                     |
|        Move Right |  Right arrow                    |
|          Interact |  Numbers (0 - 9)                |
|Toggle search mode |  f / F (only in Island view)    |
|             Paths |  p / P (only in Sea view)       |
|             Clues |  c / C                          |
|         Inventory |  i / I                          |
|             Close |  e / E (press twice to exit)    |
