#include <iostream>
#include "Gestor.h"
#include "Graph.h"
using namespace std;
int main() {
    Gestor gestor;
    gestor.read_airports();
    gestor.read_airlines();
    vector<Airport> airports=gestor.getAirports();
    vector<Airline> airlines=gestor.getAirlines();
    Graph graph= Graph(airports,airports.size());
    graph.read_flights(airlines);


    return 0;
}
