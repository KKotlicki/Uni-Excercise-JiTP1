#include "gidate.h"
#include <iomanip>
using namespace std;

const vector<int> gi_date::days_in_months
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

gi_date::gi_date(int day, int month, int year)
{
    if (!is_valid(day, month, year))
        throw invalid_argument("Invalid date in gi_date::gi_date().");
    gi_date::day = day;
    gi_date::month = month;
    gi_date::year = year;
}

int gi_date::get_year() const
{
    return year;
}

int gi_date::get_month() const
{
    return month;
}

int gi_date::get_day() const
{
    return day;
}

void gi_date::next_day()
{
    if (++day > days_in_month(month, year))
    {
        day = 1;
        if (++month > 12)
        {
            month = 1;
            if (++year > 2021)
            {
                year = 2021;
                month = 12;
                day = days_in_month(month, year);
            }
        }
    }
}

void gi_date::prev_day()
{
    if (--day < 1)
    {
        if (--month < 1)
        {
            if (--year < 2019)
            {
                day = 1;
                month = 1;
                year = 2019;
            }
            else
            {
                month = 12;
                day = days_in_month(month, year);
            }
        }
        else
            day = days_in_month(month, year);
    }
}

gi_date& gi_date::operator+=(int days)
{
    while (days > 0 && *this != gi_date(31, 12, 2021))
    {
        next_day();
        --days;
    }
    while (days < 0 && *this != gi_date(1, 1, 2019))
    {
        prev_day();
        ++days;
    }
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

bool operator==(const gi_date& left, const gi_date& right)
{
    return left.get_year() == right.get_year() &&
            left.get_month() == right.get_month() &&
            left.get_day() == right.get_day();
}

bool operator!=(const gi_date& left, const gi_date& right)
{
    return ! (left == right);
}

bool operator<(const gi_date& left, const gi_date& right)
{
    if (left.get_year() < right.get_year())
        return true;
    else if (left.get_year() == right.get_year())
    {
        if (left.get_month() < right.get_month())
            return true;
        else if (left.get_month() == right.get_month())
            return left.get_day() < right.get_day();
    }
    return false;
}
int operator-(const gi_date& left, const gi_date& right)
{
    int diff = 0;
    if (left < right)
    {
        for (gi_date cpy(left); cpy != right; cpy.next_day())
            --diff;
    }
    if (right < left)
    {
        for (gi_date cpy(left); cpy != right; cpy.prev_day())
            ++diff;
    }
    return diff;
}

std::ostream& operator<<(std::ostream& os, const gi_date& right)
{
    os << right.get_year() << '-' << setfill('0') << setw(2)
        << right.get_month() << '-' << right.get_day();
    return os;
}
