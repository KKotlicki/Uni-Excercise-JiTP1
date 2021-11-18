// Konrad Kotlicki (310958)
#include "simpleDate.h"
#include <iostream>
#include <string>
#include <set>

std::set<int> long_months = {1, 3, 5, 7, 8, 10, 12};

bool is_month_long(int mm)
{
    if(long_months.find(mm) == long_months.end()) return false;
    return true;
}

bool is_leap_year(int yy)
{
    if ((yy % 4 == 0 && !(yy % 100 == 0)) || yy % 400 == 0) return true;
    return false;
}


simpleDate::simpleDate(int dd, int mm, int yy)
: d{ dd }, m{ mm }, y{ yy }
{
if (!is_valid(d, m, y))
    throw invalid_argument();
}


bool simpleDate::is_valid(int dd, int mm, int yy)
{
    if
    (
    (2019 > yy || yy > 2021) ||
    (1 > mm || mm > 12) ||
    (1 > dd || dd > 31) ||
    (!is_month_long(mm) && dd > 30) ||
    (mm == 2 && (dd > 29 || (!is_leap_year(yy) && dd == 29)))
    ) return false;

    return true;
}


void simpleDate::print() const
{
    std::string mm = std::to_string(m);
    std::string dd = std::to_string(d);
    if (m <10) mm = "0" + mm;
    if (d <10) dd = "0" + dd;
    std::cout << y << "-" << mm << "-" << dd << std::endl;
}


void simpleDate::next_day()
{
    if
    (!(
    (d == 31) ||
    (!is_month_long(m) && d == 30) ||
    (m == 2 && (d == 29 || (!is_leap_year(y) && d == 28)))
    )) d++;

    else if(m != 12){m++; d = 1;}
    else if(y != 2021){y++; m = 1; d = 1;}
    else throw invalid_operation();
}


void simpleDate::prev_day()
{
    if(d != 1){d--; return;}

    if(y == 2019 && m == 1)throw invalid_operation();
    if(m == 1){y--; m = 12; d = 31; return;}
    m--;

    if(is_month_long(m)){d = 31;}
    else if(m == 2 && is_leap_year(y)){d = 29;}
    else if(m == 2){d = 28;}
    else d = 30;
}
