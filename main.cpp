#include <iostream>
#include <thread>
#include <string>
#include <array>
#include <time.h>
#include <chrono>
#include <vector>
#include <algorithm>
#include "person.h"
#include "date.h"
#include "pom_functions.h"

using namespace std;

void hello(int n, const string & str) {
    for(int k = 0; k < n; k++) {
        cout << str << "\n";
    }
}

template<typename T, typename F >
void persons_sort(vector<shared_ptr<T> > &vec, F f) {
    auto compare = [f](shared_ptr<T> p1, shared_ptr<T> p2) {return ((*p1).*f)() < ((*p2).*f)();};
    sort(vec.begin(), vec.end(), compare);
}

template <typename T>
void print(T t) {
    int k = 1;
    for(const auto &i : t) {
        cout << k << ".";
        spacier(4- to_string(k).length());
        cout << *i << endl;
        k++;
    }
}

int main(int argc,  char * argv[] )
{
    srand(time(nullptr));

    cout << "Dzisiejsza data to: " << date::current_date() << endl;
    cout << "Dzisiejszy rok to: " << date::current_date().getYear() << endl;   

    thread w1;
    w1 = thread(hello, 5, "hi!");
    w1.join();

    vector<int> arguments(argc - 1, 0);
    const int M = atoi(argv[1]);
    vector<shared_ptr<Person> > persons;
    vector<shared_ptr<Person> > persons_name;

    for (size_t k = 0; k < arguments.size()  ; k++) {
        arguments[k] = atoi(argv[k + 1]);
    }

    //0 - pesel
    //1 - imie
    //2 - nazwisko
    //3 - adres
    //4 - wiek
    //5 - date urodzenia

    cout << "Przeslane argumenty: \n";
    for(const &v : arguments) {
        cout << v << " ";
    }
    cout << endl;

    for(int k = 0; k < M; k++) {
        persons.push_back(make_shared<Person>(Random{}));
    }
    persons_name=persons;

    persons_sort(persons_name, &Person::get_name);

    print(persons);
    print(persons_name);
}



