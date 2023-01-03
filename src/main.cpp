
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
            vector<vector<string>> route;
            vector<string> companhias = {};
            string tipo;
            string origem;
            string destino;
            cout << "\n====================== VIAGEM =====================";
            string resposta;
            cout << "\n Pretende usar alguma lista restrita de comanhias aereras? (S/N)";
            cin >> resposta;
            if (resposta == "S") {
                string numero;
                cout << "Quantas sao as companhias aereas que pretende usar?";
                cin >> numero;
                cout << "Indique o seu codigo.";
                for (int i = 1; i <= stoi(numero); i++) {
                    string a;
                    cout << "\n" << i << ")";
                    cin >> a;
                    companhias.push_back(a);
                }
            }
            cout << "\n Vai inserir o que?: \n  1)Cidade 2)Codigo de Aeroporto 3)Localizacao";
            cin >> tipo;
            cout << "\n ORIGEM: ";
            cin >> origem;
            cout << "\n DESTINO: ";
            cin >> destino;
            if (tipo == "1") graph.fly_city(origem, destino, companhias);
            else if (tipo == "2") route = graph.fly_airport(origem, destino, companhias);
            else if (tipo == "3") {
                string x;
                cout << "\n Indique o numero de km que pode variar das localizacoes inseridas: ";
                cin >> x;
                int km = stoi(x);
                graph.fly_local(origem, destino, km, companhias);
            } else {
                cout << "\nOpcao invalida!";
                return 0;
            }

            //print route
            if (route.empty()) cout << "\n Impossivel";
            else {
                cout << "\nAs melhores opçoes são:\n";
                for (auto vec: route) {
                    for (int i = 0; i < vec.size() - 1; i++) {
                        cout << vec[i] << " | ";
                    }
                    cout << vec.back() << '\n';
                }
            }


        } else if (input == "2") {
            cout << "\nIndique o codigo do Aeroporto sobre o qual quer recolher informacao\n";
            string aeroporto;
            cin >> aeroporto;
            int a = graph.find_airport(aeroporto);
            if (a == 0) {
                cout << "Aeroporto não encontrado";
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
