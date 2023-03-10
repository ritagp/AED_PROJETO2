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

int Graph::find_airport(std::string code) {
    for( Node n:airports){
        n.visited=false;
    }
    for (int v=1;v<airports.size();v++){
        if(airports[v].airport.getCode()==code) return v;
    }
    return 0;
}


vector<vector<int>> Graph::getAllPaths(int s, int d, int min, vector<string> &companhias, bool one){
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

void Graph::getAllPathsUtil(int u, int d,int path[], int& path_index, int min, vector<int>& route,  vector<vector<int>>& result, vector<string> &companhias, bool one ){
    if(one and !result.empty()) return;
    bool c=false;
    airports[u].visited = true;
    path[path_index] = u;
    path_index++;

    if (path_index<=min) {
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
                        c = false;
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

vector<vector<string>> Graph::fly_airport(std::string origem, std::string destino, vector<std::string> &companhias, bool one, vector<vector<vector<string>>>& airlines) {
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
        if(i==7) return {};
    }
    //vector<pair<string, string>> result_;
    vector<vector<string>> res;
    vector<vector<pair<string, string>>> route;
    if (o == 0 || d == 0)
        return {};
    else if (origem == destino)
        return {};
    else {
        for (auto vec: result) {
            vector<string> route;
            for (auto elem: vec) {
                string temp = airports[elem].airport.getCode() + " " + airports[elem].airport.getName();
                route.push_back(temp);
            }
            res.push_back(route);
        }
    }
    vector<string> airlines_voo;
    vector<vector<string>> airlines_percurso;
    for(auto vec: result){
        for( int i=0;i<vec.size()-1;i++){
            for(auto e: airports[vec[i]].voos){
                if(e.destino==vec[i+1]){
                    if(companhias.empty()){
                        auto it=e.airlines.begin();
                        while (it!=e.airlines.end()){
                            airlines_voo.push_back((*it).getCode());
                            it++;
                        }
                    }
                    else{
                        for(auto elem:companhias){
                            Airline a=Airline(elem,"","","");
                            if(e.airlines.find(a)!=e.airlines.end()){
                                airlines_voo.push_back(a.getCode());
                            }

                        }
                    }
                    airlines_percurso.push_back(airlines_voo);
                    airlines_voo={};
                    break;
                }
            }

        }
        airlines.push_back(airlines_percurso);
        airlines_percurso={};
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
vector<vector<vector<string>>> Graph::fly_city(std::string origem, std::string destino, vector<std::string> companhias, bool one, vector<vector<vector<string>>>& airlines) {
    /*vector<vector<vector<string>>> ress;
        vector<int> ori;
        vector<int> dest;
        int orig;
        int desti;
        for (int i = 1; i < airports.size(); i++) {
            if (airports[i].airport.getCity() == origem) {
                orig = i;
                ori.push_back(orig);
            }
            if (airports[i].airport.getCity() == destino) {
                desti = i;
                dest.push_back(desti);
            }
        }*/
    vector<vector<vector<string>>> ress;
    vector<int> ori;
    vector<int> dest;
    unordered_set<string> c_o;
    unordered_set<string> c_d;
    vector<string> country_o;
    vector<string> country_d;
    vector<pair<int,string>> origens;
    vector<pair<int,string>> destinos;
    string country="";
    for (int i = 1; i < airports.size(); i++) {
        if (airports[i].airport.getCity() == origem) {
            origens.push_back({i,airports[i].airport.getCountry()});
            auto it=c_o.find(airports[i].airport.getCountry());
            if(it==c_o.end()) {
                c_o.insert(airports[i].airport.getCountry());
                country_o.push_back(airports[i].airport.getCountry());
            }
        }
        if (airports[i].airport.getCity() == destino) {
            destinos.push_back({i,airports[i].airport.getCountry()});
            auto it=c_d.find(airports[i].airport.getCountry());
            if(it==c_d.end()) {
                c_d.insert(airports[i].airport.getCountry());
                country_d.push_back(airports[i].airport.getCountry());
            }
        }

    }
    if(country_o.size()>1){
        cout<<"Em qual destes paises esta localizada a origem?\n";
        for(int i=0;i<country_o.size();i++){
            cout<<i<<") "<< country_o[i]<<"\n";
        }
        string input;
        cin>>input;
        int a =stoi(input);
        country=country_o[a];
        for(auto elem: origens){
            if(elem.second==country) ori.push_back(elem.first);
        }
    }
    else{
        for(auto elem: origens){
            ori.push_back(elem.first);
        }

    }

    if(country_d.size()>1){
        cout<<"Em qual destes paises esta localizado o destino?\n";
        for(int i=0;i<country_d.size();i++){
            cout<<i<<") "<< country_d[i]<<"\n";
        }
        string input;
        cin>>input;
        int a =stoi(input);
        country=country_d[a];
        for(auto elem: destinos){
            if(elem.second==country) dest.push_back(elem.first);
        }
    }
    else{
        for(auto elem: destinos){
            dest.push_back(elem.first);
        }

    }
    map<vector<string>, int> comb;
    vector<string> air;
    for (int i = 0; i < ori.size(); i++) {
        for (int j = 0; j < dest.size(); j++) {
            air.clear();
            int dist = bfs_distance(ori[i], dest[j]);
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
    if (origem == destino)
        ress = {};
    else if (possible.size() > 1) {
        vector<vector<string>> temp;
        for (int i = 0; i < possible.size(); i++) {
            temp = fly_airport(possible[i][0], possible[i][1], companhias, one,airlines);
            ress.push_back(temp);
        }
    } else if (possible.size() == 1) {
        ress.push_back(fly_airport(possible[0][0], possible[0][1], companhias, one,airlines));
    }
    else {
        ress = {};
    }
    return ress;
}


vector<vector<vector<string>>> Graph::fly_local(string lat_ori, string long_ori, string lat_dest, string long_dest, int km, vector<std::string> companhias, bool one, vector<vector<vector<string>>>& airlines) {
    vector<vector<vector<string>>> ress = {{{"not empty"}}};
    vector<string> inputs = {lat_ori, long_ori, lat_dest, long_dest};
    for (int i = 0; i < inputs.size(); i++) {
        for (char c: inputs[i]) {
            if (isdigit(c) || c == '.')
                continue;
            else {
                ress = {};
                break;
            }
        }
        break;
    }
    if (ress.size() == 0){
        return ress;
    }
    else {
        vector<int> ori;
        vector<int> dest;
        int orig;
        int desti;
        for (int i = 1; i < airports.size(); i++) {
            if (getDistanceKms(stod(lat_ori), stod(long_ori), stod(airports[i].airport.getLatitude()),
                               stod(airports[i].airport.getLongitude())) <= km) {
                orig = i;
                ori.push_back(orig);
            }
            if (getDistanceKms(stod(lat_dest), stod(long_dest), stod(airports[i].airport.getLatitude()),
                               stod(airports[i].airport.getLongitude())) <= km) {
                desti = i;
                dest.push_back(desti);
            }
        }
        map<vector<string>, int> comb;
        vector<string> air;
        for (int i = 0; i < ori.size(); i++) {
            for (int j = 0; j < dest.size(); j++) {
                air.clear();
                int dist = bfs_distance(ori[i], dest[j]);
                air.push_back(airports[ori[i]].airport.getCode());
                air.push_back(airports[dest[j]].airport.getCode());
                comb[air] = dist;
            }
        }
        ress = {};
        auto it = comb.begin();
        vector<vector<string>> possible;
        while (it != comb.end()) {
            air = it->first;
            possible.push_back(air);
            it++;
        }
        if (lat_ori == lat_dest && long_ori == long_dest)
            ress = {};
        else if (possible.size() > 1) {
            vector<vector<string>> temp;
            for (int i = 0; i < possible.size(); i++) {
                temp = fly_airport(possible[i][0], possible[i][1], companhias, one, airlines);
                ress.push_back(temp);
            }
        } else if (possible.size() == 1) {
            ress.push_back(fly_airport(possible[0][0], possible[0][1], companhias, one, airlines));
        }
        return ress;
    }
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

bool cmp(pair<int, int>& a, pair<int, int>& b){
    return a.second > b.second;
}

void Graph::topAirports(){
    vector<pair<int,int>> table(n, {0,0});

    int i=1;
    while(i<n){
        for(auto elem: airports[i].voos){
            if(table[i].first == 0){ table[i].first = i;}
            table[elem.destino].second += elem.airlines.size();
        }

        i++;
    }

    sort(table.begin(),table.end(),cmp);

    cout << "====================== TOP 10 AIRPORTS ======================\n";
    for(int j = 0; j <10; j++){
        cout << j+1 << ") " << airports[table[j].first].airport.getCode() << " - " << airports[table[j].first].airport.getName() << ", " << airports[table[j].first].airport.getCity() << " || Arrivals: " << table[j].second << '\n';
    }

}