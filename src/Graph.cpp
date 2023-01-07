//
// Created by ritag on 21/12/2022.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
#include <algorithm>
#include "Graph.h"
#include <map>
#include <valarray>

//Construção do grafo
Graph::Graph() {
    struct Node zero= {{},Airport("","","","","",""),false,-1};
    this->airports.push_back(zero);
}

//Adição dos voos ao grafo
void Graph::read_flights(unordered_set<Airline,AirlineHash> airlines_) {
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
        Airline find_=Airline(data[2],"","","");
        auto a= std::find(airlines_.begin(), airlines_.end(),find_);
        Airline airline=*a;
        addFlight(src,dest,airline);
        data.clear();
    }
}



///Add a flight from source to destination with a certain airline
void Graph::addFlight(int src, int dest, Airline airline) {
    n=airports.size();
    if(src<1 || src>n || dest<1 || dest>n) return;
    auto it=airports[src].voos.begin();
    while(it!=airports[src].voos.end()){
        Flight& temp=*it;
        if(temp.destino==dest) {
            temp.airlines.insert(airline);
            return;
        }
        it++;
    }
    unordered_set<Airline, AirlineHash> temp={airline};
    airports[src].voos.push_back({dest,temp});
}

///find the indice of an airport given a code
int Graph::find_airport(std::string code) {
    for( Node n:airports){
        n.visited=false;
    }
    for (int v=1;v<airports.size();v++){
        if(airports[v].airport.getCode()==code) return v;
    }
    return 0;
}

///find the number of flights that leave from a airport
int Graph::number_flights(int a) {
    return airports[a].voos.size();
}

///get all paths petween s and d
vector<vector<int>> Graph::getAllPaths(int s, int d, int min, vector<string> companhias, bool one){
    this->n=airports.size();
    int* path = new int[n];
    int path_index = 0;
    vector<int> route;
    vector<vector<int>> result;

    for (int i = 0; i < n; i++)
        airports[i].visited=false;

    // Call the recursive helper function to get all paths
    getAllPathsUtil(s, d, path, path_index,min,route,result, companhias,one);

    return result;
}

void Graph::getAllPathsUtil(int u, int d,int path[], int& path_index, int min, vector<int>& route,  vector<vector<int>>& result, vector<string> companhias, bool one ){
    if(one and !result.empty()) return;
    bool c=false;
    airports[u].visited = true;
    path[path_index] = u;
    path_index++;

    if (path_index<=min+1) {
        if (u == d) {
            //caminho encontrado
            for (int i = 0; i < path_index; i++) {
                route.push_back(path[i]);
            }
            result.push_back(route);
            if(one) return;
            route = {};

        } else {
            auto i = airports[u].voos.begin();;
            for (i; i != airports[u].voos.end(); ++i) {
                Flight e = *i;
                if (companhias.empty()) {
                    int d_ = e.destino;
                    if (!airports[d_].visited)
                        getAllPathsUtil(d_, d, path, path_index, min, route, result, companhias,one);

                } else {
                    for (auto elem: companhias) {
                        Airline temp = {elem, "", "", ""};
                        auto it = e.airlines.find(temp);
                        if (it != e.airlines.end()) {
                            c = true;
                            break;
                        }
                    }
                    if (c == true) {
                        int d_ = e.destino;
                        if (!airports[d_].visited)
                            getAllPathsUtil(d_, d, path, path_index, min, route, result, companhias,one);
                    }

                }

            }
        }
    }
    path_index--;
    airports[u].visited = false;

}




