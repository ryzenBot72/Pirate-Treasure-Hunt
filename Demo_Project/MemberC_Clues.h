#ifndef MEMBERC_CLUES_H
#define MEMBERC_CLUES_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

// This struct holds all data for the clue system.
struct ClueData {
    // 
    std::unordered_map<int, std::string> island_clue_database;
    std::vector<std::string> player_collected_clues;
    
    // 
    std::set<int> islands_with_clues_found;
    
    int total_clue_count;
    int final_treasure_island_id;
    std::string final_master_clue;
};

// --- Function Prototypes ---

// Initializes the clue system
void initClues(ClueData* clues, const std::vector<int>& clue_island_ids, int treasure_id);

// Called by Member D when the player lands on an island
std::string getClueForIsland(ClueData* clues, int island_id);

// Called by Member D to show the player their clue inventory
void displayCollectedClues(const ClueData* clues);

// Called by Member D to check for the win condition
bool allCluesFound(const ClueData* clues);

// Returns the final clue text
std::string getFinalTreasureLocationClue(const ClueData* clues);

// Returns the final island ID
int getTreasureIslandID(const ClueData* clues);

#endif //MEMBERC_CLUES_H