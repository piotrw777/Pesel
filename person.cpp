#include "person.h"
#include <iostream>

#define ull unsigned long long

int los(int a, int b) {
    double d = 1.0 * rand() / (static_cast<double>(RAND_MAX) + 1);
    return static_cast<int>(d * (b - a) + a);
}

void spacier(int n){
    for(int k = 0; k < n; k++) cout << " ";
}

int Person::nr = 0;

Person::Person(const string &_name, const string &_surname, const string &_address, int _day, int _month, int _year)
    : name(_name),
      surname(_surname),
      address(_address),
      Date_Of_Birth(_day, _month, _year)
{
    age = date::current_date().getYear() - Date_Of_Birth.getYear();
    generate_pesel(_day, _month, _year);
    generate_date_of_birth(_day, _month,_year);
}

Person::Person(Random) {
    static const int N = 15;
    static array<string, N> random_names {{"Piotr", "Tomek", "Bartosz", "Czeslaw",
            "Wincenty", "Ignacy", "Mateusz", "Marcin",
            "Mieczyslaw", "Marek", "Jan", "Eustachy",
            "Kazimierz", "Ludwig", "Adam"
                                          }};
    static array<string, N> random_surnames {{"Malinowski", "Kowalski", "Mirislawski", "Kiepski",
            "Graczyk", "Bialy", "Niecny", "Zaluski",
            "Wolny", "Szybki", "Policki", "Wredny",
            "Halny", "Szmalc", "Redy"
                                             }};
    static array<string, N> random_address {{"Szczecin", "Krakow", "Warszawa", "Nowy Jork",
            "Waszyngton", "Londyn", "Bielsko-biala", "Zakopane",
            "Zielona Gora", "Jelenia Gora", "Mount Everest", "Row marianski",
            "Wenus", "Ksiezyc", "Most"}};

    auto check_range = [](int n){if(n < 0 || n >= 15) return -5; else return n;};
    int name_nr = los(0,N);
    if(check_range(name_nr) == -5) cout << "Bad number: " << name_nr << endl;

    int surname_nr = los(0,N);
    if(check_range(surname_nr) == -5) cout << "Bad number: " << surname_nr << endl;

    int address_nr = los(0,N);
    if(check_range(address_nr) == -5) cout << "Bad number: " << address_nr << endl;

    name = random_names[name_nr];

    surname = random_surnames[surname_nr];
    address = random_address[address_nr];

    int day_pom, month_pom, year_pom;
    do {
        day_pom = los(1,32);
        month_pom = los(1,13);
        year_pom = los(1900, 2021);
        if(date::check_date(day_pom, month_pom, year_pom))
            Date_Of_Birth = date(day_pom, month_pom, year_pom);
    }
    while(date::check_date(day_pom, month_pom, year_pom) == false);

    age = date::current_date().getYear() - Date_Of_Birth.getYear();
    generate_pesel(day_pom, month_pom, year_pom);
    generate_date_of_birth(day_pom, month_pom, year_pom);
    nr++;
}

ostream & operator<<(ostream &out, const Person & per) {
    int name_surname = per.name.length() + per.surname.length() + 1;

    out << per.name << " " << per.surname;
    spacier(23 - name_surname);

    out << "adres: " << per.address;
    spacier(16 - per.address.length());

    out <<"data ur: " << per.get_date_of_birth();
    spacier(4);
    out << "age: " << per.age;
    spacier(4 - to_string(per.age).length());

    out << "pesel: " << per.get_pesel();
    return out;
}

void Person::generate_pesel(int d, int m, int y)
{
    long long result = los(1e4, 1e5);
    result += d * 1e5;
    result += ( m + (y >= 2000)*20  ) * 1e7;
    result += (y % 100)*1e9;
    pesel = result;
}

void Person::generate_date_of_birth(int d, int m, int y)
{
    string result(10, '.');
    result[0] = d / 10 + '0';
    result[1] = d % 10 + '0';
    result[3] = m / 10 + '0';
    result[4] = m % 10 + '0';
    result.replace(6, 4, to_string(y));
    date_of_birth = result;
}
