#include "world.hpp"
#include "render.hpp"

using namespace std;

int main_loop(unique_ptr<World>& w) {
    GameSession* curr_game = &(w->game[0]);

    render(w);
    while(curr_game->g_state.isActive != 0) {
        state_manager(getchar(), &(curr_game->g_state));
        render(w);
    }

    return 0;
}
