//
// Created by ritag on 21/12/2022.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include "Graph.h"

// Constructor
Graph::Graph(vector<Airport> airports,int number_of_airports) {
    struct Node zero= {{},Airport("","","","","",""),false,-1};
    this->airports.push_back(zero);
    this->n=number_of_airports;
    for(int i=0;i<number_of_airports;i++){
        struct Node n={{},airports[i],false,-1};
        this->airports.push_back(n);
    }
}

// Add a flight from source to destination with a certain airline
void Graph::addFlight(int src, int dest, Airline airline) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    airports[src].voos.push_back({dest, airline});
}

// Depth-First Search: example implementation
void Graph::dfs(int v) {
    // show node order
    // cout << v << " ";
    airports[v].visited = true;
    for (auto e : airports[v].voos) {
        int w = e.destino;
        if (!airports[w].visited)
            dfs(w);
    }
}

void Graph :: bfs( int v) {
    for ( int v=1; v<=n; v++) airports[v].visited = false ;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    airports[v].visited = true ;
    while (!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front (); q.pop (); // remove first element of q
        for (auto e : airports[u].voos) {
            int w = e.destino;
            if (!airports[w].visited) { // new node!
                q.push(w);
                airports[w]. visited = true;
            }
        }
    }
}


vector<int> Graph::bfs_distance(int a, int b) {
    vector<int> result;
    for (int i=1; i<=n; i++) {
        airports[i].visited = false;
        airports[i].dist = -1;
    }

    bool found = false;
    queue<int> q;
    q.push(a);
    airports[a].visited = true;
    airports[a].dist = 0;
    result.push_back(a);
    while (!q.empty()) {
        if(found) break;
        int u = q.front(); q.pop();
        for (auto e : airports[u].voos) {
            int w = e.destino;
            if (!airports[w].visited) {
                q.push(w);
                airports[w].visited = true;
                airports[w].dist = airports[u].dist + 1;
                if(airports[result.back()].dist < airports[w].dist) result.push_back(w);
                if (w == b){found = true; break;}
            }
            else{
                if(airports[w].dist > airports[u].dist + 1){ airports[w].dist = airports[u].dist + 1; }
            }
        }
    }
    return result;
}

void Graph::read_flights(vector<Airline> airlines) {
    ifstream in_flights("flights.csv");
    //remove the first line
    string fst_line;
    vector<string> data;
    getline(in_flights, fst_line);

    //create all flights adding them to the graph
    for (string line; getline(in_flights, line);) {
        string info;
        std::stringstream iss(line);
        while (getline(iss, info, ',')) {
            data.push_back(info);
        }
        int src=0;
        int dest=0;
        for(int i=1;i<airports.size();i++){
            if(airports[i].airport.getCode()==data[0])
                src=i;
            if(airports[i].airport.getCode()==data[1])
                dest=i;
        }
        Airline a= Airline("","","","");
        for(int i=0;i<airlines.size();i++){
            if(airlines[i].getCode()==data[2]) a=airlines[i];
        }
        addFlight(src,dest,a);
        data.clear();
    }
}

int Graph::find_airport(std::string code) {
    for( Node n:airports){
        n.visited=false;
    }
    for (int v=1;v<airports.size();v++){
        if(airports[v].airport.getCode()==code) return v;
    }
    return 0;
}

int Graph::number_flights(int a) {
    return airports[a].voos.size();
}

vector<pair<string,string>> Graph::fly_airport(std::string origem, std::string destino, vector<std::string> companhias) {
    vector<pair<string,string>> route;
    int o=0;
    int d=0;
    for(int i=1;i<airports.size();i++){
        if(airports[i].airport.getCode()==origem) o=i;
        if(airports[i].airport.getCode()==destino) d=i;
    }
    vector<int> way= bfs_distance(o,d);
    for(int i=0;i<way.size();i++){
        route.push_back({airports[way[i]].airport.getCode(),airports[way[i]].airport.getName()});
    }

    return route;
}

vector<int> Graph::fly_city(std::string origem, std::string destino, vector<std::string> companhias) {

}

vector<int> Graph::fly_local(std::string origem, std::string destino, int km, vector<std::string> companhias) {


}
