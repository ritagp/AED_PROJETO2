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
     /// Default constructor.
     Graph();
     /// Setter.
     /// \param a An airport
     void setAirport(Airport a);
     /// Reads flights.
     /// \param airlines The airlines
    void read_flights(unordered_set<Airline,AirlineHash> airlines);
    bool find_city(string city);
    /// Add a flight from a certain source to a certain destination performed by a certain airline.
    /// \param src Source
    /// \param dest Destination
    /// \param airline Airline
    void addFlight(int src, int dest, Airline airline);
    //find airport
    /// Find a specific airport.
    /// \param code Code of the wanted airport
    /// \return An integer with the position of that airport in the vector that is stored
    int find_airport(string code);
    /// The number of flights that leave from a certain airport.
    /// \param a The index of the airport.
    /// \return The number of flights.
    int number_flights(int a);
    ///
    /// \param u Source
    /// \param d Destination
    /// \param path
    /// \param path_index
    /// \param min
    /// \param route
    /// \param result
    /// \param companhias Airlines permitted by the user
    /// \param one Wether it wants all the fastest alternatives or just one
    void getAllPathsUtil(int u, int d, int *path, int &path_index,int min, vector<int> &route, vector<vector<int>> &result, vector<string> &companhias, bool one);
    ///
    /// \param s Source
    /// \param d Destination
    /// \param min
    /// \param companhias Airlines permitted by the user
    /// \param one
    /// \return Wether it wants all the fastest alternatives or just one
    vector<vector<int>> getAllPaths(int s, int d, int min, vector<string> &companhias, bool one);

    /// Finds the fastest option to travel through cities
    /// \param origem Source
    /// \param destino Destination
    /// \param companhias Airlines permitted by the user
    /// \param one Wether it wants all the fastest alternatives or just one
    /// \return The fastest option
    vector<vector<vector<string>>> fly_city(std::string origem, std::string destino, vector<std::string> companhias, bool one);
    //find less flights between location<
    /// Finds the fastest option to travel between locations
    /// \param lat_ori Latitude of the source
    /// \param long_ori Longitude of the source
    /// \param lat_dest Latitute of the destination
    /// \param long_dest Longitude of the destination
    /// \param km Max distance that the airports can be from the locations given
    /// \param companhias Airlines permitted by the user
    /// \param one Wether it wants all the fastest alternatives or just one
    /// \return The fastest option
    vector<vector<vector<string>>>fly_local(string lat_ori, string long_ori, string lat_dest, string long_dest, int km, vector<std::string> companhias, bool one);
    //find less flights between airport
    /// Finds the fastest option between airports given by the user.
    /// \param origem Source
    /// \param destino Destination
    /// \param companhias Airlines permitted by the user
    /// \param one Wether it wants all the fastest alternatives or just one
    /// \return The fastest option
    vector<vector<string>> fly_airport(string origem, string destino, vector<string> &companhias, bool one);
    /// Calculates the distance between two points.
    /// \param a Airport a
    /// \param b Airport b
    /// \return Distance between a and b
    int bfs_distance(int a, int b);
    /// Converter.
    /// \param diff Number in degrees
    /// \return The conversion to radius
    double degToRad(double diff);
    ///
    /// \param lat1 Latitude of the first point.
    /// \param long1 Longitude of the first point
    /// \param lat2 Latitude of the second point
    /// \param long2 Longitude of the second point
    /// \return The distance in kms between two locations
    double getDistanceKms(double lat1, double long1, double lat2, double long2);

    //Infos:
    /// Displays some informations about a certain airport.
    /// \param a An airport
    void getAirportInfo(int a);
    ///
    /// \param flights
    /// \return Number of destinies that you can get to with a certain airline
    int countDestinies(list<Flight> flights);
    ///
    /// \param flights
    /// \return Number of countries that you can go to with a certain airline
    int countCountries(list<Flight> flights);
    /// Getter.
    /// \param flights
    /// \return Unordered set containing airlines
    unordered_set<string> getAirlines(list<Flight> flights);

};



#endif //PROJETO2_GRAPH_H
