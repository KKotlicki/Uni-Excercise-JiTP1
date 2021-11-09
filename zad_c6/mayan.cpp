// Konrad Kotlicki (310958)
#include "mayan.h"
#include <limits>
#include <stdexcept>
#include <cmath>


void is_uint_sum_overflow(unsigned int a, unsigned int b, const std::string& ex_message)
{
    if(a > std::numeric_limits<unsigned int>::max() - b)
        throw std::runtime_error(ex_message);
}


void is_too_many_mayan_digits(int mayan_length, const std::string& ex_message)
{
    if(mayan_length > log(std::numeric_limits<unsigned int>::max())/std::log(mayan_base) + 1)
        throw std::runtime_error(ex_message);
}


char uint2md(unsigned int uint_digit)
{
    if (uint_digit <= 9)
        return '0' + uint_digit;
    if (10 <= uint_digit && uint_digit <= mayan_base - 1)
        return ((char) uint_digit + 'a' - 10);
    throw std::runtime_error("<uint2md>: Digit outside of range!");
};


unsigned int md2uint(char mayan_digit)
{
    if ('0' <= mayan_digit  && mayan_digit <= '9')
        return mayan_digit - '0';
    if ('A' <= mayan_digit  && mayan_digit <= 'A' + mayan_base - 11)
        return mayan_digit - 'A' + 10;
    if ('a' <= mayan_digit  && mayan_digit <= 'a' + mayan_base - 11)
        return mayan_digit - 'a' + 10;
    throw std::runtime_error("<md2uint>: Unsupported Character!");
};


unsigned int mayan2uint(const std::string& mayan_digits)
{
    int mayan_length = mayan_digits.size();

    is_too_many_mayan_digits(mayan_length, "<mayan2uint>: Mayan Value too large!");

    char mayan_digit;
    int mayan_digit_value;
    unsigned int uint_value = 0;
    unsigned int partial_uint_value = 0;

    for(int i = 0; i < mayan_length; i++)
    {
        mayan_digit = mayan_digits[i];
        mayan_digit_value = md2uint(mayan_digit);
        partial_uint_value = mayan_digit_value * pow(mayan_base, mayan_length - i - 1);

        is_uint_sum_overflow(uint_value, partial_uint_value, "<mayan2uint>: Mayan Value too large!");

        uint_value += partial_uint_value;
    };

    return uint_value;
};


std::string uint2mayan(unsigned int uint_value)
{
    std::string mayan_digits;
    char mayan_digit;
    int uint_value_by_mayan_quotient = uint_value;
    unsigned int remainder;
    do
    {
        remainder = uint_value_by_mayan_quotient % mayan_base;
        uint_value_by_mayan_quotient = uint_value_by_mayan_quotient / mayan_base;
        mayan_digit = uint2md(remainder);
        mayan_digits = mayan_digit + mayan_digits;
    } while(uint_value_by_mayan_quotient >= 1);

    return mayan_digits;
};
