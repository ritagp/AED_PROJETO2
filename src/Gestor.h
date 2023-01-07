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
        /// Default construtor.
        Gestor();
        /// Reads the contents of the file "airlines.csv" and place them in a vector.
        void read_airlines();
        /// Reads the contents of the file "airports.csv" and place them in a vector.
        /// \param graph
        void read_airports(Graph& graph);
        /// Getter.
        /// \return Unordered set containing airlines
        unordered_set<Airline, AirlineHash> getAirlines();

    private:
        unordered_set<Airline, AirlineHash>  airlines;
};


#endif //PROJETO2_GESTOR_H
