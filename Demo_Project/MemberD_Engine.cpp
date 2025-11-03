#include "MemberD_Engine.h"
#include <iostream>
#include <limits> // For clearing cin buffer

// Helper function to clear the console
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Sets up the entire game
void setupGame(GameState* state) {
    // --- Member A Setup ---
    initPlayer(&state->player, 100, 10); // Start with 100 energy, 10 gold

    // --- Member B Setup ---
    const int TOTAL_ISLANDS = 6;
    initMap(&state->map, TOTAL_ISLANDS);
    
    // Set up a hardcoded map
    setIslandName(&state->map, 1, "Base Island (Start)");
    setIslandName(&state->map, 2, "Whispering Isles");
    setIslandName(&state->map, 3, "Sharkfin Bay");
    setIslandName(&state->map, 4, "Smuggler's Cove");
    setIslandName(&state->map, 5, "Dead Man's Atoll");
    setIslandName(&state->map, 6, "TREASURE ISLAND");

    addRoute(&state->map, 1, 2, 10); // Base -> Whispering (Cost 10)
    addRoute(&state->map, 1, 3, 15); // Base -> Sharkfin (Cost 15)
    addRoute(&state->map, 2, 3, 20); // Whispering -> Sharkfin (Cost 20)
    addRoute(&state->map, 2, 4, 10); // Whispering -> Smuggler's
    addRoute(&state->map, 3, 5, 10); // Sharkfin -> Dead Man's
    addRoute(&state->map, 4, 5, 15); // Smuggler's -> Dead Man's
    addRoute(&state->map, 5, 6, 25); // Dead Man's -> TREASURE (High cost)
    addRoute(&state->map, 4, 6, 50); // Smuggler's -> TREASURE (High cost)

    // --- Member C Setup ---
    std::vector<int> clue_islands = {2, 4, 5}; // Clues are on islands 2, 4, 5
    int treasure_island_id = 6;
    initClues(&state->clues, clue_islands, treasure_island_id);

    // --- Member D Setup ---
    state->currentPlayerLocation = 1; // Start at Base Island
    state->visited_islands.insert(1);
    state->gameIsRunning = true;
    state->gameMessage = "Welcome to Pirate Treasure Hunt!";
    
    // Add dummy scores
    addLeaderboardScore(&state->leaderboard, 150, "Blackbeard");
    addLeaderboardScore(&state->leaderboard, 100, "Calico Jack");
}

// The main game loop
void runGameLoop(GameState* state) {
    while (state->gameIsRunning) {
        renderGame(state);
        handlePlayerInput(state);
        updateGame(state);
    }
    
    // Game Over
    clearScreen();
    std::cout << "============================\n";
    std::cout << "        GAME OVER\n";
    std::cout << "============================\n\n";
    std::cout << state->gameMessage << std::endl;
    
    // Add final score
    int finalScore = getEnergy(&state->player) + state->player.gold * 10;
    std::cout << "Your final score: " << finalScore << std::endl << std::endl;
    addLeaderboardScore(&state->leaderboard, finalScore, "You");
    
    displayLeaderboard(state->leaderboard);
}

