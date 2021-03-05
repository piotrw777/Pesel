#ifndef DATE_H
#define DATE_H

#include <string>

using namespace std;

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

    static bool check_date(int d, int m, int y);

    static date current_date();

    friend ostream & operator<<(ostream &out, const date & d);

private:
    int day;
    int month;
    int year;
    static int month_days[13];
};


#endif // DATE_H
