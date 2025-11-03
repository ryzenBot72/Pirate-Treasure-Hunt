#include "MemberC_Clues.h"

// Private helper function (only called from this .cpp file)
void generateClues(ClueData* clues, const std::vector<int>& clue_island_ids) {
    // This is the puzzle. Each clue is one word of the final sentence.
    std::vector<std::string> clue_words = {"The", "treasure", "is", "on", "island..."};
    
    if (clue_words.size() < clue_island_ids.size()) {
         std::cout << "CLUE ERROR: Not enough clue words!" << std::endl;
         return;
    }

    for (int i = 0; i < clue_island_ids.size(); ++i) {
        int id = clue_island_ids[i];
        clues->island_clue_database[id] = clue_words[i];
    }
    
    clues->final_master_clue = "The clues assemble! 'The treasure is on island...'\n";
    clues->final_master_clue += "  The final piece points to: Island " + std::to_string(clues->final_treasure_island_id) + "!";
}

// --- Public Function Implementations ---

void initClues(ClueData* clues, const std::vector<int>& clue_island_ids, int treasure_id) {
    clues->final_treasure_island_id = treasure_id;
    clues->total_clue_count = clue_island_ids.size();
    
    clues->island_clue_database.clear();
    clues->player_collected_clues.clear();
    clues->islands_with_clues_found.clear();

    generateClues(clues, clue_island_ids);
}

std::string getClueForIsland(ClueData* clues, int island_id) {
    // 1. Check if a clue even exists for this island
    if (clues->island_clue_database.find(island_id) == clues->island_clue_database.end()) {
        return "  You search the island, but find no new clues.";
    }

    // 2. Check if we've *already* found this clue
    if (clues->islands_with_clues_found.find(island_id) != clues->islands_with_clues_found.end()) {
        return "  You've already found the clue on this island.";
    }

    // 3. If it's a new clue, get it and store it
    std::string new_clue = clues->island_clue_database[island_id];
    
    clues->player_collected_clues.push_back(new_clue);
    clues->islands_with_clues_found.insert(island_id);

    return "  [You found a clue! It's a fragment: '" + new_clue + "']";
}

void displayCollectedClues(const ClueData* clues) {
    std::cout << "\n--- Your Collected Clues ---" << std::endl;
    if (clues->player_collected_clues.empty()) {
        std::cout << "  You haven't found any clues yet." << std::endl;
    } else {
        for (const std::string& clue : clues->player_collected_clues) {
            std::cout << "  - " << clue << std::endl;
        }
        std::cout << "  (" << clues->player_collected_clues.size() << " of " << clues->total_clue_count << " found)" << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
}

bool allCluesFound(const ClueData* clues) {
    return clues->player_collected_clues.size() == clues->total_clue_count;
}

std::string getFinalTreasureLocationClue(const ClueData* clues) {
    if (allCluesFound(clues)) {
        return clues->final_master_clue;
    }
    return "  You don't have all the pieces yet. Keep searching!";
}

int getTreasureIslandID(const ClueData* clues) {
    return clues->final_treasure_island_id;
}