// Konrad Kotlicki (310958)
#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>

class entry
{

public:
    entry(const std::string& value)
    {
        val = value;
        cnt = 0;
    }

    std::string operator*() const
    {
        return val;
    }

    operator int() const
    {
        return cnt;
    }

    operator++(int)
    {
        if(cnt == INT_MAX) throw std::overflow_error("Object count overflow (must be in integer range).");
        return cnt++;
    }

    bool operator<(const entry& rhf) const
    {
        return val < rhf.val;
    }

    friend std::ostream& operator<<(std::ostream& os, const entry& rhf)
    {
        os << "[" << *rhf << " " << (int) rhf << "]";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, entry& rhf)
    {
        char start = '*', stop = '*';
        is >> start >> rhf.val >> rhf.cnt >> stop;
        if (start != '[' || stop != ']')
            throw std::invalid_argument("Invalid entry on input stream.");
        return is;
    }

private:
    std::string val;
    int cnt;
};
