//
// Created by ritag on 21/12/2022.
//

#ifndef PROJETO2_AIRPORT_H
#define PROJETO2_AIRPORT_H

#include <string>

using namespace std;

class Airport {
public:
    Airport(string code, string name, string city, string country, string latitude, string longitude);
    string getCode();
    string getName();
    string getCity();
    string getCountry();
    string getLatitude();
    string getLongitude();

private:
    string code;
    string name;
    string city;
    string country;
    string latitude;
    string longitude;

};


#endif //PROJETO2_AIRPORT_H
