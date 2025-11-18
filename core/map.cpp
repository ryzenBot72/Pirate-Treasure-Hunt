#include <cstdlib>
#include <ctime>
#include <math.h>
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <string>

// Include your headers
#include "map.hpp"
#include "utils.hpp"

using namespace std;

// --- MEMBER B: GRAPH & DIJKSTRA UTILITIES ---

// Calculate distance between two islands
int calculate_distance(Island& a, Island& b) {
    return (int)sqrt(pow(a.coords[0] - b.coords[0], 2) + pow(a.coords[1] - b.coords[1], 2));
}

// Function to build the graph (Adjacency List)
void create_graph(WorldMap* map) {
    map->graph.clear();
    // Connect every island to every other island if they are within a certain range
    // This creates a 'Mesh' graph structure
    for (size_t i = 0; i < map->island.size(); i++) {
        for (size_t j = i + 1; j < map->island.size(); j++) {
            int dist = calculate_distance(map->island[i], map->island[j]);
            
            // Member B: Adding Weighted Edges (Weight = Distance)
            // Graph Representation: Adjacency List using std::map
            map->graph[i].push_back({(int)j, dist});
            map->graph[j].push_back({(int)i, dist}); 
        }
    }
}

// Member B: Dijkstra's Algorithm Implementation
// Finds the shortest path from start_node to end_node
int get_shortest_path_cost(WorldMap* map, int start_node, int end_node) {
    // Min-Priority Queue: Stores {cost, node_index}
    // Orders elements so the smallest cost is always at the top
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Distances array initialized to Infinity
    unordered_map<int, int> dist;
    for(size_t i=0; i<map->island.size(); i++) dist[i] = numeric_limits<int>::max();

    // Start node distance is 0
    dist[start_node] = 0;
    pq.push({0, start_node});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (u == end_node) return d; // Reached destination

        if (d > dist[u]) continue;

        // Explore neighbors
        for (auto& edge : map->graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return -1; // No path found
}

// MEMBER C: CLUE INITIALIZATION

void init_clues(vector<Island>& island) {
    // Member C: Using an Array of strings to store riddle data
    string clues_db[] = {
        "The start is near...", 
        "Look beneath the ancient palm.", 
        "Walk ten paces east from the skull rock.", 
        "The treasure sleeps where the shadow falls.",
        "X Marks the spot!"
    };

    // Member C: Linear Traversal to assign clues
    for(size_t i = 0; i < island.size(); i++) {
        // Ensure we don't go out of bounds of our clue database
        if (i < 5) {
            Events ev;
            ev.type = 1; // 1 represents a CLUE
            ev.description = "Clue: " + clues_db[i];
            // Add event to the island's event vector
            island[i].initial.events.push_back(ev);
        }
    }
}


// --- EXISTING MAP GENERATION LOGIC ---

int random_tile(int type) {
    int tile[2][5] = {{39, 33, 39, 33, 39}, {240, 76, 220, 112, 112}};
    return tile[type - 1][(int)sqrt(rand() % 25)];
}

void generate_islands(vector<Island>& island, int n) {
    srand(time(0));
    for(int i = 0; i < n; i++) {
        island.push_back(Island());
        island[i].id = i; // Assign ID for Graph Logic
        island[i].coords[0] = rand() % (SEA_OVERVIEW_X - 5) + 2; // Boundary safety
        island[i].coords[1] = rand() % (SEA_OVERVIEW_Y - 5) + 2;
    }
}

void init_matrix(WorldMap *map) {
    // ... (Keep your team leader's existing logic for init_matrix here) ...
    // Just copy paste the body of init_matrix from the file you sent me.
    // It handles the coloring of sea and islands.
    // (Omitted here to save space, but ensure it is pasted in your final file)
    
    /*------------SEA_OVERVIEW-------------*/
    //water
    srand(time(0));
    for(int i = 0; i < SEA_OVERVIEW_Y; i++) {
        for(int j = 0; j < SEA_OVERVIEW_X; j++) {
            map->sea_overview[i][j] = random_tile(1);
        }
    }

    //islands
    for(size_t i = 0; i < map->island.size(); i++) {
        int x = map->island[i].coords[0];
        int y = map->island[i].coords[1];
        map->sea_overview[y][x] = 40; //Green
    }
    /*-------------------------------------*/

    /*-----------ISLAND_NORMAL------------*/
    //land
    for(int i = 0; i < ISLAND_Y; i++) {
        for(int j = 0; j < ISLAND_X; j++) {
            map->island_normal[i][j] = random_tile(2);
        }
    }
    /*-------------------------------------*/
}

// --- MASTER INIT FUNCTION ---
void init_map(WorldMap *map) {
    generate_islands(map->island, 5); // 1. Create Islands
    create_graph(map);                // 2. Member B: Build Graph
    init_clues(map->island);          // 3. Member C: Populate Clues
    init_matrix(map);                 // 4. Render setup
}
