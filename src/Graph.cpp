//
// Created by ritag on 21/12/2022.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include "Graph.h"

// Constructor
Graph::Graph(vector<Airport> airports,int number_of_airports) {
    struct Node zero= {{},Airport("","","","","",""),false,-1};
    this->airports.push_back(zero);
    this->n=number_of_airports;
    for(int i=0;i<number_of_airports;i++){
        struct Node n={{},airports[i],false,-1};
        this->airports.push_back(n);
    }
}


// Add a flight from source to destination with a certain airline
void Graph::addFlight(int src, int dest, Airline airline) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    airports[src].voos.push_back({dest, airline});
}


//ckecks to see if it is possible to find destiny, starting in v
bool Graph :: dfs(int v, int destiny, int distancia) {
    if(distancia==0) return false;
    airports[v].visited = true;
    for (auto e :  airports[v].voos) {
        int w = e.destino;
        if(w==destiny) return true;
        if (!airports[w].visited)
        dfs(w,destiny,distancia--);
    }
    return false;
}


vector<vector<int>> Graph::findRoutes(int origin, int destiny){
    for (int i=1; i<=n; i++) {
        airports[i].visited = false; airports[i].dist = -1;
    }
    vector<vector<int>> routes;

    for(auto flight : airports[origin].voos){
        vector<int> this_route;
        this_route.push_back(origin);
        int dest = flight.destino;
        if(dest == destiny) {
            this_route.push_back(dest);
        }
        else{
            int d = bfs_distance(dest, destiny);
            this_route.push_back(dest);
            getRoute(dest, destiny, d, this_route);
        }


        routes.push_back(this_route);
    }

    return routes;
}


void Graph::getRoute(int origem, int destino, int distancia, vector<int>& route){

    auto it=airports[origem].voos.begin();
    while (it!=airports[origem].voos.end()){
        Flight e=*it;
        int d=e.destino;
        if(d==destino) {
            route.push_back(d);
            break;
        }
        if(dfs(d,destino,distancia-1)){
            route.push_back(d);
            it=airports[d].voos.begin();
            origem=d;
            distancia=distancia-1;
        }
        else it++;
    }
}


//Calcula a distancia
int Graph::bfs_distance(int a, int b) {
    for (int i=1; i<=n; i++) {
        airports[i].visited = false; airports[i].dist = -1;
    }
    queue<int> q;
    q.push(a); airports[a].visited = true; airports[a].dist = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto e : airports[u].voos) {
            int w = e.destino  ;
            if (!airports[w].visited) {
                q.push(w);
                airports[w].visited = true;
                airports[w].dist = airports[u].dist + 1;
                if (w == b) break;
            }
        }
    }
    return airports[b].dist;
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
        for(int i=1;i<airports.size();i++){
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


int Graph::find_airport(std::string code) {
    for( Node n:airports){
        n.visited=false;
    }
    for (int v=1;v<airports.size();v++){
        if(airports[v].airport.getCode()==code) return v;
    }
    return 0;
}


int Graph::number_flights(int a) {
    return airports[a].voos.size();
}


int Graph::minRoute(vector<vector<int>> routes){
    int min = 100;

    for(auto elem : routes){
        if(elem.size() < min){ min = elem.size();}
    }

    return min;
}


vector<vector<string>> Graph::fly_airport(std::string origem, std::string destino, vector<std::string> companhias) {
    vector<vector<string>> result;
    int o=0;
    int d=0;
    for(int i=1;i<airports.size();i++){
        if(airports[i].airport.getCode()==origem) o=i;
        if(airports[i].airport.getCode()==destino) d=i;
    }

    vector<vector<int>> routes = findRoutes(o,d);
    int min_route = minRoute(routes);

    for(auto vec : routes){
        if(vec.size() != min_route) continue;
        vector<string> route;
        for(auto elem : vec){
            string temp = airports[elem].airport.getCode() + " " + airports[elem].airport.getName();
            route.push_back(temp);
        }
        result.push_back(route);
    }

    return result;
}


vector<int> Graph::fly_city(std::string origem, std::string destino, vector<std::string> companhias) {

}


vector<int> Graph::fly_local(std::string origem, std::string destino, int km, vector<std::string> companhias) {


}
