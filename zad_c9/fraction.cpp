// Konrad Kotlicki (310958)
#include "fraction.h"
#include <cmath>
using namespace std;

int gcd(int m, int n)
{
    if (n == 0)
        return m;
    return gcd(n, m % n);
}

fraction::fraction(int numerator, int denominator)
{
    num = numerator;
    denom = denominator;
    if(denom == 0)
            throw std::invalid_argument("error!");
    if (denom < 0)
    {
        num = -num;
        denom = -denom;
    }
    int gc = gcd(abs(num), denom);
    if (gc != 1)
    {
        num /= gc;
        denom /= gc;
    }
}

int fraction::numerator() const
{
    return num;
}

int fraction::denominator() const
{
    return denom;
}

std::ostream& operator<<(std::ostream& os, const fraction& rhf)
{
    os << rhf.numerator();
    if (rhf.denominator() != 1)
        os << "/" << rhf.denominator();
    return os;
}

bool operator==(const fraction& left, const fraction& right)
{
    fraction(lhf) = left;
    fraction(rhf) = right;
    return lhf.numerator() == rhf.numerator() && lhf.denominator() == rhf.denominator();
}

bool operator!=(const fraction& left, const fraction& right)
{

    return !(left == right);
}

fraction& fraction::operator+=(const fraction& right)
{
    *this = fraction(
                     numerator()*right.denominator() + right.numerator() * denominator(),
                     denominator() * right.denominator());
    return *this;
}

fraction& fraction::operator-=(const fraction& right)
{
    return *this += -right;
}

fraction& fraction::operator*=(const fraction& right)
{
    *this = fraction(
                     numerator() * right.numerator(),
                     denominator() * right.denominator());
    return *this;
}

fraction& fraction::operator/=(const fraction& right)
{
    *this = fraction(
                     numerator() * right.denominator(),
                     denominator() * right.numerator());
    return *this;
}

fraction& operator +(const fraction& lhf, const fraction& rhf)
{
    fraction tmp(lhf);
    return tmp += rhf;
}

fraction& operator -(const fraction& lhf, const fraction& rhf)
{
    fraction tmp(lhf);
    return tmp -= rhf;
}

fraction& operator *(const fraction& lhf, const fraction& rhf)
{
    fraction tmp(lhf);
    return tmp *= rhf;
}

fraction& operator /(const fraction& lhf, const fraction& rhf)
{
    fraction tmp(lhf);
    return tmp /= rhf;
}

fraction operator-(const fraction& obj)
{
    fraction tmp(obj.numerator() * (-1), obj.denominator());
    return tmp;
}
