#pragma once
#include <iostream>
#include <stdexcept>

class fraction
{

public:
    fraction(int numerator=0, int denominator=1)
    {
        num = numerator;
        denom = denominator;

        if(denom == 0)
            throw std::invalid_argument("error!");

        if(denom < 0)
        {
            num=-num;
            denom=-denom;
        }

        int gc = gcd(abs(num), denom);
        if(gc != 1)
        {
            num /= gc;
            denom /= gc;
        }
    }

    int numerator() const
    {
        return num;
    }
    int denominator() const
    {
        return denom;
    }

    fraction& operator+=(const fraction& rhf)
    {
        *this = fraction(
                         numerator()*rhf.denominator() + rhf.numerator() * denominator(),
                         denominator() * rhf.denominator());
        return *this;
    }

    friend fraction operator +(const fraction& lhf, const fraction& rhf)
    {
        fraction tmp(lhf);
        return tmp += rhf;
    }

    friend std::ostream& operator<<(std::ostream& os, const fraction& rhf)
    {
        os << rhf.numerator();
        if (rhf.denominator() != 1)
            os << '/' << rhf.denominator();
        return os;
    }

private:
    int num;
    int denom;

    int gcd(int m, int n)
    {
        if (n==0)
            return m;
        return (gcd (n, m%n));
    }
};
