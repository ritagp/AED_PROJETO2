//
// Created by ritag on 21/12/2022.
//

#include "Gestor.h"
#include "Airport.h"
#include "Airline.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

Gestor::Gestor() {
    airports={};
    airlines={};
}

void Gestor::read_airports() {
    ifstream in_airplanes("airports.csv");
    //remove the first line
    string fst_line;
    vector<string> data;
    getline(in_airplanes, fst_line);

    //create all different airports and placing them in the vector airports
    for (string line; getline(in_airplanes, line);) {
        string info;
        std::stringstream iss(line);
        while (getline(iss, info, ',')) {
            data.push_back(info);
        }
        Airport airport = *new Airport(data[0], data[1], data[2], data[3], data[4], data[5]);
        airports.push_back(airport);
        data.clear();
    }
}

void Gestor::read_airlines() {
    ifstream in_airlines("airlines.csv");
    //remove the first line
    string fst_line;
    vector<string> data;
    getline(in_airlines, fst_line);

    //create all different airlines and placing them in the vector airlines
    for (string line; getline(in_airlines, line);) {
        string info;
        std::stringstream iss(line);
        while (getline(iss, info, ',')) {
            data.push_back(info);
        }
        Airline airline = *new Airline(data[0], data[1], data[2], data[3]);
        airlines.push_back(airline);
        data.clear();
    }
}

vector<Airport> Gestor::getAirports() {
    return this->airports;
}

vector<Airline> Gestor::getAirlines() {
    return this->airlines;
}