#include "text.hpp"
#include "utils.hpp"    //for sf();

void update_key_string(GameState *g_state, WorldMap *map, Player *player) {
    string *t = &(g_state->t_state.t);

    t->clear();     //Clear the key text string

    // Initialise the text string as per the key pressed
    switch(g_state->last_key) {
        case 0:
                break;

        case 'i': {
                *t += "\n **** INVENTORY ****\n\n";
                *t += sf(" Energy : %.2f / %.2f\n", g_state->p_state.energy, g_state->p_state.max_energy);
                //*t += sf(" Gold : %d\n", g_state->p_state.gold);

                break;
            }

        case 'c' : {
                vector<Clue>& clues = (player->inventory.collected_clues);

                *t += "\n **** CLUES ****\n\n";
                *t += "     From | \n";
                *t += "-------------------------------------------------\n";
                *t += sf("    Start | You may find something on island %d\n", map->clue_start);
                for(size_t i = 0; i < clues.size(); i++) {
                    *t += sf(" Island %d | ", clues[i].island_id);
                    
                    if(clues[i].isFound == true) {
                        *t += "You've found the treasure, but don't have all the keys to open it!";
                    }
                    else {
                        *t += clues[i].riddle;
                    }
                    *t += "\n";
                }
                break;
            }

        case 'p': 
            if(g_state->d_state.mode == 1){
                Path p;
                int length;

                *t += "\n Following are the available paths:\n";
 
                *t += sf(" To | Cost | Path\n");
                for(int i = 0; i < map->g.I; i++) {
                    p = run_Dijkstra(map, map->g.I, i);
                    length = (int)p.path.size();

                    if(p.cost > 0) {
                        p.cost += 8;
                    }
                    else {
                        p.cost += (map->g.adj[p.path[length - 2]][p.path[length - 1]]).second + 8;
                    }
                    
                    *t += sf(" %2d | %4d | ", i, p.cost);
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

    array<int,3> event_info; 

    s->clear();

    //Key info bar
    *s += "\x1b[48;5;17m";
    *s += sf("%3d%3d", g_state->p_state.pos[g_state->d_state.mode][0], g_state->p_state.pos[g_state->d_state.mode][1]);
//    *s += sf("%3d", g_state->game_event.size());
    *s += sf("%8.2f", g_state->p_state.energy);
//    *s += sf(" %d ", (int)(map->island[map->curr].initial.events.size()));
    *s += sf(" | ");
    if(g_state->d_state.mode == 1) {
        *s += "\x1b[38;5;75m";
        *s += sf("Ocean");
    }
    else if(g_state->d_state.mode == 2) {
        *s += "\x1b[38;5;220m";
        *s += sf("Island %d", map->curr);
    }
    *s += "\x1b[38;5;255m";
    *s += "\n";
    *s += "\x1b[48;5;233m";

    if(g_state->isActive == 0) {
        *s = g_state->t_state.r;
        *s += g_state->t_state.t;
        return;
    }

    // Search mode
    if(g_state->p_state.search_mode == true) {
        int arr[] = {198,210,228,231};

        *s += " SEARCH MODE\n";
        *s += "\n         Player  icon\n";
        *s += "         ";
        for(int i = 0; i < 4; i++) {
            *s += sf("\x1b[48;5;%dm", arr[i]);
            *s += sf("%3c", ' ');
        }
        *s += "\x1b[48;5;233m\n";
        *s += " Farther <----------> Closer\n\n";
        *s += " \x1b[48;5;160m";
        *s += sf("%3c", ' ');
        *s += "\x1b[48;5;233m";
        *s += " (normal color) means there is nothing to search here\n\n";
    }



    if(!g_state->t_state.r.empty()) {
        *s += g_state->t_state.r;
        g_state->t_state.r.clear();
    }

    //Event detection text
    if(g_state->game_event.size() != 0) {
        deque<array<int,3>> temp = g_state->game_event;
        event_info = g_state->game_event.front();

        if(g_state->d_state.mode == 1) {
            *s += "\n Do you want to explore?\n";
        }
        else if (g_state->d_state.mode == 2) {
            if(event_info[2] == 1) {    
                *s += "\n Exit?\n";
            }
            else {
                *s += "\n Examine?\n";
            }
        }

        for(int i = 1; !temp.empty(); i++) {
            *s += sf(" %i\n", i);
            temp.pop_front();
        }
    }

    //Other text generated due to key press
    if(!g_state->t_state.t.empty()) {
        *s += g_state->t_state.t;
    }
}