vector<vector<string>> Graph::fly_airport(std::string origem, std::string destino, vector<std::string> &companhias, bool one) {
    int o = find_airport(origem);
    int d = find_airport(destino);
    int i;
    vector<vector<int>> result={};
    int distancia= bfs_distance(o,d);
    if(distancia==-1) return {};
    else i=distancia;
    while (true) {
        for(int i=1;i<airports.size();i++){
            airports[i].visited=false;
        }
        result =getAllPaths(o,d,i,companhias, one);
        if(!result.empty()) break;
        i++;
    }
    vector<vector<string>> res;
    vector<pair<string, string>> result_;
    vector<vector<pair<string, string>>> route;

    for (auto vec: result) {
        vector<string> route;
        for (auto elem: vec) {
            string temp = airports[elem].airport.getCode() + " " + airports[elem].airport.getName();
            route.push_back(temp);
        }
        res.push_back(route);
    }

    return res;

}
int Graph::bfs_distance(int a, int b){
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
vector<vector<vector<string>>> Graph::fly_city(std::string origem, std::string destino, vector<std::string> companhias, bool one) {
    vector<int> ori;
    vector<int> dest;
    int orig;
    int desti;
    for (int i = 1; i < airports.size(); i++){
        if (airports[i].airport.getCity() == origem){
            orig = i;
            ori.push_back(orig);
        }
        if (airports[i].airport.getCity() == destino){
            desti = i;
            dest.push_back(desti);
        }
    }
    map<vector<string>,int> comb;
    vector<string> air;
    for (int i = 0; i < ori.size(); i++){
        for (int j = 0; j < dest.size(); j++){
            air.clear();
            int dist = bfs_distance(ori[i],dest[j]);
            air.push_back(airports[ori[i]].airport.getCode());
            air.push_back(airports[dest[j]].airport.getCode());
            comb[air] = dist;
        }
    }
    auto it = comb.begin();
    vector<vector<string>> possible;
    while (it != comb.end()) {
        air = it->first;
        possible.push_back(air);
        it++;
    }
    vector<vector<vector<string>>> ress;
    if (possible.size() > 1){
        vector<vector<string>> temp;
        for (int i = 0; i < possible.size(); i++){
            temp = fly_airport(possible[i][0], possible[i][1], companhias,one);
            ress.push_back(temp);
        }
    }
    else{
        ress.push_back(fly_airport(possible[0][0], possible[0][1], companhias,one));
    }
    return ress;
}


vector<vector<vector<string>>> Graph::fly_local(string lat_ori, string long_ori, string lat_dest, string long_dest, int km, vector<std::string> companhias, bool one) {
    vector<int> ori;
    vector<int> dest;
    int orig;
    int desti;
    for (int i = 1; i < airports.size(); i++){
        if (getDistanceKms(stod(lat_ori), stod(long_ori),stod(airports[i].airport.getLatitude()), stod(airports[i].airport.getLongitude())) <= km) {
            orig = i;
            ori.push_back(orig);
        }
        if (getDistanceKms(stod(lat_dest), stod(long_dest),stod(airports[i].airport.getLatitude()), stod(airports[i].airport.getLongitude())) <= km){
            desti = i;
            dest.push_back(desti);
        }
    }
    map<vector<string>,int> comb;
    vector<string> air;
    for (int i = 0; i < ori.size(); i++){
        for (int j = 0; j < dest.size(); j++){
            air.clear();
            int dist = bfs_distance(ori[i],dest[j]);
            air.push_back(airports[ori[i]].airport.getCode());
            air.push_back(airports[dest[j]].airport.getCode());
            comb[air] = dist;
        }
    }
    auto it = comb.begin();
    vector<vector<string>> possible;
    while (it != comb.end()) {
        air = it->first;
        possible.push_back(air);
        it++;
    }
    vector<vector<vector<string>>> ress;
    if (possible.size() > 1){
        vector<vector<string>> temp;
        for (int i = 0; i < possible.size(); i++){
            temp = fly_airport(possible[i][0], possible[i][1], companhias, one);
            ress.push_back(temp);
        }
    }
    else{
        ress.push_back(fly_airport(possible[0][0], possible[0][1], companhias,one));
    }
    return ress;
}




unordered_set<string> Graph::getAirlines(list<Flight> flights){
    unordered_set<string> temp;
    for(auto elem : flights){
        for(auto f : elem.airlines){
            if(temp.find(f.getName()) == temp.end()){
                temp.insert(f.getCode()+ " - " + f.getName());
            }
        }
    }
    return temp;
}

int Graph::countDestinies(list<Flight> flights){
    unordered_set<string> temp;

    for(auto elem : flights){
        if(temp.find(airports[elem.destino].airport.getCity()) == temp.end()){
            temp.insert(airports[elem.destino].airport.getCity() + " - " + airports[elem.destino].airport.getCountry());
        }
    }
    return temp.size();
}

int Graph::countCountries(list<Flight> flights){
    unordered_set<string> temp;

    for(auto elem : flights){
        if(temp.find(airports[elem.destino].airport.getCountry()) == temp.end()){
            temp.insert(airports[elem.destino].airport.getCountry());
        }
    }
    return temp.size();
}

void Graph::getAirportInfo(int a) {

    cout << "\n============== INFORMACOES GERAIS ==================\n";
    cout << "Aeroporto: " << airports[a].airport.getCode() << " - " << airports[a].airport.getName() << '\n';
    cout << "Localizacao: " << airports[a].airport.getCity() << " - " << airports[a].airport.getCountry() << " | "
         << airports[a].airport.getLatitude() << ", " << airports[a].airport.getLongitude() << '\n';
    cout << "Quantidade de voos de partida: " << airports[a].voos.size() << '\n';
    cout << "Quantidade de destinos: " << countDestinies(airports[a].voos) << '\n';
    cout << "Quantidade de paises: " << countCountries(airports[a].voos) << '\n';
    cout << "Companhias aereas operantes: " << '\n';

    for (auto elem: getAirlines(airports[a].voos)) {
        cout << "  > " << elem << '\n';
    }
}

void Graph::setAirport(Airport a) {
    struct Node n={{},a,false,-1};
    this->airports.push_back(n);
}

double Graph::getDistanceKms(double lat1, double long1, double lat2, double long2){
    int earth_radius = 6371;
    double diff_lat = degToRad(lat2-lat1);
    double diff_long = degToRad(long2-long1);
    double res = sin(diff_lat/2) * sin(diff_lat/2) + cos(degToRad(lat1)) * cos(degToRad(lat2))* sin(diff_long/2) * sin(diff_long/2);
    double c = 2 * atan2(sqrt(res), sqrt(1-res));
    double final = earth_radius * c;
    return final;
}

double Graph::degToRad(double diff){
    return diff * (M_PI/180);
}
