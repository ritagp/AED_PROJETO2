//
// Created by ritag on 21/12/2022.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
#include "Graph.h"

///Construção do grafo

Graph::Graph(vector<Airport> airports,int number_of_airports) {
    struct Node zero= {{},Airport("","","","","",""),false,-1};
    this->airports.push_back(zero);
    this->n=number_of_airports;
    for(int i=0;i<number_of_airports;i++){
        struct Node n={{},airports[i],false,-1};
        this->airports.push_back(n);
    }
}

///Adição dos voos ao grafo
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



//Add a flight from source to destination with a certain airline
void Graph::addFlight(int src, int dest, Airline airline) {
    if (src<1 || src>n || dest<1 || dest>n) return;
    auto it=airports[src].voos.begin();
    while(it!=airports[src].voos.end()){
        Flight& temp=*it;
        if(temp.destino==dest) {
            temp.airlines.push_back(airline);
            return;
        }
        it++;
    }
    list<Airline> temp={airline};
    airports[src].voos.push_back({dest,temp});
}

//find the indice of an airport given a code
int Graph::find_airport(std::string code) {
    for( Node n:airports){
        n.visited=false;
    }
    for (int v=1;v<airports.size();v++){
        if(airports[v].airport.getCode()==code) return v;
    }
    return 0;
}

//find the number of flights that leave from a airport
int Graph::number_flights(int a) {
    return airports[a].voos.size();
}


vector<vector<int>> Graph::getAllPaths(int s, int d){
    int* path = new int[n];
    int path_index = 0;
    vector<int> route;
    vector<vector<int>> result;

    for (int i = 0; i < n; i++)
        airports[i].visited=false;

    // Call the recursive helper function to get all paths
    getAllPathsUtil(s, d, path, path_index,route,result);

    return result;
}

void Graph::getAllPathsUtil(int u, int d,int path[], int& path_index,vector<int>& route,  vector<vector<int>>& result){
    airports[u].visited = true;
    path[path_index] = u;
    path_index++;

    if (path_index<5) {
        if (u == d) {
            //caminho encontrado
            for (int i = 0; i < path_index; i++) {
                route.push_back(path[i]);
            }
            if (route.size() > 4) return;
            result.push_back(route);
            route = {};

        } else
        {
            auto i = airports[u].voos.begin();;
            for (i; i != airports[u].voos.end(); ++i) {
                Flight e = *i;
                int d_ = e.destino;
                if (!airports[d_].visited)
                    getAllPathsUtil(d_, d, path, path_index, route, result);
            }


        }
    }
    path_index--;
    airports[u].visited = false;

}

vector<vector<pair<string,string>>> Graph::fly_airport(std::string origem, std::string destino, vector<std::string> companhias) {
    int o= find_airport(origem);
    int d= find_airport(destino);
    vector<vector<int>> result= getAllPaths(o, d);
    vector<pair<string,string>> result_;
    vector<vector<pair<string,string>>> route;
    for(int i=0;i<result.size();i++){
        for(int j=0;j<result[i].size();j++){
            result_.push_back({airports[result[i][j]].airport.getCode(),airports[result[i][j]].airport.getName()});
        }
        route.push_back(result_);
        result_={};
    }
    return route;
}


vector<int> Graph::fly_city(std::string origem, std::string destino, vector<std::string> companhias) {

}


vector<int> Graph::fly_local(std::string origem, std::string destino, int km, vector<std::string> companhias) {

}
