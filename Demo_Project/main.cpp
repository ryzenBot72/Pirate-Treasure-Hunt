#include "MemberD_Engine.h"

int main() {
    // 1. Create the one and only GameState on the stack
    GameState myGame;
    
    // 2. Pass its address (&) to the setup function
    setupGame(&myGame);
    
    // 3. Pass its address to the main loop
    runGameLoop(&myGame);

    return 0;
}
