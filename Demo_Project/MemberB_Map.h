#ifndef MEMBERB_MAP_H
#define MEMBERB_MAP_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility> // For std::pair

// This struct holds the map (graph) data
struct MapData {
    // The Graph (Adjacency List)
    // 
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
    
    // Stores a name for each island ID
    std::unordered_map<int, std::string> island_names;
    
    int num_islands; 
};

// --- Function Prototypes ---

// Sets up the map with the total number of islands
void initMap(MapData* map, int total_islands);

// Adds a two-way route between islands with a specific energy cost
void addRoute(MapData* map, int islandA, int islandB, int energy_cost);

// Sets the name for an island
void setIslandName(MapData* map, int islandID, std::string name);

// Gets the name of an island
std::string getIslandName(const MapData* map, int islandID);

// Gets a list of neighbors for a given island (for Member D)
std::vector<std::pair<int, int>> getNeighbors(const MapData* map, int islandID);

// Runs Dijkstra's Algorithm to find the *cost* of the shortest path
int getShortestPath(const MapData* map, int startID, int endID);

// Displays the map connections in the console (for debugging)
void displayMap(const MapData* map);

#endif //MEMBERB_MAP_H