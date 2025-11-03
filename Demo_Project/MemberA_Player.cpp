#include "MemberA_Player.h"
#include <algorithm> // For std::find

// Initializes the player's starting stats
void initPlayer(PlayerData* player, int startEnergy, int startGold) {
    player->energy = startEnergy;
    player->gold = startGold;
    player->inventory.clear(); 
}

// Deducts energy (can be negative to add energy)
void deductEnergy(PlayerData* player, int amount) {
    player->energy -= amount;
    if (player->energy < 0) {
        player->energy = 0; 
    }
}

// Adds an item to the inventory
void addItem(PlayerData* player, std::string item_name) {
    player->inventory.push_back(item_name);
    std::cout << "  [You picked up: " << item_name << "]" << std::endl;
}

// Checks if the player has a specific item
bool hasItem(const PlayerData* player, std::string item_name) {
    auto it = std::find(player->inventory.begin(), player->inventory.end(), item_name);
    return (it != player->inventory.end());
}

// Prints the player's current inventory to the console
void displayInventory(const PlayerData* player) {
    std::cout << "\n--- Your Inventory ---" << std::endl;
    if (player->inventory.empty()) {
        std::cout << "  Your inventory is empty." << std::endl;
    } else {
        for (const std::string& item : player->inventory) {
            std::cout << "  - " << item << std::endl;
        }
    }
    std::cout << "----------------------" << std::endl;
}

// Returns the player's current energy
int getEnergy(const PlayerData* player) {
    return player->energy;
}

// Checks if the player is still alive
bool isPlayerAlive(const PlayerData* player) {
    return (player->energy > 0);
}