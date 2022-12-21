//
// Created by ritag on 21/12/2022.
//

#ifndef PROJETO2_GRAPH_H
#define PROJETO2_GRAPH_H

#include <list>
#include <vector>
#include "Airport.h"
#include "Airline.h"

using namespace std;

class Graph {
    struct Flight {
        int destino;   // Destination node
        Airline airline; // An integer weight
    };

    struct Node {  // Os nodes correspondem a aeroportos
        list<Flight> voos; // A list de voos que sai daquele aeroporto
        Airport airport;
        bool visited;
    };

    int n;              // Graph size = numero de aeroportos
    bool hasDir=true;
    vector<Node> airports; // Lista de aeroportos

public:
    // Constructor: nr nodes and direction
    Graph(vector<Airport> airports,int number_of_airports);

    // Add flight from source to destination with a certain airline
    void addFlight(int src, int dest, Airline airline);

    // Depth-First Search: example implementation
    void dfs(int v);

    //read flights
    void read_flights(vector<Airline> airlines);
};



#endif //PROJETO2_GRAPH_H
