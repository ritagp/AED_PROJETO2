
#include <iostream>

#include <iostream>
#include "Gestor.h"
#include "Graph.h"
using namespace std;
int main() {

    //store information
    Gestor gestor;
    gestor.read_airports();
    gestor.read_airlines();
    vector<Airport> airports=gestor.getAirports();
    vector<Airline> airlines=gestor.getAirlines();
    Graph graph= Graph(airports,airports.size());
    graph.read_flights(airlines);

    //menu
    string input;
    cout<<"\n==================== PLAN YOUR FLIGHT ===================\n";
    cout<<"\nEscolha a opcao que mais se adequa ao que pretende fazer?\n";
    cout<<"\n1) Planear uma viagem (ver qual o menor numero de voos)\n";
    cout<<"2) Ver informacao sobre um aeroporto\n";

    cin>>input;


    if(input=="1"){
        vector<vector<pair<string,string>>> route;
        vector<string>companhias={};
        string tipo;
        string origem;
        string destino;
        cout<< "\n====================== VIAGEM =====================";
        string resposta;
        cout<<"\n Pretende usar alguma lista restrita de comanhias aereras? (S/N)";
        cin>> resposta;
        if(resposta=="S"){
            string numero;
            cout<<"Quantas sao as companhias aereas que pretende usar?";
            cin>>numero;
            cout<<"Indique o seu código.";
            for(int i=1;i<=stoi(numero);i++){
                string a;
                cout<<i<<")";
                cin>> a;
                companhias.push_back(a);
            }
        }
        cout<<"\n Vai inserir o que?: \n  1)Cidade 2)Código de Aeroporto 3)Localizacao";
        cin>> tipo;
        cout<<"\n ORIGEM: ";
        cin>> origem;
        cout<<"\n DESTINO: ";
        cin >> destino;
        if(tipo=="1") graph.fly_city(origem, destino,companhias);
        else if (tipo=="2") route = graph.fly_airport(origem, destino,companhias);
        else if (tipo=="3") {
            string x;
            cout<< "\n Indique o numero de km que pode variar das localizacoes inseridas: ";
            cin>>x;
            int km=stoi(x);
            graph.fly_local(origem, destino,km,companhias);
        }
        else{
            cout<<"\nOpcao invalida!";
            return 0;
        }

        //print route
        //cout<<"\nThe fastest way to get to your destiny is:\n";
        /*for(auto vec : route){
            for(int i =0; i<vec.size()-1;i++){
                cout << vec[i] << " | ";
            }
            cout << vec.back()<< '\n';
        }*/
        cout<<"\n The fastest way to get to your destiny is:";
        for(int i=0;i<route.size();i++){
            for(int j=0;j<route[i].size()-1;j++){
                cout << route[i][j].first << "," << route[i][j].second << " -> ";
                if(j+1==route.size()-1) break;
            }
            cout << route[i].back().first << "," << route[i].back().second;
            if(i+1<route.size()) cout<< "\nAnother option:\n";
        }





    }
    else if(input=="2"){
        cout<<"\nIndique o codigo do Aeroporto sobre o qual quer recolher informacao\n";
        string aeroporto;
        cin>>aeroporto;
        int number_of_flights=0;
        int a=graph.find_airport(aeroporto);
        if(a==0){
            cout<<"Aeroporto não encontrado";
        }
        else{
            number_of_flights=graph.number_flights(a);
        }
        cout<<"\n============== INFORMACOES GERAIS ==================\n";
        cout<<"Numero de voos que partem do areroporto: "<<number_of_flights;
        cout<<"";
    }

    return 0;
}
