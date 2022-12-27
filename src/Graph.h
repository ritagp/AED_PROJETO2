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
        int dist;
    };

    int n;              // Graph size = numero de aeroportos
    bool hasDir=true;
    vector<Node> airports; // Lista de aeroportos

public:
    // Constructor: nr nodes and direction
    Graph(vector<Airport> airports,int number_of_airports);

    // Add flight from source to destination with a certain airline
    void addFlight(int src, int dest, Airline airline);

    //finds the shortest distance between a and b
    int bfs_distance(int a, int b);

    //checks if it is possible to go from v to destino
    bool dfs(int v, int destino, int distancia);

    //returns the rout between origem e destino
    vector<int> getRoute(int origem, int destino, int distancia);

    //read flights
    void read_flights(vector<Airline> airlines);

    //find airport
    int find_airport(string code);

    //how many flights leave from airport
    int number_flights(int a);


    //find less flights between city
    vector<int> fly_city(string origem, string destino, vector<string> companhias);
    //find less flights between location<
    vector<int> fly_local(string origem, string destino, int km,vector<string> companhias);
    //find less flights between airport
    vector<pair<string,string>> fly_airport(string origem, string destino, vector<string> companhias);

};



#endif //PROJETO2_GRAPH_H
