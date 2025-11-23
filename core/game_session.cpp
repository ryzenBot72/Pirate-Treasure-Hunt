#include "game_session.hpp"

//Initialise the GameSession struct
void init_game_session(GameSession *game) {
    init_game_state(&(game->g_state));
}
