#ifndef MEMBERA_PLAYER_H
#define MEMBERA_PLAYER_H

#include <iostream>
#include <string>
#include <vector>

// This struct holds all data for the player.
struct PlayerData {
    int energy;
    int gold;
    std::vector<std::string> inventory;
};

// --- Function Prototypes ---

// Initializes the player's starting stats
void initPlayer(PlayerData* player, int startEnergy, int startGold);

// Deducts energy (can be negative to add energy)
void deductEnergy(PlayerData* player, int amount);

// Adds an item (e.g., "key", "shovel") to the inventory
void addItem(PlayerData* player, std::string item_name);

// Checks if the player has a specific item
bool hasItem(const PlayerData* player, std::string item_name);

// Prints the player's current inventory to the console
void displayInventory(const PlayerData* player);

// Returns the player's current energy
int getEnergy(const PlayerData* player);

// Checks if the player is still alive
bool isPlayerAlive(const PlayerData* player);

#endif //MEMBERA_PLAYER_H