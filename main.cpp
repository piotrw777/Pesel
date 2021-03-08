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
#include <map>

using namespace std;

void hello(int n, const string & str) {
    for(int k = 0; k < n; k++) {
        cout << str << "\n";
    }
}
bool str_less(const string &s1, const string &s2) {
    int m = min(s1.length(), s2.length());
    int k = 0;
    while(s1[k] == s2[k] && k < m) k++;
    if(k == m) return s1.length() < s2.length();
    else return s1[k] < s2[k];
}

bool operator<(const string &s1, const string &s2){
    return str_less(s1, s2);
}

template<typename T, typename F >
void persons_sort(vector<shared_ptr<T> > &vec, F f) {
    auto compare = [f](shared_ptr<T> p1, shared_ptr<T> p2) {return ((*p1).*f)() < ((*p2).*f)();};
    sort(vec.begin(), vec.end(), compare);
}

template<typename T>
void persons_sort(vector<shared_ptr<T> > &vec) {
    sort(vec.begin(), vec.end());
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

template <typename T>
void print(T t, int ile) {
    for(int k = 0; k < ile; k++)
        cout << **t++ << endl;
    cout << endl;
}
int main(int argc,  char * argv[] )
{
    srand(time(nullptr));

    cout << "Dzisiejsza data to: " << date::current_date() << endl;
    cout << "Dzisiejszy rok to: " << date::current_date().getYear() << endl;   
    map<int, string> task = {{0,"peselu"}, {1, "imieniu"}, {2, "nazwisku"},
                             {3,"adresie"}, {4, "wieku"}, {5, "dacie urodzenia"}};
//    thread w1;
//    w1 = thread(hello, 5, "hi!");
//    w1.join();

    vector<int> arguments(argc - 2, 0);

    int M;
    if(argc == 1) {
       cout << "Nie podano argumentow!";
       exit(1);
    }
    M = atoi(argv[1]);
    vector<shared_ptr<Person> > persons;

    vector<shared_ptr<Person> > persons_pesel; //0
    vector<shared_ptr<Person> > persons_name;  //1
    vector<shared_ptr<Person> > persons_surname; //2
    vector<shared_ptr<Person> > persons_address; //3
    vector<shared_ptr<Person> > persons_age;    //4
    vector<shared_ptr<Person> > persons_date_of_birth; //5

    for (size_t k = 0; k < arguments.size()  ; k++) {
        arguments[k] = atoi(argv[k + 2]);
    }

    //0 - pesel
    //1 - imie
    //2 - nazwisko
    //3 - adres
    //4 - wiek
    //5 - date urodzenia

    cout << "Przeslane argumenty: \n";
    for(const auto &v : arguments) {
        cout << v << " ";
    }

    cout << endl;
    //tworzenie listy osób
    for(int k = 0; k < M; k++) {
        persons.push_back(make_shared<Person>(Random{}));
    }
    //tworzymy shared pointery
    persons_date_of_birth=persons_age=persons_address=persons_surname=persons_name=persons_pesel=persons;
    //sortujemy
    persons_sort(persons_pesel, &Person::get_pesel);
    persons_sort(persons_name, &Person::get_name);
    persons_sort(persons_surname, &Person::get_surname);
    persons_sort(persons_age, &Person::get_age);
    persons_sort(persons_address, &Person::get_address);
    persons_sort(persons_date_of_birth, &Person::get_date);

    int nr_zad = 1;
    int start_position;
    vector<shared_ptr<Person> >::iterator start_iterator;
    int list_len;
    int case_nr;
    cout << "Lista wygenerowanych osob: \n";
    print(persons);

    for(size_t k = 0; k < arguments.size() ; k += 3) {
        cout << "Zadanie nr " << nr_zad++ << " - ";
        cout << "Sortowanie po " << task[arguments[k]] << endl;
        cout << arguments[k] <<" " << arguments[k+1] << " " << arguments[k+2] << endl;

        case_nr = arguments[k];
        start_position = arguments[k + 1];
        list_len = arguments[k + 2];

        switch (case_nr) {
        case 0:
            start_iterator = persons_pesel.begin() + start_position - 1;
            print(start_iterator, list_len);
            break;
        case 1:
            start_iterator = persons_name.begin() + start_position - 1;
            print(start_iterator, list_len);
            break;
        case 2:
            start_iterator = persons_surname.begin() + start_position - 1;
            print(start_iterator, list_len);
            break;
        case 3:
            start_iterator = persons_address.begin() + start_position - 1;
            print(start_iterator, list_len);
            break;
        case 4:
            start_iterator = persons_age.begin() + start_position - 1;
            print(start_iterator, list_len);
            break;
        case 5:
            start_iterator = persons_date_of_birth.begin() + start_position - 1;
            print(start_iterator, list_len);
            break;
        }
    }
    cout << "Koniec programu";
}
