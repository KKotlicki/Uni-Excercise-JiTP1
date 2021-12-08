// Konrad Kotlicki (310958)
#pragma once
#include <iostream>
#include <string>

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

    entry operator++(int)
    {
        entry retv(*this);
        cnt++;
        return retv;
    }

    bool operator<(const entry& right) const
    {
        entry tmp_obj = *this;
        return *tmp_obj < *right;
    }

    friend std::ostream& operator<<(std::ostream& os, const entry& right)
    {
        os << "[" << *right << " " << (int) right << "]";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, entry& right)
    {
        std::string val;
        int cnt;
        is >> val >> cnt;
        right.val = val;
        right.cnt = cnt;
        return is;
    }

private:
    std::string val;
    int cnt;
};
