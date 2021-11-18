#pragma once
#include <iostream>
#include <vector>

// date operations in the time window <1-1-2019, 31-12-2021>
class gi_date
{
public:
    explicit gi_date(int day = 1, int month = 1, int year = 2019);

    int get_year() const;
    int get_month() const;
    int get_day() const;

    void next_day();
    void prev_day();

    gi_date& operator+=(int days);
    gi_date& operator-=(int days);

    static bool is_valid(int day, int month, int year);
    static int days_in_month(int month, int year);

private:
    const static std::vector<int> days_in_months;

    int year, month, day;
};

bool operator==(const gi_date& left, const gi_date& right);
bool operator!=(const gi_date& left, const gi_date& right);
bool operator<(const gi_date& left, const gi_date& right);

int operator-(const gi_date& left, const gi_date& right);

std::ostream& operator<<(std::ostream& os, const gi_date& right);
