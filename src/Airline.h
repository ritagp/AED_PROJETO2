//
// Created by ritag on 21/12/2022.
//

#ifndef PROJETO2_AIRLINE_H
#define PROJETO2_AIRLINE_H

#include <string>
using namespace std;

class Airline {
public:
    Airline(string code, string name, string callsign, string country);
    string getCode();
    string getName();
    string getCallSign();
    string getCountry();
private:
    string code;
    string name;
    string callsign;
    string country;

};


#endif //PROJETO2_AIRLINE_H
