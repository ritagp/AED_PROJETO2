//
// Created by ritag on 21/12/2022.
//

#include "Airport.h"

using namespace std;

Airport::Airport(string code,string name,string city,string country,string latitude,string longitude) {
    this->code=code;
    this->city=city;
    this->country=country;
    this->latitude=latitude;
    this->longitude=longitude;
    this->name=name;
}

string Airport::getCode() {
    return this->code;
}
string Airport::getName() {
    return this->name;
}
string Airport::getCity() {
    return this->city;
}
string Airport::getCountry() {
    return this->country;
}
string Airport::getLatitude() {
    return this->latitude;
}
string Airport::getLongitude() {
    return this->longitude;
}