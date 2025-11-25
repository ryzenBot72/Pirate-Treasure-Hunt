#ifndef GAME_SESSION_HPP
#define GAME_SESSION_HPP

#include <string>
#include "player.hpp"
#include "game_state.hpp"

using namespace std;

typedef struct GameSession {
    int id;
    string name;            //name of the game session/player
    Player player;          //data associated with the player(inventory, abilities)
    GameState g_state;      //States of all the entities of the game
} GameSession;


void init_game_session(GameSession *game);

void trigger_event(array<int,2> coords, WorldMap *map, GameState *g_state);

#endif

