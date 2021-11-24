// Konrad Kotlicki (310958)
#include "gidate.h"
#include <iomanip>
using namespace std;

const vector<int> gi_date::days_in_months
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

gi_date::gi_date(int day, int month, int year)
{
    if (!is_valid(day, month, year))
        throw invalid_argument("Invalid date in gi_date::gi_date().");
    if(year == 2019)
        days_since_start = 0;
    else if(year == 2020)
        days_since_start = 365;
    else
        days_since_start = 731;
    for(int i = 1; i < month; i++)
        days_since_start += days_in_month(i, year);
    days_since_start += day - 1;
}


int gi_date::get_year() const
{
    int days_since_current_year = days_since_start;
    int current_year = 2019;

    while(days_since_current_year + 1 > days_in_year(current_year))
        days_since_current_year -= days_in_year(current_year++);

    return current_year;
}

int gi_date::get_month() const
{
    int days_since_current_date = days_since_start;
    int current_year = 2019;
    int current_month = 1;

    while(days_since_current_date + 1 > days_in_year(current_year))
        days_since_current_date -= days_in_year(current_year++);

    while(days_since_current_date + 1 > days_in_month(current_month, current_year))
        days_since_current_date -= days_in_month(current_month++, current_year);

    return current_month;
}

int gi_date::get_day() const
{
        int days_since_current_date = days_since_start;
    int current_year = 2019;
    int current_month = 1;

    while(days_since_current_date + 1 > days_in_year(current_year))
        days_since_current_date -= days_in_year(current_year++);

    while(days_since_current_date + 1 > days_in_month(current_month, current_year))
        days_since_current_date -= days_in_month(current_month++, current_year);

    return days_since_current_date + 1;
}

void gi_date::next_day()
{
    if(days_since_start != max_day)
        days_since_start++;
}

void gi_date::prev_day()
{
    if(days_since_start != 0)
        days_since_start--;
}

gi_date& gi_date::operator+=(int days)
{
    if(days_since_start <= -days)
       days_since_start = 0;
    else if(days_since_start + days >= max_day)
        days_since_start = max_day;
    else days_since_start += days;
    return *this;
}

gi_date& gi_date::operator-=(int days)
{
    return *this += -days;
}

bool gi_date::is_valid(int day, int month, int year)
{
    if (year < 2019 || 2021 < year)
        return false;
    if (month < 1 || 12 < month)
        return false;
    if (day < 1 || days_in_month(month, year) < day)
        return false;
    return true;
}

int gi_date::days_in_month(int month, int year)
{
    if (1 <= month && month <= 12 && month != 2)
        return days_in_months[month - 1];
    if (month == 2)
    {
        if (year % 4 == 0)
            return days_in_months[month - 1] + 1;
        else
            return days_in_months[month - 1];
    }
    return 0;
}

int gi_date::days_in_year(int year)
{
    if(year == 2019)
        return 365;
    if(year == 2020)
        return 366;
    if(year == 2021)
        return 365;
    return 0;
}

bool operator==(const gi_date& left, const gi_date& right)
{
    return left.diff(right) == 0;
}

bool operator!=(const gi_date& left, const gi_date& right)
{
    return ! (left == right);
}

bool operator<(const gi_date& left, const gi_date& right)
{
    return left.diff(right) < 0;
}

int operator-(const gi_date& left, const gi_date& right)
{
    int diff = left.diff(right);
    return diff;
}

std::ostream& operator<<(std::ostream& os, const gi_date& right)
{
    os << right.get_year()
     << '-' << setfill('0') << setw(2)<< right.get_month()
     << '-'<< setfill('0') << setw(2) << right.get_day();
    return os;
}

int gi_date::diff(const gi_date& right) const
{
    return days_since_start - right.days_since_start;
}
