//
// Created by ritag on 21/12/2022.
//

#include "Airline.h"

using namespace std;

Airline::Airline(string code, string name, string callsign, string country) {
    this->name=name;
    this->country=country;
    this->code=code;
    this->callsign=callsign;
}
string Airline::getCode() {
    return this->code;
}
string Airline::getCountry() {
    return this->country;
}
string Airline::getName() {
    return this->name;
}
string Airline::getCallSign() {
    return this->callsign;
}