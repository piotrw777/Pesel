#include <iostream>
#include "date.h"
#include <chrono>

bool date::check_date(int d, int m, int y) {
    string errange = "error range";
    string errleap = "error leap year";

    if(m < 1 || m > 12 || d < 1 || y < 1582) return false;
    bool leap_year = ( (y % 4 == 0) && (y % 100 != 0) ) | ( y % 400 == 0 );
    if(d > date::month_days[m] + ( (m == 2) && (leap_year == true) )  ) return false;

    return true;
}

date date::current_date() {
    auto current_date = chrono::system_clock::now();
    time_t current_time = chrono::system_clock::to_time_t(current_date);
    struct tm *timeinfo;
    timeinfo = localtime(&current_time);
    return date(timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900);
}

ostream & operator<<(ostream &out, const date &d) {
    out << d.getDay() << "." << d.getMonth() << "." <<  d.getYear();
    return out;
}

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
