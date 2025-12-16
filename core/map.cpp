#include <cstdlib>
#include <ctime>
#include <math.h>
#include <queue>
#include <climits> // for INT_MAX
#include <string>
#include <algorithm> //for reverse()

#include "map.hpp"
#include "utils.hpp"
//#include "game_state.hpp"

using namespace std;

// --- MEMBER B: GRAPH & DIJKSTRA UTILITIES ---

// Calculate distance between two points
int calculate_distance(int *a, int *b) {
    int dx, dy;

    dx = abs(a[0] - b[0]);
    dy = abs(a[1] - b[1]);

//    if(dx != 0) dx--;
//    if(dy != 0) dy--;

    return (dx + dy);

    //return (abs(a[0] - b[0]) + abs(a[1] - b[1]));
}


/*
   addConnection:
   --------------
   Adds a two-way (undirected) connection between island A and B.
   'cost' represents how hard or long the journey is.
   Used only inside buildMap or whenever the map is expanded.
*/
void addConnection(Graph *g, int A, int B, int cost) {
    g->adj[A].push_back({B, cost});
    g->adj[B].push_back({A, cost});
}

// Function to build the graph (Adjacency List)
void create_graph(WorldMap* map) {
    map->g.adj.clear(); //empty map
    map->g.I = map->island.size();

    // Connect every island to every other island if they are within a certain range
    // This creates a 'Mesh' graph structure
    for (int i = 0; i < map->g.I; i++) {
        for (int j = i + 1; j < map->g.I; j++) {
            int cost = calculate_distance(map->island[i].coords, map->island[j].coords) - 8;
            /*if(cost < 0) {
                cost = 0;
            }*/
    
            // Member B: Adding Weighted Edges (Weight = Distance)
            addConnection(&(map->g), i, j, cost);
        }
        addConnection(&(map->g), i, map->g.I, INT_MAX);
    }
}


void update_graph(WorldMap *map, int *pos) {
    int p = map->g.I;
    int cost;

    for(int i = 0; i < p; i++) {
        cost = calculate_distance(map->island[i].coords, pos) - 8;
        /*if(cost < 0) {
            cost = 0;
        }*/

        map->g.adj[i][p - 1] = {p, cost};
        map->g.adj[p][i] = {i, cost};
    }
}


// Member B: Dijkstra's Algorithm Implementation
// Finds the shortest path from start_node to end_node
Path run_Dijkstra (WorldMap* map, int start, int target){
    Path p;
    vector<int> parent(map->g.I + 1, -1);

    vector<int> dist(map->g.I + 1, INT_MAX);        // shortest known cost to each island
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    // Start node distance is 0
    dist[start] = 0;                        
    pq.push({0, start}); // begin from the starting island

    while (!pq.empty()) {
        int cost = pq.top().first;      
        int u    = pq.top().second; // current best island to process
        
        p.cost = cost;
        pq.pop();

        if(u == target) // reached destination; shortest path found
            break;

        if(cost > dist[u]) // ignore outdated entries
            continue;

        for(const auto& p : map->g.adj.at(u)) { // explore all neighbors of island u
            int v = p.first;               // neighbor island ID
            int w = p.second;              // travel cost to that island
            if(w < 0) { 
                w = 0;
            }
            
            if(dist[u] + w < dist[v]) {    // found a cheaper path
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});     // push updated cost
                parent[v] = u;
            }
        }
    }

    if(dist[target] == INT_MAX) {
        return {INT_MAX, {}};
    }

    int current_node = target;
    while(current_node != -1) {
        p.path.push_back(current_node);
        current_node = parent[current_node];
    }
    reverse(p.path.begin(), p.path.end());
    
    //p.cost += 8;

    return p;
}

// MEMBER C: CLUE INITIALIZATION

string build_clue_text(WorldMap *map, int pos) {
    return {};
}


void init_clues(WorldMap *map) {
    // Member C: Using an Array of strings to store riddle data
/*    string clues_db[] = {
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
    }*/
    srand(time(0));

    Events ev;
    vector<int> arr = {0,1,2,3,4};
    int curr, prev = -1;

    for(size_t i = 0; i < map->island.size(); i++) {
        
        curr = rand() % arr.size(); //random index for arr
        
        if(i == 0) {
            map->clue_start = arr[curr];
        }
        
        ev.type = 1;
        ev.clueData.id = i;
        ev.clueData.isFound = false;
        ev.clueData.island_id = arr[curr];
        ev.pos[0] = rand() % (ISLAND_X - 9) + 4;
        ev.pos[1] = rand() % (ISLAND_Y - 9) + 4;
        
        map->island[arr[curr]].initial.events.push_back(ev);

        if(prev != -1) {
            map->island[prev].initial.events[0].clueData.riddle = sf("Go to %d", arr[curr]);
        }

        prev = arr[curr];

        arr.erase(arr.begin() + curr);
    }
    map->clue_end = prev;
    map->island[prev].initial.events[0].type = 2;
    map->island[prev].initial.events[0].clueData.riddle = "You unlocked the Treasure!\n";
}

