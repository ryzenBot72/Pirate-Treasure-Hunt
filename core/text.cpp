#include "text.hpp"
#include "utils.hpp"    //for sf();

void update_key_string(GameState *g_state, WorldMap *map) {
    string *t = &(g_state->t_state.t);

    t->clear();     //Clear the key text string

    // Initialise the text string as per the key pressed
    switch(g_state->last_key) {
        case 0:
                break;

        case 'i': {
                *t += "\n **** INVENTORY ****\n\n";
                *t += sf(" Energy : %.2f / %.2f\n", g_state->p_state.energy, g_state->p_state.max_energy);
                *t += sf(" Gold : %d\n", g_state->p_state.gold);

                break;
            }

        case 'p': 
            if(g_state->d_state.mode == 1){
                Path p;
                int length;

                *t += "\n Following are the availabe paths:\n";
                for(int i = 0; i < map->g.I; i++) {
                    p = run_Dijkstra(map, map->g.I, i);
                    length = (int)p.path.size();

                    *t += sf(" %2d,%-2d | ", p.cost, length);
                    for(int j = 1; j < length - 1; j++) {
                        *t += sf("%d -> ", p.path[j]);
                    }
                    *t += sf("%d", p.path[length - 1]);
                    *t += "\n";
                }
                g_state->last_key = 'p';
            }
            break;
    }
}

void build_text(GameState *g_state, WorldMap *map) {
    string *s = &(g_state->t_state.s);

    s->clear();

    //Key info bar
    *s += sf("%3d%3d", g_state->p_state.pos[g_state->d_state.mode][0], g_state->p_state.pos[g_state->d_state.mode][1]);
    *s += sf("%3d", g_state->game_event.size());
    *s += sf("%8.2f\n", g_state->p_state.energy);

    //Event detection text
    if(g_state->game_event.size() != 0) {
        queue<array<int,2>> temp = g_state->game_event;

        if(g_state->d_state.mode == 1) {
            *s += "\nDo you want to explore?\n";
        }
        else if (g_state->d_state.mode == 2) {
            *s += "\nExamine?\n";
        }

        for(int i = 1; !temp.empty(); i++) {
            *s += sf("%i\n", i);
            temp.pop();
        }
    }

    //Other text generated due to key press
    if(!g_state->t_state.t.empty()) {
        *s += g_state->t_state.t;
    }
}
