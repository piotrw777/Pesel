# Pesel
 Zadanie dodatkowe z biblioteki standardowej
 
 
1) Posiadamy interfejs PersonIf:

class PersonIf {
   public:
       virtual const std::string & get_name() const = 0;
       virtual const std::string & get_surname() const = 0;
       virtual const std::string & get_address() const = 0;

       virtual const int get_age() const = 0;
       // zwróci string w formacie "YYYY.MM.DD" 
       virtual const std::string get_date_of_birth() const = 0;
       virtual const long long get_pesel() const = 0;
}

2) Trzeba stworzyć klasę Person, która implementuje powyższy interfejs.

class Person : public PersonIf {
    const std::string & get_name() const
    {
    	//odpowiednia implementacja
    }
}

Wszystkie inne potrzebne metody, konstruktory, destruktory - wedle uznania.

3) Potrzebujemy generatora osób. Osoby powinny spełniać zgodność wieku z numerem pesel.
Pesel wszystkich wygenerowanych osób musi spełniać kryteria peselu dla pierwszych 6 cyfr.
5 ostatnich cyfr - może być losowych(nie ma potrzeby umieszczania sumy kontrolnej i płci)

YYMMDDabcde 
- YY - ostatnie 2 cyfry roku urodzenia
- MM - numer miesiąc dla osób sprzed 2000, lub numer miesiąca + 20 dla osób po 2000
- DD - numer dnia
- abcde - losowe z zakresu 00000-99999

Przykład, dla osoby urodzonej 20 października 1990 roku:
       
       virtual const int get_age() const = 0;
       // zwraca jej aktualny wiek, (dla uproszczenia wystarczy 'rocznikowo'), 
       // czyli dla 15 maja 2020 - zwróci wartość 30
       
       virtual const std::string get_date_of_birth() const = 0;
       // zwróci string "1990.10.20"
       
       virtual const long long get_pesel() const = 0;
       // zwróci liczbę 901020nnnnn


4) program ma przyjmować 1+3*N parametrów

Pierwszy argument - ilość osób które mają zostac wygenerowane i umieszczone w strukturach, zakres : 1-1.000.000
argument 2,3,4 - 
	(2)z jakiego pola ma wypisac posortowane dane
	(3)od jakiej pozycji[numerujemy od 1]
	(4)ilosć pozycji do wypisania
	
argument 5,6,7 - jak wyżej, pole, pozycja, ilość
argument 8,9,10 - ...

Pole: 
0- pesel
1- imie
2- nazwisko
3- adres
4- wiek
5- data urodzenia

Przykład :
<program> 10000 0 1 1 2 20 50
- stworzy 10.000 osób, 
- odpowiednio je posortuje 
- ze wszystkich osób posortowanych po peselu, wypisze pierwszą,
- ze wszystkich osób posortowanych po nazwisku, wypisze 50 osób, od pozycji 20, czyli osoby 20-69
- zakończy się

Uwaga : proszę aby program był zgodny z tym interfejsem. Program w trakcie działania nie powinien pytać o żadne inne rzeczy.

5) przykład możliwych struktur do użycia :

[0] std::map<'pesel', std::shared_ptr<Person>> id_people;

oraz zbiory:

[1] std::set<std::shared_ptr<Person>, ??> sort_name;
[2] std::set<std::shared_ptr<Person>, ??> sort_surname;
[3] std::set<std::shared_ptr<Person>, ??> sort_address;
[4] std::set<std::shared_ptr<Person>, ??> sort_age;
[5] std::set<std::shared_ptr<Person>, ??> sort_dob;//date of birth

6) Kolejność działań

W pierwszym kroku program stworzy i posortuje dane.
W drugim kroku wykona polecenia użytkownika co do odpowiedniego wypisania danych.
W drugim kroku program korzysta z posortowanych danych. (nie sortuje na bieżąco)

7) Nie-duplikowalność danych

Po stworzeniu instancji obiektu Person, obiekt i jego pola będą zajmować miejsca w pamięci.
Jeśli ten obiekt miałby być przechowywany w kilku miejscach, należy się zastanowić jak ograniczyć kopiowanie tego obiektu,
a zamiast kopii trzymać logiczne powiązania do oryginalnego obiektu.

8) Kwestie opcjonalne (które jeśli będą, będą brane pod uwagę na plus):

a) sprawdzanie poprawności dat (czyli 30 luty to data nieprawidłowa) i/lub lat przestępnych.
b) wykorzystanie wielowątkowości - np. do tworzenia, sortowania, (liczba wątków może być ustawiona w zmiennej)




Pojawiło się pytanie:

"Metoda zwracająca numer pesel zwraca pesel jako zmienną long long, w przypadku osoby z roku 2000 pierwsze dwie cyfry tej liczby będą zerami co da pesel o 2 cyfry krótszy (MMDDXXXXX) zamiast (YYMMDDXXXXX). Zostawiamy to w taki sposób ?"

Tak. Liczba jest long long i tak to zostawiamy. W zależności od rocznika urodzenia, będzie od 9 do 11-cyfrowej.
Proszę na to zwrócić uwagę przy funkcji sortującej po peselu. Być może będzie konieczność zdefiniowania jej trochę inaczej, niż zwykłych liczb long long.

Sortowanie alfanumeryczne da kolejność(5 losowych liczb dla uproszczenia zostało usuniętych):
2101
10101
100101
110101
990101

Z kolei rocznikowo:
990101
  2101
 10101
100101
110101


