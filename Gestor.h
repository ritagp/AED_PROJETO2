//
// Created by ritag on 21/12/2022.
//

#ifndef PROJETO2_GESTOR_H
#define PROJETO2_GESTOR_H


#include <vector>
#include "Airport.h"
#include "Airline.h"

class Gestor {
    public:
        Gestor();
        void read_airlines();
        void read_airports();
        vector<Airport> getAirports();
        vector<Airline> getAirlines();

    private:
        vector<Airport> airports;
        vector<Airline> airlines;
};


#endif //PROJETO2_GESTOR_H
