#ifndef MEMBERD_ENGINE_H
#define MEMBERD_ENGINE_H

#include "MemberA_Player.h"
#include "MemberB_Map.h"
#include "MemberC_Clues.h"
#include <queue> // For priority_queue
#include <set>   // For visited_islands

// 
struct LeaderboardData {
    std::priority_queue<std::pair<int, std::string>> scores;
};

// This is the master struct that holds ALL game data
struct GameState {
    PlayerData       player;
    MapData          map;
    ClueData         clues;
    LeaderboardData  leaderboard;
    
    std::set<int>    visited_islands;
    int              currentPlayerLocation;
    bool             gameIsRunning;
    std::string      gameMessage; // To show results of actions
};

// --- Function Prototypes ---

// Sets up the entire game
void setupGame(GameState* state);

// The main game loop
void runGameLoop(GameState* state);

// Handles user input
void handlePlayerInput(GameState* state);

// Updates the game state after input (checks for win/loss)
void updateGame(GameState* state);

// Renders all game info to the console
void renderGame(GameState* state);

// Adds a score to the leaderboard
void addLeaderboardScore(LeaderboardData* board, int score, std::string name);

// Displays the leaderboard
void displayLeaderboard(LeaderboardData board); // Pass by copy to preserve it

#endif //MEMBERD_ENGINE_H