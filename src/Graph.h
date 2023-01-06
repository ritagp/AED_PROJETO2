//
// Created by ritag on 21/12/2022.
//

#ifndef PROJETO2_GRAPH_H
#define PROJETO2_GRAPH_H

#include <list>
#include <vector>
#include <unordered_set>
#include <set>
#include <stack>
#include "Airport.h"
#include "Airline.h"

using namespace std;

class Graph {

    struct Flight {
        int destino;   // Destination node
        unordered_set<Airline, AirlineHash> airlines; // An integer weight

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
     Graph();
     void setAirport(Airport a);
     //read flights
    void read_flights(unordered_set<Airline,AirlineHash> airlines);
    // Add flight from source to destination with a certain airline
    void addFlight(int src, int dest, Airline airline);
    //find airport
    int find_airport(string code);
    //how many flights leave from airport
    int number_flights(int a);

    void getAllPathsUtil(int u, int d, int *path, int &path_index,int min, vector<int> &route, vector<vector<int>> &result, vector<string> companhias, bool one);
    vector<vector<int>> getAllPaths(int s, int d, int min, vector<string> companhias, bool one);

    //find less flights between city
    vector<vector<vector<string>>>fly_city(std::string origem, std::string destino, vector<std::string> companhias, bool one);
    //find less flights between location<
    vector<vector<vector<string>>>fly_local(string lat_ori, string long_ori, string lat_dest, string long_dest, int km, vector<std::string> companhias, bool one);
    //find less flights between airport
    vector<vector<string>> fly_airport(string origem, string destino, vector<string> &companhias, bool one);


    int bfs_distance(int a, int b);
    double degToRad(double diff);
    double getDistanceKms(double lat1, double long1, double lat2, double long2);

    //Infos:
    void getAirportInfo(int a);
    int countDestinies(list<Flight> flights);
    int countCountries(list<Flight> flights);
    unordered_set<string> getAirlines(list<Flight> flights);

};



#endif //PROJETO2_GRAPH_H
