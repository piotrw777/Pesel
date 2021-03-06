#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <array>
#include "date.h"
#include "pom_functions.h"

using namespace std;

struct Random {
    Random() {}
};

class PersonIf {
public:
    virtual const string & get_name() const = 0;
    virtual const string & get_surname() const = 0;
    virtual const string & get_address() const = 0;
    virtual const int & get_age() const = 0;
    virtual const string & get_date_of_birth() const = 0;     //zwraca string w formacie YYY.MM.DD
    virtual const long long & get_pesel() const = 0;
};

class Person : public PersonIf {
public:
    Person(const string & _name, const string & _surname,
           const string & _address, int _day, int _month, int _year);
    Person(Random);
    const string & get_name() const { return name; }
    const string & get_surname() const { return surname; }
    const string & get_address() const { return address; }
    const int & get_age() const { return age; }
    const string & get_date_of_birth() const { return date_of_birth; }
    const date & get_date() const { return Date_Of_Birth; }
    const long long & get_pesel() const { return pesel; }
    int getNr() const { return nr; }
    friend ostream & operator<<(ostream &out, const Person & per);

private:
    string name;
    string surname;
    int age;
    static int nr;
    date Date_Of_Birth;
    string date_of_birth;
    string address;
    long long pesel;
    void generate_pesel(int d, int m, int y);
    void generate_date_of_birth(int d, int m, int y);
};

#endif // PERSON_H
