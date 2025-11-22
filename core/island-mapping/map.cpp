#include "map.hpp"
#include <iostream>
#include <queue>
#include <climits>
using namespace std;

void buildMap(Graph& g) {
    g.adj.clear(); //empty map
    g.I = 5;
    g.adj[0]; //Home Island
    g.adj[1]; //
    g.adj[2]; //
    g.adj[3]; //
    g.adj[4]; //Treasure Island

    for(int i = 0; i< g.I-1; i++)
        addConnection(g, i, i+1, 5); //connections to adjacent islands 0-1, 1-2, 2-3, 3-4
    
    for(int i = 0; i<g.I-2; i++)
        addConnection(g, i, i+2, 12); //connections to farther islands 0-2, 1-3, 2-4

    for(int i = 0; i<g.I-3; i++)
        addConnection(g, i, i+3, 25); //connections to farthest islands 0-3, 1-4
}

void addConnection(Graph& g, int A, int B, int cost) {
    g.adj[A].push_back({B, cost});
    g.adj[B].push_back({A, cost});
}

vector<pair<int,int>> getNeighbors(const Graph& g, int island) {
    if(g.adj.find(island) != g.adj.end())
        return g.adj.at(island);
    return {};
}

void exploreBFS(const Graph& g, int start) {
    queue<int> Q;
    vector<bool> vis(g.I, false);

    vis[start] = true;
    Q.push(start);

    while(!Q.empty()){
        int u = Q.front();
        Q.pop();

        cout << u << " ";

        for(auto& v : g.adj.at(u)){
            int next = v.first;
            if(!vis[next]){
                vis[next] = true;
                Q.push(next);
            }
        }
    }

    cout << endl;
}

void dfsHelper(const Graph& g, int start, vector<bool> &vis){
    cout << start << " ";
    vis[start] = true;

    for(auto& p : g.adj.at(start)){
        int next = p.first;
        if(!vis[next])
            dfsHelper(g, next, vis);
    }
}

void exploreDFS(const Graph& g, int start) {
    vector<bool> vis(g.I, false);

    dfsHelper(g, start, vis);
}

int runDijkstra(const Graph& g, int start, int target) {
    vector<int> dist(g.I, INT_MAX);        // shortest known cost to each island
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq; 

    dist[start] = 0;                        
    pq.push({0, start}); // begin from the starting island

    while(!pq.empty()) {
        int cost = pq.top().first;     
        int u    = pq.top().second; // current best island to process
        pq.pop();

        if(u == target) // reached destination — shortest path found
            return cost;

        if(cost > dist[u]) // ignore outdated entries
            continue;

        for(const auto& p : g.adj.at(u)) { // explore all neighbors of island u
            int v = p.first;               // neighbor island ID
            int w = p.second;              // travel cost to that island

            if(dist[u] + w < dist[v]) {    // found a cheaper path
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});     // push updated cost
            }
        }
    }
    return -1;
}

// void displayMap(const Graph& g) {
    
// }

int main(){
    Graph g;
    buildMap(g);
    exploreBFS(g, 0);
    exploreDFS(g, 0);
    cout << runDijkstra(g, 0, 4) << endl;
    return 0;
}
