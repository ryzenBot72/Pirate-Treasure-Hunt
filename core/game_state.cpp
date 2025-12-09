#include "game_state.hpp"
#include "render.hpp"
#include "text.hpp"
#include "utils.hpp"
#include "game_session.hpp"

using namespace std;

//Initialise the GameState struct
void init_game_state(GameState *g_state, WorldMap *map) {
    PlayerState *p = &(g_state->p_state);
    DisplayState *d = &(g_state->d_state);

    d->mode = 1;
    d->show_map = false;

    // Reset display origin
    for(int i = 0; i < 3; i++) {
        d->disp[i][0] = 0;
        d->disp[i][1] = 0;
    }

    // Reset player position
    for(int i = 0; i < 3; i++) {
        p->pos[i][0] = 0;
        p->pos[i][1] = 0;
    }

    // --- MEMBER A: Init Stats ---
    p->isAlive = true;
    p->search_mode = false;
    p->energy = 50.0f;      // Start with full energy
    p->max_energy = 100.0f;
    p->gold = 0;             // Start with 0 gold
    p->deplete_rate[0] = 0;  // Rate of energy loss per move
    p->deplete_rate[1] = 0.5f;
    p->deplete_rate[2] = 0.01f;
    // ----------------------------

    p->total_distance = 0;
    p->x_max = DISPLAY_X;
    p->y_max = DISPLAY_Y;


//    g_state->t_state.s += "Hello!\nNext line!\nDemo demoo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo demo!";
    g_state->t_state.s += sf(" You may find something on island %d", map->clue_start);
    g_state->isActive = 2;
    g_state->proximity = 1;
    g_state->last_key = 0;
}


//changes the elements of the GameState struct as per the player key input
// Note: We are changing the signature slightly to 'int ch' based on leader's code
int state_manager(int ch, GameState *g_state, WorldMap *map, Player *player) {
    //GameState *g_state = &(curr->g_state);
    //Player *player = &(curr->player);

    DisplayState *d = &(g_state->d_state);
    PlayerState *p = &(g_state->p_state);

    int* x = &(p->pos[d->mode][0]);
    int* y = &(p->pos[d->mode][1]);
    bool moved = false;


    // --- MEMBER A: Death Check ---
    // If player is dead, don't allow movement
    if (!p->isAlive && ch != 'e' && ch != 'E') {
        return 0; 
    }
    // -----------------------------


    //For arrow keys
    if(ch == 27) {  // Escape character
        ch = getchar();  // Get the next character
        if(ch == '[') {
            ch = getchar();  // Get the actual arrow key code
            switch (ch) {
                case 'A': //Up
                    if(*y > 0 && (*map->type[d->mode - 1])[1][*y - 1][*x] >= 2) {
                        (*y)--;
                        moved = true;
                    }
                    break;
                case 'B': //Down
                    if(*y < p->y_max && (*map->type[d->mode - 1])[1][*y + 1][*x] >=  2) {
                        (*y)++;
                        moved = true;
                    }
                    break;
                case 'C': //Right
                    if(*x < p->x_max && (*map->type[d->mode - 1])[1][*y][*x + 1] >= 2) {
                        (*x)++;
                        moved = true;
                    }
                    break;
                case 'D': //Left
                    if(*x > 0 && (*map->type[d->mode - 1])[1][*y][*x - 1] >= 2) {
                        (*x)--;
                        moved = true;
                    }
                    break;
            }

            // --- MEMBER A: Energy Deduction ---
            if (moved) {
                p->energy -= p->deplete_rate[d->mode];
                p->total_distance += (p->deplete_rate[d->mode] / p->deplete_rate[1]);
                if (p->energy <= 0) {
                    p->energy = 0;
                    p->isAlive = false;
                    
                    g_state->isActive = 0;

                    string *t = &(g_state->t_state.t);
                    *t = " xxxx---- You Died! ----xxxx\n\n";
                    *t += " ------| STATS |------\n";
                    *t += sf(" Total Distance travelled : %.2f\n", g_state->p_state.total_distance);

                    build_text(g_state, map);
                    return 0;
                }
            }
            // ---------------------------------

        }
    }
    else {
        switch (ch) {
/*            case 'm':
            case 'M': {
                        //toggling show_map
                        if(d->mode == 1) {
                            d->mode = 2; // Island
                        }
                        else if (d->mode == 2){
                            d->mode = 1; // Sea
                        }
                        break;
                    }                    
*/
                      //MEMBER C ADDITION
            case 'c':
            case 'C': {
                          // Interaction Logic: Check / Collect Clue
                          if(d->mode == 2) {
                              // We are in Island View. 
                              // Logic to check if this specific island has a clue would go here.
                              // For the prototype, we display a generic message or the first clue.
                              // In a full implementation, we would cross-reference player coordinates
                              // with the WorldMap island list.
                          }
                        if(g_state->last_key == 'c') {
                            g_state->last_key = 0;
                        }
                        else{
                            g_state->last_key = 'c';
                        }


                          break;
                      }
                      // -------------------------

                      // --- MEMBER A: Inventory Access ---
            case 'i':
            case 'I': {
                        // Toggle Inventory View
                        if(g_state->last_key == 'i') {
                            g_state->last_key = 0;
                        }
                        else{
                            g_state->last_key = 'i';
                        }

                        break;
                    }
                      // ---------------------------------

            case 'p':
            case 'P': {
                        // Toggle path menu
                        if(g_state->last_key == 'p') {
                            g_state->last_key = 0;
                        }
                        else {
                            g_state->last_key = 'p';
                        }
                        break;
                      }

            case 'f':
            case 'F': {
                        // Toggle seach_mode
                        if(d->mode == 2) {
                            g_state->p_state.search_mode = !(g_state->p_state.search_mode);
                        }
                        break;
                    }

            case 'e':
            case 'E':
                      //closing the current game session
                      (g_state->isActive)--;
                      break;

            case 'y':
                      /*       
                               if(g_state->proximity == 1 && g_state->game_event.size() > 0) {
                               trigger_event(&(g_state->game_event));
                               }*/
                      break;
        }
    }

    //Trigger the event selected by the player
    if(ch >= '1' && ch <= '9') {
        if(g_state->proximity == 1 && g_state->game_event.size() > 0) {
            while(ch > '1') {
                g_state->game_event.pop_front();
                ch--;
            }
            trigger_event(g_state->game_event.front(), map, g_state, player);
        }
    }

    // Boundary checks
    if(d->mode == 1) {
        p->x_max = SEA_OVERVIEW_X - 1;
        p->y_max = SEA_OVERVIEW_Y - 1;
    }
    else if(d->mode == 2) {
        p->x_max = ISLAND_X - 1;
        p->y_max = ISLAND_Y - 1;
    }

    //Update the graph as per change in player's position
    update_graph(map, (int*)p->pos[d->mode]);

    //Clear the event deque
    while(!g_state->game_event.empty()) {
        g_state->game_event.pop_front();
    }

    //Search for events nearby player's position
    scan_player_area(map, g_state);


    //---Text related functions---//
    //Update the string containing text related to a key press
    update_key_string(g_state, map, player);

    //Clear the main string buffer
    g_state->t_state.s.clear();

    //Add the text to be printed, to the string buffer
    build_text(g_state, map);

    return 0;
}
