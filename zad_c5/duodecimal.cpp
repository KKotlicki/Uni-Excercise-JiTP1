#include "duodecimal.h"
#include <cmath>
// Konrad Kotlicki (310958)



int dd2int(const std::string& dd_digits)
{
    if(dd_digits.size() != 4){return -1;};
    int int_digits = 0;
    int t = 1;
    int int_digit;
    char c;
    for(int i = 0; i < 4; i++)
    {
        c = dd_digits[3 - i];
        int_digit = ddd2int(c);
        if(int_digit == -1){return -1;};
        int_digits += int_digit * t;
        t *= 12;
    };
    return int_digits;
};

int ddd2int(char c)
{
    if ('0' <= c  && c <= '9')
        return c - '0';
    if ('A' <= c  && c <= 'B')
        return c - 'A' + 10;
    if ('a' <= c  && c <= 'b')
        return c - 'a' + 10;
    return -1;
};

std::string int2dd(int val)  // ((19782  - (6 + 4*12 + 5*12^2) mod (12^4))/12^3
{
    if(val > 20735 || val < 0)
    {
        return "xxxx";
    };
    std::string dd_digits;
    std::string dd_digit;
    int int_digit;
    int substraction = 0;
    for (int i=0; i<4; i++)
    {
        int_digit = ((val - substraction) % (int) pow(12, (i+1))) / (int) pow(12, (i));
        substraction += int_digit * ((int) pow(12, (i)));
        dd_digit = int2ddd(int_digit);
        dd_digits = dd_digit + dd_digits;
    };


    return dd_digits;
};


char int2ddd(int int_digit)
{
    if (0 <= int_digit && int_digit <= 9)
    {
        char c = '0' + int_digit;
        return c;
    };
    if (10 == int_digit){return 'a';};
    if (11 == int_digit){return 'b';};

    return 'x';
};
