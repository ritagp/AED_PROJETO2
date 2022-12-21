//
// Created by ritag on 21/12/2022.
//

#include <fstream>
#include <sstream>
#include "Graph.h"

// Constructor
Graph::Graph(vector<Airport> airports,int number_of_airports) {
    this->n=number_of_airports;
    for(int i=0;i<number_of_airports;i++){
        struct Node n={{},airports[i],false};
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
        for(int i=0;i<airports.size();i++){
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
