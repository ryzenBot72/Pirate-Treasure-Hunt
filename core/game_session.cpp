#include <queue>
#include "game_session.hpp"
#include "game_state.hpp"
//#include "player.hpp"
#include <ctime>

//Initialise the GameSession struct
void init_game_session(GameSession *game, WorldMap *map) {
    init_game_state(&(game->g_state), map);
}

void trigger_event(array<int,3> event_info, WorldMap *map, GameState *g_state, Player *player) {
    int mode = g_state->d_state.mode;
    int x = event_info[0];
    int y = event_info[1];
    int type = event_info[2];
    int layer = (*map->type[mode - 1])[1][y][x];
    int color[] = {112,220};

    srand(time(0));
    if(mode == 1 && layer == 1) {
        for(long unsigned int i = 0; i < map->island.size(); i++) {     //Traverse throught list of islands
            if(map->island[i].coords[0] == x && map->island[i].coords[1] == y) {    //Match the event coordinates with island coordinates. If matched, we found the island, and thus its data
                map->curr = i;
                g_state->d_state.mode = 2;
                set_pos(g_state, x, y);
                build_canvas(map, i);
            }
        }
    }
    else if(mode == 2 && layer == 1) {
        int i, j;
        vector<Events>& ev = (map->island[map->curr].initial.events);

        j = ev[0].pos[0];
        i = ev[0].pos[1];
        if(i == y && j == x) {
            if(ev[0].type == 2 && player->inventory.collected_clues.size() == 4) {
                g_state->t_state.r = ev[0].clueData.riddle;
                g_state->isActive = 0;
            }
            else {
                player->inventory.collected_clues.push_back(ev[0].clueData);
                g_state->t_state.r = ev[0].clueData.riddle;
                map->island_canvas[0][i][j] = 220;
                map->island_canvas[1][i][j] = 2;

                map->island_normal[0][i][j] = 220;
                map->island_normal[1][i][j] = 2;
                ev.erase(ev.begin() + 0);
            }
        }
    }
    else if(mode == 2 && layer == 3) {
        g_state->t_state.r = " Picked Energy Booster!\n Energy++\n\n";
        
        map->island_canvas[0][y][x] = color[rand() % 2];
        map->island_canvas[1][y][x] = 2;

        map->island_normal[0][y][x] = color[rand() % 2];
        map->island_normal[1][y][x] = 2;

        g_state->p_state.energy += 10;

    }
    else if(mode == 2 && type == 1) {
        g_state->d_state.mode = 1;
        g_state->p_state.search_mode = false;
    }
}
