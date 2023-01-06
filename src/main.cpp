
#include <iostream>

#include <iostream>
#include <set>
#include "Gestor.h"
#include "Graph.h"
using namespace std;
int main() {

    //store information
    Gestor gestor;
    Graph graph= Graph();
    gestor.read_airports(graph);
    gestor.read_airlines();
    unordered_set<Airline,AirlineHash> airlines=gestor.getAirlines();

    graph.read_flights(airlines);

    //menu
    while(true) {
        string input;
        cout << "\n==================== PLAN YOUR FLIGHT ===================\n";
        cout << "\nEscolha a opcao que mais se adequa ao que pretende fazer?\n";
        cout << "\n1) Planear uma viagem (ver qual o menor numero de voos)\n";
        cout << "2) Ver informacao sobre um aeroporto\n";
        cout << "3) Sair\n";

        cin >> input;


        if (input == "1") {
            vector<vector<vector<string>>> route_big;
            vector<vector<string>> route;
            vector<string> companhias = {};
            string tipo;
            string origem;
            string destino;
            cout << "\n====================== VIAGEM =====================";
            string resposta;
            cout << "\n Pretende usar alguma lista restrita de companhias aereas? (S/N) ";
            cin >> resposta;
            if (resposta == "S") {
                string numero;
                cout << "\nQuantas sao as companhias aereas que pretende usar? ";
                cin >> numero;
                cout << "Indique o seu codigo.";
                for (int i = 1; i <= stoi(numero); i++) {
                    string a;
                    cout << "\n" << i << ")";
                    cin >> a;
                    companhias.push_back(a);
                }
            }
            cout<<"\n Pretende que seja apresentada uma unica possibilidade de percurso, ou todas  que consistem no menor número de voos?\n";
            cout<<"\n 1) Uma";
            cout<<"\n 2) Todas\n";
            string a;
            cin>> a;
            bool one;
            if(a=="1") one=true;
            if(a=="2") one=false;
            cout << "\n Vai inserir o que?: \n  1) Cidade 2) Codigo de Aeroporto 3) Localizacao ";
            cin >> tipo;
            if (tipo == "1") {
                cout << "\n ORIGEM: ";
                cin >> origem;
                cout << "\n DESTINO: ";
                cin >> destino;
                route_big = graph.fly_city(origem, destino, companhias,one);
            }
            else if (tipo == "2") {
                cout << "\n ORIGEM: ";
                cin >> origem;
                cout << "\n DESTINO: ";
                cin >> destino;
                route = graph.fly_airport(origem, destino, companhias, one);
            }
            else if (tipo == "3") {
                string lat_orig;
                string lat_dest;
                string long_orig;
                string long_dest;
                cout << "\n Indique as coordenadas do local de origem e o local de destino.";
                cout << "\n Latitude origem: ";
                cin >> lat_orig;
                cout << "\n Longitude origem: ";
                cin >> long_orig;
                cout << "\n Latitude destino: ";
                cin >> lat_dest;
                cout << "\n Longitude destino: ";
                cin >> long_dest;
                string x;
                cout << "\n Indique o numero de km que pode variar das localizacoes inseridas: ";
                cin >> x;
                int km = stoi(x);
                route_big = graph.fly_local(lat_orig,long_orig,lat_dest,long_dest,km ,companhias,one);
            } else {
                cout << "\nOpcao invalida!";
                return 0;
            }

            //print route
            if (!route.empty() && route_big.empty()) {
                cout << "\nAs opcoes sao:\n";
                for (auto vec: route) {
                    for (int i = 0; i < vec.size() - 1; i++) {
                        cout << vec[i] << " | ";
                    }
                    cout << vec.back() << '\n';
                }
            }

            else if (!route_big.empty() && route.empty()) {
                cout << "\nAs opcoes sao:\n";
                for (auto vec: route_big){
                    for (auto vec1: vec) {
                        for (int i = 0; i < vec1.size() - 1; i++) {
                            cout << vec1[i] << " | ";
                        }
                        cout << vec1.back() << '\n';
                    }
                }
            }


        } else if (input == "2") {
            cout << "\nIndique o codigo do Aeroporto sobre o qual quer recolher informacao\n";
            string aeroporto;
            cin >> aeroporto;
            int a = graph.find_airport(aeroporto);
            if (a == 0) {
                cout << "Aeroporto nao encontrado";
            } else {
                graph.getAirportInfo(a);
            }

        }
        else if(input=="3"){
            break;
        }
    }

    return EXIT_SUCCESS;
}
