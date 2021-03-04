#include <iostream>
#include <thread>
#include <string>
#include <array>
#include <time.h>
#include <chrono>
#include <vector>
#include <iomanip>

using namespace std;

int los(int a, int b) {
    double d = 1.0 * rand() / RAND_MAX;
    return static_cast<int>(d * (b - a) + a);
}

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

class date {
public:
    date(){};
    date(int _day, int _month, int _year) : day(_day),  month(_month), year(_year){}

    int getDay() const;
    void setDay(int value);
    int getMonth() const;
    void setMonth(int value);
    int getYear() const;
    void setYear(int value);

    static bool check_date(int d, int m, int y) {
        string errange = "error range";
        string errleap = "error leap year";

        if(m < 1 || m > 12 || d < 1 || y < 1582) return false;
        bool leap_year = ( (y % 4 == 0) && (y % 100 != 0) ) | ( y % 400 == 0 );
        if(d > date::month_days[m] + ( (m == 2) && (leap_year == true) )  ) return false;

        return true;
    }

    static date current_date() {
        auto current_date = chrono::system_clock::now();
        time_t current_time = chrono::system_clock::to_time_t(current_date);
        struct tm *timeinfo;
        timeinfo = localtime(&current_time);
        return date(timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);
    }

    friend ostream & operator<<(ostream &out, const date & d) {
        out << d.getDay() << "." << d.getMonth() << "." <<  d.getYear();
        return out;
    }

private:
    int day;
    int month;
    int year;
    static int month_days[13];
};

int date::month_days[13] = {0, 31,28,31, 30,31, 30, 31, 31, 30, 31, 30, 31};

int date::getMonth() const
{
    return month;
}

void date::setMonth(int value)
{
    month = value;
}

int date::getYear() const
{
    return year;
}

void date::setYear(int value)
{
    year = value;
}

int date::getDay() const
{
    return day;
}

void date::setDay(int value)
{
    day = value;
}
class Person : public PersonIf {
public:
    Person(const string & _name, const string & _surname,
           const string & _address, int _day, int _month, int _year)
           : name(_name),
             surname(_surname),
             address(_address),
             Date_Of_Birth(_day, _month, _year)
    {
        age = date::current_date().getYear() - Date_Of_Birth.getYear() + 1;
    }
    Person(Random) {
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
                                               "Wenus", "Ksiezyc", "Most"
                                               }};
        int name_nr = los(0,N);
        int surname_nr = los(0,N);
        int address_nr = los(0,N);

        name = random_names[name_nr];
        surname = random_surnames[surname_nr];
        address = random_address[address_nr];

        int day_pom, month_pom, year_pom;
        do {
            day_pom = los(1,32);
            month_pom = los(1,13);
            year_pom = los(1900, 2021);
            if(date::check_date(day_pom, month_pom, year_pom))
            Date_Of_Birth = date(los(1,32), los(1,13), los(1900, 2021));
        }
        while(date::check_date(day_pom, month_pom, year_pom) == false);

        age = date::current_date().getYear() - Date_Of_Birth.getYear() + 1;

    }
    const string & get_name() const { return name; }
    const string & get_surname() const { return surname; }
    const string & get_address() const { return address; }
    const int & get_age() const { return age; }
    const string & get_date_of_birth() const { return date_of_birth; }
    const long long & get_pesel() const { return pesel; }

    friend ostream & operator<<(ostream &out, const Person & per) {
        int name_surname = per.name.length() + per.surname.length() + 1;
        auto spacier = [](int n){for(int k = 0; k < n; k++) cout << " ";};

        out << per.name << " " << per.surname;
        spacier(23 - name_surname);

        out << "adres: " << per.address;
        spacier(18 - per.address.length());

        out <<"data ur: " << per.Date_Of_Birth;
        spacier(19 - (per.Date_Of_Birth.getDay() > 9));
        out << "age: " << per.age;
        return out;
    }

private:
    string name;
    string surname;
    int age;
    date Date_Of_Birth;
    string date_of_birth;
    string address;
    long long pesel;
    void generate_pesel();
};

void hello(int n, const string & str) {
    for(int k = 0; k < n; k++) {
        cout << str << "\n";
    }
}

int main()
{
    cout << "Dzisiejsza data to: " << date::current_date() << endl;
    cout << "Dzisiejszy rok to: " << date::current_date().getYear() << endl;

    srand(time(nullptr));

    for(int k = 0; k < 10; k++) {
        cout << los(3,7) << endl;
    }

    thread w1;
    w1 = thread(hello, 5, "hi!");
    w1.join();

    vector<Person> persons;

    const int M = 10;

    for(int k = 0; k < M; k++) {
        persons.push_back(Person(Random{}));
    }

    int k = 1;
    for(const auto &i : persons) {
        cout << k << ". " << ((k < 10) ? " " : "") << i << endl;
        k++;
    }
}
