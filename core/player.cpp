#include "player.hpp"
#include "game_state.hpp"

void scan_player_area(WorldMap *map, GameState *g_state) {
    int x, y, layer_type, mode;
    PlayerState *p = &(g_state->p_state);
    queue<array<int,2>>* game_event = &(g_state->game_event);

    mode = g_state->d_state.mode;

    x = p->pos[mode][0] - 1;
    y = p->pos[mode][1] - 1;

    /*
       if(x > 0 && x < p->x_max) {
       x = p->pos[mode][0] - 1;
       }*/
    //game_event->push(10);
    for(int i = y; i < y + 3; i++) {
        if(i < 0 || i > p->y_max)
            continue;

        for(int j = x; j < x + 3; j++) {
            if(j < 0 || j > p->x_max)
                continue;

            layer_type = (*map->type[mode - 1])[1][i][j];
            if(layer_type == 1 || layer_type == 3) {
                //game_event->push(10);
                /*if(mode == 1) {
                    game_event->push(110);
                }
                else if(mode == 2) {
                    if(layer_type == 1)
                        game_event->push(10, );
                    else if(layer_type == 3)
                        game_event->push(30);
                }*/
                game_event->push({j,i});
            }
        }
    }
}
