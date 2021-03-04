#include <iostream>
#include <thread>
#include <string>
#include <array>
#include <time.h>
#include <chrono>

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
    void check_date();

private:
    int day;
    int month;
    int year;
    static constexpr int month_days[13] = {0, 31,28,31, 30,31, 30, 31, 31, 30, 31, 30, 31 };
};


class Person : public PersonIf {
public:
    Person(const string & _name, const string & _surname,
           const string & _address, int _day, int _month, int _year)
           : name(_name),
             surname(_surname),
             address(_address),
             Date_Of_Birth(_day, _month, _year)
    {


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
                                               "Wenus", "Księzyc", "Most"
                                               }};

        name = random_names[los(0,N)];
        surname = random_surnames[los(0,N)];
        address = random_address[los(0,N)];
    }
    const string & get_name() const { return name; }
    const string & get_surname() const { return surname; }
    const string & get_address() const { return address; }
    const int & get_age() const { return age; }
    const string & get_date_of_birth() const { return date_of_birth; }
    const long long & get_pesel() const { return pesel; }

    friend ostream & operator<<(ostream &out, const Person & per) {
        out << per.name << " " << per.surname << " " << "adres: " << per.address;
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

};

void hello(int n, const string & str) {
    for(int k = 0; k < n; k++) {
        cout << str << "\n";
    }
}

int main()
{
    auto start = std::chrono::system_clock::now();
    // Some computation here
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

    srand(time(nullptr));

    for(int k = 0; k < 10; k++) {
        cout << los(3,7) << endl;
    }

    Person test(Random{});
    cout << test << endl;
    thread w1;
    w1 = thread(hello, 5, "hi!");
    w1.join();
    return 0;
}

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
