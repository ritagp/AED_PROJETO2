//
// Created by ritag on 21/12/2022.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <map>
#include <stack>
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


/*vector<vector<int>> Graph::findRoutes(int origin, int destiny){
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
}*/


vector<vector<int>> Graph::getRoute(int origem, int destino, int distancia){
    vector<vector<int>> result;
    vector<int> route;
    auto it=airports[origem].voos.begin();
    stack<list<Flight>::iterator> save_it;
    stack<vector<int>> save_vector;
    stack<int> save_dist;

    save_it.push(it);
    save_vector.push({origem});
    save_dist.push(distancia);

    route.push_back(origem);

    while(!save_it.empty()) {
        it=save_it.top();
        route=save_vector.top();
        distancia=save_dist.top();
        save_it.pop();
        save_vector.pop();
        save_dist.pop();

        if(distancia!=1){  Flight temp=*it;
            while(!dfs(temp.destino, destino,distancia-1) and it!=airports[route.back()].voos.end()){
                it++;
                temp=*it;
            }
            if(it==airports[route.back()].voos.end()) break;
        }


        while (it != airports[route.back()].voos.end()) {
            Flight e = *it;
            int d = e.destino;
            if (d == destino) {
                route.push_back(d);
                break;
            }
            if (dfs(d, destino, distancia - 1)) {
                save_it.push(++it);
                save_vector.push(route);
                save_dist.push(distancia);
                route.push_back(d);
                it = airports[d].voos.begin();
                origem = d;
                distancia = distancia - 1;
            } else it++;
        }
        if(route.back()==destino) result.push_back(route);
    }

    return result;
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


/*int Graph::minRoute(vector<vector<int>> routes){
    int min = 100;

    for(auto elem : routes){
        if(elem.size() < min){ min = elem.size();}
    }

    return min;
}*/


vector<vector<pair<string,string>>> Graph::fly_airport(std::string origem, std::string destino, vector<std::string> companhias) {
    vector<pair<string,string>> result;
    vector<vector<pair<string,string>>> route;
    int o= find_airport(origem);
    int d= find_airport(destino);
    int dist= bfs_distance(o,d);
    vector<vector<int>> route_= getRoute(o,d,dist);
    for(int i=0;i<route_.size();i++){
        for(int j=0;j<route_[i].size();j++){
            result.push_back({airports[route_[i][j]].airport.getCode(),airports[route_[i][j]].airport.getName()});
        }
        route.push_back(result);
        result={};
    }

    /*vector<vector<int>> routes = findRoutes(o,d);
    int min_route = minRoute(routes);

    for(auto vec : routes){
        if(vec.size() != min_route) continue;
        vector<string> route;
        for(auto elem : vec){
            string temp = airports[elem].airport.getCode() + " " + airports[elem].airport.getName();
            route.push_back(temp);
        }
        result.push_back(route);
    }*/

    return route;
}


vector<int> Graph::fly_city(std::string origem, std::string destino, vector<std::string> companhias) {

}


vector<int> Graph::fly_local(std::string origem, std::string destino, int km, vector<std::string> companhias) {


}
