#ifndef MAP_HPP
#define MAP_HPP

#include <stack>
#include <unordered_map>
#include "island.hpp"

using namespace std;

#define SEA_OVERVIEW_X 60
#define SEA_OVERVIEW_Y 40
#define ISLAND_X 60
#define ISLAND_Y 40

/*
   Graph Structure:

   adj : Adjacency list storing connections between islands.
         Each island (int) maps to a list of (neighbor, cost) pairs.
         Cost represents travel difficulty/distance between islands.

   I : Total number of islands in the game.
*/
typedef struct Graph {
    unordered_map<int, vector<pair<int,int>>> adj;
    int I;
}Graph;

typedef struct Path {
    int cost;
    vector<int> path;
}Path;

typedef struct WorldMap {
    int curr;
    int clue_start;
    int clue_end;
    Graph g;            //(change the type as per your implementation; this is just a placeholder); graph that represents the connections/relations between the islands.
    //map<int, vector<vector<int>>> graph;
    vector<Island> island;  //vector for islands; contains every possible parameter to set-up that island(coordinates, challenges, hints, random items, etc)

    vector<vector<vector<vector<int>>>*> type;

    vector<vector<vector<int>>> sea_overview{2, vector<vector<int>>{SEA_OVERVIEW_Y, vector<int>(SEA_OVERVIEW_X, 0)}};
    
    vector<vector<vector<int>>> island_normal{2, vector<vector<int>>{ISLAND_Y, vector<int>(ISLAND_X, 0)}};

    vector<vector<vector<int>>> island_canvas{2, vector<vector<int>>{ISLAND_Y, vector<int>(ISLAND_X, 0)}};

} WorldMap;

int calculate_distance(int *a, int *b);
void addConnection(Graph *g, int A, int B, int cost);
void update_graph(WorldMap *map, int *pos);
Path run_Dijkstra(WorldMap *map, int start, int target);

void generate_islands(vector<Island>& island, int n);                //function to randomly generate position co-ordinates for n islands. -(almost done, needs some refinement)
void create_graph(int pos[][2]);             //given a 2-d array containing (x,y) co-ordinates of all islands, form a graph to represent connections between the islands.
void init_islands(vector<Island>& island);   //initialising the parameters for each islands
void get_all_within_distance_k();            //function to fetch all islands connected to current island and are at a given distance
                                        //add more functions as per requirement
void init_clues(WorldMap *map);
void init_map(WorldMap *map);
void init_map_vector(WorldMap *map);

int find_island(WorldMap *map, int x, int y);

void build_canvas(WorldMap *map, int id);
#endif