// Renders all game info to the console
void renderGame(GameState* state) {
    clearScreen();
    std::cout << "============================================================\n";
    std::cout << "  Location: " << getIslandName(&state->map, state->currentPlayerLocation);
    std::cout << "  (Island " << state->currentPlayerLocation << ")" << std::endl;
    std::cout << "  Energy: " << getEnergy(&state->player) << "   Gold: " << state->player.gold << std::endl;
    std::cout << "------------------------------------------------------------\n";
    
    // Display the last action's result
    if (!state->gameMessage.empty()) {
        std::cout << state->gameMessage << std::endl;
        std::cout << "------------------------------------------------------------\n";
        state->gameMessage = ""; // Clear message after showing it
    }

    // Show available routes
    std::cout << "  Available Routes:\n";
    auto neighbors = getNeighbors(&state->map, state->currentPlayerLocation);
    if (neighbors.empty()) {
        std::cout << "  You are stranded!\n";
    } else {
        int i = 1;
        for (const auto& edge : neighbors) {
            std::cout << "    " << i << ". Sail to " << getIslandName(&state->map, edge.first);
            std::cout << " (Cost: " << edge.second << " Energy)\n";
            i++;
        }
    }
    std::cout << "\n  --- Other Actions --- \n";
    std::cout << "    i. Show Inventory\n";
    std::cout << "    c. Show Collected Clues\n";
    std::cout << "    m. Show Full Map (DEBUG)\n";
    std::cout << "    q. Quit Game\n";
    std::cout << "============================================================\n";
    std::cout << "Enter your choice (1-" << neighbors.size() << ", i, c, m, q): ";
}

// Handles user input
void handlePlayerInput(GameState* state) {
    char choice;
    std::cin >> choice;
    
    auto neighbors = getNeighbors(&state->map, state->currentPlayerLocation);

    // Check for numeric choice (1-9)
    if (choice >= '1' && choice <= '9') {
        int move_choice = choice - '0'; // Convert char '1' to int 1
        if (move_choice > 0 && move_choice <= neighbors.size()) {
            auto& route = neighbors[move_choice - 1];
            int dest_island = route.first;
            int cost = route.second;

            if (getEnergy(&state->player) >= cost) {
                deductEnergy(&state->player, cost);
                state->currentPlayerLocation = dest_island;
                state->visited_islands.insert(dest_island);
                state->gameMessage = "Sailing... you arrived at " + getIslandName(&state->map, dest_island) + ".";
                
                // Check for clues (Member C)
                state->gameMessage += "\n" + getClueForIsland(&state->clues, dest_island);

            } else {
                state->gameMessage = "Not enough energy to sail there!";
            }
            return;
        }
    }

    // Check for char choice
    switch (choice) {
        case 'i':
            displayInventory(&state->player);
            break;
        case 'c':
            displayCollectedClues(&state->clues);
            break;
        case 'm':
            displayMap(&state->map);
            break;
        case 'q':
            state->gameIsRunning = false;
            state->gameMessage = "You decided to end your adventure.";
            return;
        default:
            state->gameMessage = "Invalid choice, try again.";
            break;
    }
    
    // Pause screen if we displayed info (inventory, clues, map)
    if (choice == 'i' || choice == 'c' || choice == 'm') {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}

// Updates the game state after input (checks for win/loss)
void updateGame(GameState* state) {
    if (!state->gameIsRunning) return; // Don't update if we just quit

    if (!isPlayerAlive(&state->player)) {
        state->gameIsRunning = false;
        state->gameMessage = "You ran out of energy! Your hunt is over.";
        return;
    }

    // Check for win condition
    if (state->currentPlayerLocation == getTreasureIslandID(&state->clues)) {
        if (allCluesFound(&state->clues)) {
            state->gameIsRunning = false;
            state->gameMessage = "You found it! You've discovered the legendary treasure!";
        } else {
            state->gameMessage = "You found the treasure island, but you don't have all the clues!\n";
            state->gameMessage += "  You can't seem to figure out how to open the final chest.";
        }
    }
}

// Adds a score to the leaderboard
void addLeaderboardScore(LeaderboardData* board, int score, std::string name) {
    board->scores.push({score, name});
}

// Displays the leaderboard
void displayLeaderboard(LeaderboardData board) {
    std::cout << "--- All-Time Leaderboard ---" << std::endl;
    int rank = 1;
    while (!board.scores.empty() && rank <= 5) {
        auto top = board.scores.top();
        std::cout << "  " << rank << ". " << top.second << " - " << top.first << " points\n";
        board.scores.pop();
        rank++;
    }
    std::cout << "----------------------------" << std::endl;
}