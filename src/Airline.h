//
// Created by ritag on 21/12/2022.
//

#ifndef PROJETO2_AIRLINE_H
#define PROJETO2_AIRLINE_H

#include <string>
#include <unordered_map>

using namespace std;

class Airline {
public:
    Airline(string code, string name, string callsign, string country);

    string getCode() const;
    string getName();
    string getCallSign();
    string getCountry();
    bool operator==(const Airline& f) const {
         return (this->getCode() == f.code);
    }
    bool operator<(const Airline& f) const {
        return (this->getCode() < f.code);
    }

private:
    string code;
    string name;
    string callsign;
    string country;

};

struct AirlineHash{
    size_t operator() (Airline const& airline) const{
        return hash<string>() (airline.getCode());
    }
};

#endif //PROJETO2_AIRLINE_H
