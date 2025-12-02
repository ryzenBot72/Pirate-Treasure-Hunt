#include <queue>
#include "game_session.hpp"

//Initialise the GameSession struct
void init_game_session(GameSession *game) {
    init_game_state(&(game->g_state));
}

void trigger_event(array<int,2> coords, WorldMap *map, GameState *g_state) {
    int mode = g_state->d_state.mode;
    int x = coords[0];
    int y = coords[1];
    int layer = (*map->type[mode - 1])[1][y][x];

    if(mode == 1 && layer == 1) {
        for(long unsigned int i = 0; i < map->island.size(); i++) {     //Traverse throught list of islands
            if(map->island[i].coords[0] == x && map->island[i].coords[1] == y) {    //Match the event coordinates with island coordinates. If matched, we found the island, and thus its data
                g_state->d_state.mode = 2;                
            }
        }
    }
    else if(mode == 2 && layer == 1) {
                
    }
}
