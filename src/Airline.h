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
    /// Construtor with parameters.
    /// \param code Code of the Airline
    /// \param name Name of the Airline
    /// \param callsign Callsign of the Airline
    /// \param country Country that the Airline belongs
    Airline(string code, string name, string callsign, string country);
    /// Getter.
    /// \return Code of the Airline
    string getCode() const;
    /// Getter.
    /// \return Name of the Airline
    string getName();
    /// Getter.
    /// \return Callsign of the Airline
    string getCallSign();
    /// Getter.
    /// \return Country of the Airline
    string getCountry();
    /// Definition of operator "==".
    /// \param f An airline
    /// \return Wether if it the same airline or not
    bool operator==(const Airline& f) const {
         return (this->getCode() == f.code);
    }
    /// Definition of operator "<".
    /// \param f An airline
    /// \return Wether if the code of the airline is "smaller" (alphabetically) or not
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
