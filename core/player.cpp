#include "player.hpp"
#include "game_state.hpp"
#include <math.h>

int proximity_color(GameState *g_state, WorldMap* map) {
    int color = 160;
    if(map->island[map->curr].initial.events.size() != 0) {
        float seg, curr;
        int col_arr[] = {231,228,228,210,210,210,198,198,198,198,198};
        int *p_pos = &(g_state->p_state.pos[g_state->d_state.mode][0]);
        int *c_pos = (map->island[map->curr].initial.events[0].pos);

        if(g_state->d_state.mode == 2 && g_state->p_state.search_mode == true) {
            seg = sqrt(ISLAND_X * ISLAND_X + ISLAND_Y * ISLAND_Y) / 11;//(sizeof(col_arr) - sizeof(col_arr[0]));
            curr = sqrt(pow(p_pos[0] - c_pos[0], 2) + pow(p_pos[1] - c_pos[1], 2));

            color = col_arr[(int)(curr / seg)];
        }
    }

    return color;
}

void scan_player_area(WorldMap *map, GameState *g_state) {
    int x, y, layer_type, mode;
    PlayerState *p = &(g_state->p_state);
    deque<array<int,3>>* game_event = &(g_state->game_event);

    mode = g_state->d_state.mode;

    x = p->pos[mode][0] - 1;
    y = p->pos[mode][1] - 1;

    // Island boundary detection
    if(mode == 2 && (x + 1 == 0 || x + 1 == ISLAND_X - 1 || y + 1 == 0 || y + 1 == ISLAND_Y - 1)) {
        game_event->push_back({x + 1, y + 1, 1});
        return;
    }

    for(int i = y; i < y + 3; i++) {
        if(i < 0 || i > p->y_max)
            continue;

        for(int j = x; j < x + 3; j++) {
            if(j < 0 || j > p->x_max)
                continue;

            layer_type = (*map->type[mode - 1])[1][i][j];
            if(layer_type == 1 || layer_type == 3) {
                game_event->push_back({j, i, 0});
            }
        }
    }
}

// Sets player's starting position on the island based on their entry point
void set_pos(GameState *g_state, int i, int j) {
    int (*pos)[2] = g_state->p_state.pos;

    // Set x coordinate
    if(pos[1][0] < i) {
        pos[2][0] = 0;
    }
    else if(pos[1][0] > i) {
        pos[2][0] = ISLAND_X - 1;
    }
    else {
        pos[2][0] = (ISLAND_X - 1) / 2;
    }

    // Set y coordinate
    if(pos[1][1] < j) {
        pos[2][1] = 0;
    }
    else if(pos[1][1] > j) {
        pos[2][1] = ISLAND_Y - 1;
    }
    else {
        pos[2][1] = (ISLAND_Y - 1) / 2;
    }
}
