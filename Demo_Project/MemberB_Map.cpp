#include "MemberB_Map.h" 
#include <queue>   // For std::priority_queue (Dijkstra)
#include <limits>  // For std::numeric_limits (infinity)

void initMap(MapData* map, int total_islands) {
    map->num_islands = total_islands;
    map->graph.clear(); 
    map->island_names.clear();
}

void addRoute(MapData* map, int islandA, int islandB, int energy_cost) {
    map->graph[islandA].push_back({islandB, energy_cost});
    map->graph[islandB].push_back({islandA, energy_cost});
}

void setIslandName(MapData* map, int islandID, std::string name) {
    map->island_names[islandID] = name;
}

std::string getIslandName(const MapData* map, int islandID) {
    if (map->island_names.find(islandID) != map->island_names.end()) {
        return map->island_names.at(islandID);
    }
    return "Unknown Island";
}

std::vector<std::pair<int, int>> getNeighbors(const MapData* map, int islandID) {
    auto it = map->graph.find(islandID);
    if (it == map->graph.end()) {
        return {}; 
    }
    return it->second; 
}

void displayMap(const MapData* map) {
    std::cout << "\n--- Island Map ---" << std::endl;
    for (int i = 1; i <= map->num_islands; ++i) {
        std::cout << "  Island " << i << " (" << getIslandName(map, i) << ") -> ";
        auto neighbors = getNeighbors(map, i);
        if (neighbors.empty()) {
            std::cout << "[No routes]";
        } else {
            for (const auto& edge : neighbors) {
                std::cout << "[To " << edge.first << " (Cost: " << edge.second << ")] ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "------------------" << std::endl;
}

// Runs Dijkstra's Algorithm
int getShortestPath(const MapData* map, int startID, int endID) {
    // 
    std::priority_queue<std::pair<int, int>, 
                        std::vector<std::pair<int, int>>, 
                        std::greater<std::pair<int, int>>> pq;

    int max_dist = std::numeric_limits<int>::max();
    std::vector<int> dist(map->num_islands + 1, max_dist); 

    dist[startID] = 0;
    pq.push({0, startID}); // {cost, node}

    while (!pq.empty()) {
        int current_cost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (u == endID) {
            return current_cost;
        }
        if (current_cost > dist[u]) {
            continue;
        }

        auto neighbors = getNeighbors(map, u);
        for (const auto& edge : neighbors) {
            int v = edge.first;
            int weight = edge.second;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return -1; 
}