#ifndef ISLAND_HPP
#define ISLAND_HPP

#include <vector>

using namespace std;

typedef struct Events {
    //event type, all the relevent data
} Events;

typedef struct Items {
    //type of item, associated data 
} Items;

typedef struct IslandStuff {
    vector<Events> events;  //challenges, direct hints
    vector<Items> items;    //random items (along with their position maybe?)
} IslandStuff;

typedef struct Island {
    int id;
    int coords[2];          //x,y coordinates of the island
    IslandStuff initial;
} Island;

#endif