void init_items(WorldMap *map) {
    srand(time(0));

    Item it;

    do {
        it.pos[0] = rand() % (ISLAND_Y - 9) + 4;
        it.pos[1] = rand() % (ISLAND_Y - 9) + 4;
    } while(it.pos[1] == map->island[map->clue_start].initial.events[0].pos[1]);

    it.name = "search";
    map->island[map->clue_start].initial.items.push_back(it);
}



int random_tile(int type) {
    int tile[2][5] = {{27, 27, 21, 21, 21}, {240, 76, 220, 112, 112}};
    return tile[type - 1][(int)sqrt(rand() % 25)];
}

float closest_island_distance(WorldMap *map, int x, int y) {
    float min_dist = ISLAND_X + ISLAND_Y;
    float dist;
    
    for(size_t k = 0; k < map->island.size(); k++) {
        dist = sqrt(pow(x - map->island[k].coords[0], 2) + pow(y - map->island[k].coords[1], 2));
        if(dist < min_dist)
            min_dist = dist;
    }

    return min_dist;
}

int sea_col(WorldMap *map, int x, int y) {
    float dist = closest_island_distance(map, x, y);

    if(dist < 1.5) {
        return 51;
    }
    if(dist >= 1.5 && dist < 2.8) {
        return 45;
    }
    else if(dist >= 2.8 && dist < 3.9) {
        return 39;
    }
    else if(dist >= 3.9 && dist < 4.6) {
        return 33;
    }
    else if(dist >= 4.6 && dist < 5.4) {
        return 27;
    }
    else if(dist >= 5.4 && dist < 6.1){
        return 27;
    }
    else {
        return random_tile(1);
        //return 21;
    }
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
    //For the layer map, 
    //0 = can't move, can't interact
    //1 = can't move, can interact
    //2 = can move, can't interact
    //3 = can move, can interact


    /*------------SEA_OVERVIEW-------------*/
    //water
    srand(time(0));
    for(int i = 0; i < SEA_OVERVIEW_Y; i++) {
        for(int j = 0; j < SEA_OVERVIEW_X; j++) {
            //map->sea_overview[0][i][j] = random_tile(1);
            map->sea_overview[0][i][j] = sea_col(map, j, i);
            map->sea_overview[1][i][j] = 2;
        }
    }

    //islands
    for(size_t i = 0; i < map->island.size(); i++) {
        int x = map->island[i].coords[0];
        int y = map->island[i].coords[1];
        map->sea_overview[0][y][x] = 40; //Green
        map->sea_overview[1][y][x] = 1;
    }
    /*-------------------------------------*/

    /*-----------ISLAND_NORMAL------------*/
    //land
    for(int i = 0; i < ISLAND_Y; i++) {
        for(int j = 0; j < ISLAND_X; j++) {
            map->island_normal[0][i][j] = random_tile(2);
            if(map->island_normal[0][i][j] == 240) {
                map->island_normal[1][i][j] = 1;
            }
            else {
                map->island_normal[1][i][j] = 2;
            }
        }

    }
    /*-------------------------------------*/
}

void init_map_vector(WorldMap *map) {
    map->type.push_back(&(map->sea_overview));
    map->type.push_back(&(map->island_canvas));
}

int find_island(WorldMap *map, int x, int y) {
    for(int i = 0; i < (int)map->island.size(); i++) {
        if(map->island[i].coords[0] == x && map->island[i].coords[1] == y)
            return map->island[i].id;
    }

    return -1;
}

// --- master map initialisation function ---
void init_map(WorldMap *map) {
    generate_islands(map->island, 5); // Create Islands
    create_graph(map);                // Member B: Build Graph
    init_clues(map);                  // Member C: Populate Clues
    init_items(map);
    init_matrix(map);                 // Render setup
    init_map_vector(map);           // Map type pointers
}

void build_canvas(WorldMap *map, int id) {
    int i,j; 

    // Copy the island template onto the island canvas
    for(i = 0; i < ISLAND_Y; i++) {
        for(j = 0; j < ISLAND_X; j++) {
            map->island_canvas[0][i][j] = map->island_normal[0][i][j];
            map->island_canvas[1][i][j] = map->island_normal[1][i][j];
        }
    }

    srand(time(0));
    //Generate random coordinates
    j = rand() % ISLAND_X;
    i = rand() % ISLAND_Y;
    //Place the energy booster onto the above generated coordinates
    map->island_canvas[0][i][j] = 164;
    map->island_canvas[1][i][j] = 3;

    //Place the clue onto the island
    if(map->island[id].initial.events.size() != 0) {
        j = map->island[id].initial.events[0].pos[0];
        i = map->island[id].initial.events[0].pos[1];

        if(map->island[id].initial.events[0].clueData.isFound == true) {
            map->island_canvas[0][i][j] = 53;
        }
        else {
            map->island_canvas[0][i][j] = 240;//29 earlier (dark green)
        }
        map->island_canvas[1][i][j] = 1;
    }

    if(map->island[id].initial.items.size() != 0) {
        j = map->island[id].initial.items[0].pos[0];
        i = map->island[id].initial.items[0].pos[1];

        map->island_canvas[0][i][j] = 220;
        map->island_canvas[1][i][j] = 3;
    }
}
