// Konrad Kotlicki (310958)
//#include <iostream>
#include <sstream>
#pragma once
class fraction
{
public:
    fraction(int numerator = 0, int denominator = 1);
    int numerator() const;
    int denominator() const;
    fraction& operator+=(const fraction& rhf);
    fraction& operator-=(const fraction& rhf);
    fraction& operator*=(const fraction& rhf);
    fraction& operator/=(const fraction& rhf);

private:
    int num, denom;
    friend fraction operator-(const fraction& obj);
};

int gcd(int m, int n);
std::ostream& operator<<(std::ostream& os, const fraction& rhf);

bool operator==(const fraction& left, const fraction& right);
bool operator!=(const fraction& left, const fraction& right);

fraction& operator+(const fraction& left, const fraction& right);
fraction& operator-(const fraction& left, const fraction& right);
fraction& operator*(const fraction& left, const fraction& right);
fraction& operator/(const fraction& left, const fraction& right);
