//
// Created by ritag on 21/12/2022.
//

#ifndef PROJETO2_AIRPORT_H
#define PROJETO2_AIRPORT_H

#include <string>

using namespace std;

class Airport {
public:
    /// Constructor with parameters
    /// \param code Code of the airport
    /// \param name Name of the airport
    /// \param city City of the airport
    /// \param country Country of the airport
    /// \param latitude Latitude of the airport
    /// \param longitude Longitude of the airport
    Airport(string code, string name, string city, string country, string latitude, string longitude);
    /// Getter.
    /// \return Code of the airport
    string getCode() const;
    /// Getter.
    /// \return Name of the airport
    string getName();
    /// Getter.
    /// \return City of the airport
    string getCity();
    /// Getter.
    /// \return Country which to the airport belongs
    string getCountry();
    /// Getter.
    /// \return Latitude of the airport
    string getLatitude();
    /// Getter.
    /// \return Longitude of the airport
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
