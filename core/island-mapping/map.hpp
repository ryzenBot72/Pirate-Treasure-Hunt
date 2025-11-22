#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

/*
   Graph Structure:
   ----------------
   adj : Adjacency list storing connections between islands.
         Each island (int) maps to a list of (neighbor, cost) pairs.
         Cost represents travel difficulty/distance between islands.

   I   : Total number of islands in the game.
*/
struct Graph {
    unordered_map<int, vector<pair<int,int>>> adj;
    int I; //number of islands
};

/*
   buildMap:
   ---------
   Initializes the game world.
   Creates all islands and defines their connections with weights.
   This function is called once at the start of the game.
*/
void buildMap(Graph& g);

/*
   addConnection:
   --------------
   Adds a two-way (undirected) connection between island A and B.
   'cost' represents how hard or long the journey is.
   Used only inside buildMap or whenever the map is expanded.
*/
void addConnection(Graph& g, int A, int B, int cost);

/*
   getNeighbors:
   --------------
   Returns all connected islands from a given island.
   Useful for movement, pathfinding, or displaying available routes.
*/
vector<pair<int,int>> getNeighbors(const Graph& g, int island);

/*
   exploreBFS:
   -----------
   Used to verify that the entire map is connected (reachable from start).
   Ensures there are no isolated islands in the game world.
*/
void exploreBFS(const Graph& g, int start);

/*
   exploreDFS:
   -----------
   Also helps verify connectivity of the graph.
   Ensures all islands can be reached through some sequence of paths.
*/
void exploreDFS(const Graph& g, int start);

/*
   runDijkstra:
   ------------
   Computes the minimum travel cost between 'start' and 'target' islands.
   Core algorithm for suggesting the shortest or least expensive path.
   Returns the total minimum cost (or -1 if no path exists).
*/
int runDijkstra(const Graph& g, int start, int target);

// // Debug print
// void displayMap(const Graph& g);