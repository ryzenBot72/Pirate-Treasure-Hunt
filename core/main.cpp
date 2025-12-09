#include <memory>

//#include "saves.hpp" //contains the structs to strore save file data
#include "utils.hpp"
#include "world.hpp"

int main() {
    //Saves s;
    //load_saves(&s); //function to load the save game files(world name/id, player name/id)

    set_raw_input_mode(); //enable non-canonical mode
    
    auto w1 = make_unique<World>();

    w1->name = "First world";
    init_map(&(w1->map));

    (w1->game).push_back(GameSession());
    init_game_session(&(w1->game[0]), &(w1->map));

    main_loop(w1);

    reset_input_mode(); //restore canonical mode
    return 0;
}
