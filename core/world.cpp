#include "world.hpp"
#include "render.hpp"
//#include "player.hpp"

using namespace std;

int main_loop(unique_ptr<World>& w) {
    GameSession* curr_game = &(w->game[0]);

    printf("\x1b[H;\x1b[J");    // Clears the entire screen
    render(w);
    while(curr_game->g_state.isActive != 0) {
        state_manager(getchar(), &(curr_game->g_state), &(w->map), &(curr_game->player));
        render(w);
    }

    return 0;
}
