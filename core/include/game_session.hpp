#ifndef GAME_SESSION_HPP
#define GAME_SESSION_HPP

#include "player.hpp"
#include "game_state.hpp"

using namespace std;

typedef struct GameSession {
    int id;
    string name;            //name of the game session/player
    Player player;          //data associated with the player(inventory, abilities)
    GameState g_state;      //States of all the entities of the game
} GameSession;

#endif

