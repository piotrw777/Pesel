#include <iostream>
#include <thread>
#include <string>
#include <array>
#include <time.h>

using namespace std;

int los(int a, int b) {
    double d = 1.0 * rand() / RAND_MAX;
    return static_cast<int>(d*(b-a) + a);
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

class Person : public PersonIf {
public:
    Person(const string & _name, const string & _surname,
           const string & _address, const long long & _pesel)
           : name(_name),
             surname(_surname),
             address(_address),
             pesel(_pesel)
    {


    }
    Person(Random) {
        static const int N = 15;
        static array<string, N> random_names {{"Piotr", "Tomek", "Bartosz", "Czesław",
                                               "Wincenty", "Ignacy", "Mateusz", "Marcin",
                                               "Mieczysław", "Marek", "Jan", "Eustachy",
                                               "Kazimierz", "Ludwig", "Adam"
                                               }};
        static array<string, N> random_surnames {{"Malinowski", "Kowalski", "Mirisławski", "Kiepski",
                                               "Graczyk", "Biały", "Niecny", "Załuski",
                                               "Wolny", "Szybki", "Policki", "Wredny",
                                               "Halny", "Szmalc", "Redy"
                                               }};
        static array<string, N> random_address {{"Szczecin", "Kraków", "Warszawa", "Nowy Jork",
                                               "Waszyngton", "Londyn", "Bielsko-biała", "Zakopane",
                                               "Zielona Góra", "Jelenia Góra", "Mount Everest", "Rów mariański",
                                               "Wenus", "Księżyc", "Most"
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
