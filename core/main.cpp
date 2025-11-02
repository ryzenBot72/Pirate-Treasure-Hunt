//#include <saves.hpp> //contains the structs to strore save file data
#include "utils.hpp"
#include "world.hpp"
#include "render.hpp"

int main() {
    //Saves s;
    //load_saves(&s); //function to load the save game files(world name/id, player name/id)

    //intro_loop();
    set_raw_input_mode(); //enable non-canonical mode

    World w1;

    w1.name = "First world";
    init_map(&(w1.map));

    (w1.game).push_back(GameSession());
    init_game_session(&(w1.game[0]));

    render(&w1);
    while((w1.game[0]).g_state.isActive != 0) {
        state_manager(getchar(), &(w1.game[0].g_state));
        render(&w1);
    }

    reset_input_mode(); //restore canonical mode
    return 0;
}
