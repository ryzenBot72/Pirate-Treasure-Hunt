#include "world.hpp"
#include "render.hpp"
//#include "player.hpp"

using namespace std;

int main_loop(unique_ptr<World>& w) {
    GameSession* curr_game = &(w->game[0]);

    render(w);
    while(curr_game->g_state.isActive != 0) {
        /*while(!(curr_game->g_state.game_event.empty())) {
            curr_game->g_state.game_event.pop();
        }*/
        //state_manager(getchar(), &(curr_game->g_state), &(w->map), &(curr_game->player));
        state_manager(getchar(), &(curr_game->g_state), &(w->map), &(curr_game->player));
        render(w);

    }

    return 0;
}
