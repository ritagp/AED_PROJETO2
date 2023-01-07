
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
            vector<vector<vector<string>>> airlines={};
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
            cout << "\n Vai inserir o que? \n  1) Cidade 2) Codigo de Aeroporto 3) Localizacao\n";
            cin >> tipo;

            if(tipo=="2"){
                cout<<"\n Escolha a opcao que mais se adequa ao que pretende ver:";
                cout<<"\n 1) Uma das possibilidades de percurso com menor numero de voos";
                cout<<"\n 2) Todas as possibilidades de percurso com menor numero de voos\n";
            }
            else if(tipo =="3" or tipo=="1"){
                cout<<"\n Escolha a opcao que mais se adequa ao que pretende ver:";
                cout<<"\n 1) Um percurso para cada conjunto de aeroporto (origem, destino) com menor numero de voos";
                cout<<"\n 2) Todas as possibilidades de percurso com menor numero de voos\n";

            }
            string a;
            cin>> a;
            bool one;
            if(a=="1") one=true;
            if(a=="2") one=false;

            if (tipo == "1") {
                cout << "\n ORIGEM: ";
                string origem1;
                cin>>origem1;
                getline(cin,origem,'\n');
                origem=origem1+origem;
                cout << "\n DESTINO: ";
                string destino1;
                cin>>destino1;
                getline(cin,destino,'\n');
                destino=destino1+destino;
                route_big = graph.fly_city(origem, destino, companhias,one,airlines);
            }
            else if (tipo == "2") {
                cout << "\n ORIGEM: ";
                cin >> origem;
                cout << "\n DESTINO: ";
                cin >> destino;
                route = graph.fly_airport(origem, destino, companhias, one,airlines);
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
                route_big = graph.fly_local(lat_orig,long_orig,lat_dest,long_dest,km ,companhias,one,airlines);
            } else {
                cout << "\nOpcao invalida!";
                return 0;
            }

            //print route
            if (route_big.empty() && route.empty())
                cout << "\n Input invalido";
            if (!route.empty() && route_big.empty()) {
                cout << "\nAs opcoes sao:\n";
                for (int j=0;j<route.size(); j++) {
                    for (int i = 0; i < route[j].size() - 1; i++) {
                        cout << route[j][i] << " | ";
                    }
                    cout << route[j].back();
                    cout<<"\nCompanhias: ";
                    for(auto vec: airlines[j]){
                        for( int k=0;k<vec.size()-1;k++ ){
                            cout<< vec[k]<<",";
                        }
                        cout<<vec.back()<<" | ";
                    }
                    cout<<"\n\n";
                }

            }

            else if (!route_big.empty() && route.empty()) {
                cout << "\nAs opcoes sao:\n";
                for (int k=0;k<route_big.size();k++){
                    for (int j=0; j<route_big[k].size();j++) {
                        for (int i = 0; i < route_big[k][j].size() - 1; i++) {
                            cout << route_big[k][k][i] << " | ";
                        }
                        cout << route_big[k][j].back();
                        cout<<"\nCompanhias: ";
                        for(auto vec: airlines[k+j]){
                            for( int l=0;l<vec.size()-1;l++ ){
                                string a=vec[l];
                                cout<< vec[l]<<",";
                            }
                            cout<<vec.back()<<" | ";
                        }
                        cout<<"\n\n";
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
