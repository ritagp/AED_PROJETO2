//
// Created by ritag on 21/12/2022.
//

#ifndef PROJETO2_GESTOR_H
#define PROJETO2_GESTOR_H


#include <vector>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

class Gestor {
    public:
        Gestor();
        void read_airlines();
        void read_airports(Graph& graph);
        unordered_set<Airline, AirlineHash> getAirlines();

    private:
        unordered_set<Airline, AirlineHash>  airlines;
};


#endif //PROJETO2_GESTOR_H
