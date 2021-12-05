#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <sstream>
#include "fraction.h"
using namespace std;

// ustawienie wiekszej wartosci TEST_STAGE
// wlacza kolejna sekcje testow
// ostatnia sekcja ma numer 19

#define TEST_STAGE 19

int main()
{
    int errCnt = 0;
    int maxScore = 0;

#if TEST_STAGE >= 1
    // konstruktor domyslny
    {
        fraction zero;
        if (zero.numerator() != 0 || zero.denominator() != 1)
        {
            cout << "Default ctor error.\n";
            ++errCnt;
        }
    }
#endif

#if TEST_STAGE >= 2
	// konstruktor jednoparametrowy
    {
        vector<int> numerators { 2, 666, -3, -987654, };
        for (unsigned int i = 0; i < numerators.size(); ++i)
        {
            fraction one(numerators[i]);
            if (one.numerator() != numerators[i] || one.denominator() != 1)
            {
                cout << "One-argument ctor error at " << i << endl;
                ++errCnt;
            }
        }
    }
#endif

#if TEST_STAGE >= 3
	// konstruktor dwuargumentowy
    {
        vector<vector<int>> twoarg {{1, 2}, {-3, 7}, {44, -999}, {-77, -8454}};
        vector<vector<int>> twores {{1, 2}, {-3, 7}, {-44, 999}, {77, 8454}};
        for (unsigned int i = 0; i < twoarg.size(); ++i)
        {
            fraction two(twoarg[i][0], twoarg[i][1]);
            if (two.numerator() != twores[i][0] || two.denominator() != twores[i][1])
            {
                cout << "Two-argument ctor error at " << i << endl;
                ++errCnt;
            }
        }
    }
#endif

#if TEST_STAGE >= 4
    // konstruktor kopiujacy (na wypadek, gdyby kogos z Panstwa swierzbila klawiatura i zaimplementowal)
    {
        vector<vector<int>> twoarg {{1, 2}, {-3, 7}, {44, -999}, {-77, -8454}};
        for (unsigned int i = 0; i < twoarg.size(); ++i)
        {
            fraction two(twoarg[i][0], twoarg[i][1]);
            fraction cpy(two);
            if (two.numerator() != cpy.numerator() || two.denominator() != cpy.denominator())
            {
                cout << "Copy ctor error at " << i << endl;
                ++errCnt;
            }
        }
    }

    if (errCnt == 0)
        maxScore = 1;
#endif

#if TEST_STAGE >= 5
	// operator <<
    // znacznie ulatwi przyrzadzanie komunikatow bledow w testach
    // te testy nie zostawiaja Panstwu swobody w implementacji
    {
        vector<fraction> streamtest {{1, 2}, {-1, 2}, {1, 3}, {2, 1}, {-3, 1}, {148, 255}, {-255, 148}};
        vector<string> streamres {"1/2", "-1/2", "1/3", "2", "-3", "148/255", "-255/148" };
        for (unsigned int i = 0; i < streamtest.size(); ++i)
        {
            fraction right(streamtest[i]);
            stringstream ss;
            ss << right;
            if (streamres[i] != ss.str())
            {
                cout << "<< operator error at " << i << "('" << ss.str()
                    << "' written instead of '" << streamres[i] << "'\n";
                ++errCnt;
            }
        }
    }
#endif

#if TEST_STAGE >= 6
	// operator ==
    // konstruktor jeszcze nie jest przetestowany, ale operator == ulatwi nastepne testy
    {
        vector<fraction> eqtest {{1, 2}, {-1, 2}, {1, 3}, {2, 1}, {-3, 1}, {147, 255}, {-255, 147}};

        for (unsigned int i = 0; i < eqtest.size(); ++i)
            for (unsigned int j = 0; j < eqtest.size(); ++j)
            {
                fraction left(eqtest[i]);
                fraction right(eqtest[j]);

                if (left == right)
                {
                    if (i != j)
                    {
                        cout << "== operator error reported equal but " << left << " != " << right << endl;
                        ++errCnt;
                    }
                }
                else
                {
                    if (i == j)
                    {
                        cout << "== operator error reported not equal but " << left << " == " << right << endl;
                        ++errCnt;
                    }
                }
            }
    }
#endif

#if TEST_STAGE >= 7
    // konstruktor - skracanie
    {
        vector<vector<int>> twoarg {{1, 2}, {-2, 4}, {3, -6}, {4, 8}, {0, 244}, {0, -34567}, {6305, 886095}, {-35741646, 3043}, };
        vector<fraction> twores {{1, 2}, {-1, 2}, {-1, 2}, {1, 2}, {0}, {0}, {13, 1827}, {-199674, 17}, };
        for (unsigned int i = 0; i < twoarg.size(); ++i)
        {
            fraction two(twoarg[i][0], twoarg[i][1]);
            if (!(two == twores[i]))
            {
                cout << "Two-argument ctor normalization error at " << i << " expected " <<
                    twores[i] << " instead of " << two << endl;
                ++errCnt;
            }
        }
    }
#endif

#if TEST_STAGE >= 8
    // konstruktor - wyjatek
    {
        try
        {
            fraction fex(1, 0);
            cout << "Missing exception in two-argument ctor\n";
        }
        catch (invalid_argument&)
        {
            // ok. spodziewamy sie tego
        }
    }

    if (errCnt == 0)
        maxScore = 2;
#endif

#if TEST_STAGE >= 9
	// operator +=
    {
        vector<fraction> left {{1, 2}, {-1, 2}, {1, 2}, {17, 35}, };
        vector<fraction> right {{1, 4}, {1, 4}, {-1, 3}, {-19, 15}, };
        vector<fraction> res {{3, 4}, {-1, 4}, {1, 6}, {-82, 105}, };
        for (unsigned int i = 0; i < left.size(); ++i)
        {
            fraction lhf(left[i]);
            if (!((lhf += right[i]) == res[i]))
            {
                cout << "+= error at " << i << " expected " <<
                    res[i] << " instead of " << lhf << endl;
                ++errCnt;
            }
        }
    }
#endif

#if TEST_STAGE >= 10
	// operator +
    {
        vector<fraction> left {{1, 2}, {-1, 2}, {1, 2}, {17, 35}, };
        vector<fraction> right {{1, 4}, {1, 4}, {-1, 3}, {-19, 15}, };
        vector<fraction> res {{3, 4}, {-1, 4}, {1, 6}, {-82, 105}, };
        for (unsigned int i = 0; i < left.size(); ++i)
        {
            if (!((left[i] + right[i]) == res[i]))
            {
                cout << "+ error at " << i << " expected " <<
                    res[i] << " instead of " << left[i] + right[i] << endl;
                ++errCnt;
            }
        }
    }
#endif

#if TEST_STAGE >= 11
    // operator -=
    {
        vector<fraction> left {{1, 2}, {-1, 2}, {1, 2}, {17, 35}, };
        vector<fraction> right {{1, 4}, {1, 4}, {-1, 3}, {-19, 15}, };
        vector<fraction> res {{1, 4}, {-3, 4}, {5, 6}, {184, 105}, };
        for (unsigned int i = 0; i < left.size(); ++i)
        {
            fraction lhf(left[i]);
            if (!((lhf -= right[i]) == res[i]))
            {
                cout << "-= error at " << i << " expected " <<
                    res[i] << " instead of " << lhf << endl;
                ++errCnt;
            }
        }
    }
#endif

#if TEST_STAGE >= 12
    // operator -
    {
        vector<fraction> left {{1, 2}, {-1, 2}, {1, 2}, {17, 35}, };
        vector<fraction> right {{1, 4}, {1, 4}, {-1, 3}, {-19, 15}, };
        vector<fraction> res {{1, 4}, {-3, 4}, {5, 6}, {184, 105}, };
        for (unsigned int i = 0; i < left.size(); ++i)
        {
            if (!((left[i] - right[i]) == res[i]))
            {
                cout << "- error at " << i << " expected " <<
                    res[i] << " instead of " << left[i] - right[i] << endl;
                ++errCnt;
            }
        }
    }
#endif

#if TEST_STAGE >= 13
	// operator - jednoargumentowy
    {
        vector<fraction> right {{1, 4}, {-1, 77}, };
        vector<fraction> res {{-1, 4}, {1, 77}, };
        for (unsigned int i = 0; i < right.size(); ++i)
        {
            if (!( -right[i] == res[i]))
            {
                cout << "unary - error at " << i << " expected " <<
                    res[i] << " instead of " << -right[i] << endl;
                ++errCnt;
            }
        }
    }

    if (errCnt == 0)
        maxScore = 3;
#endif

#if TEST_STAGE >= 14
	// operator *=
    {
        vector<fraction> left {{1, 2}, {-1, 18}, {-10, 151}, {17, 35}, };
        vector<fraction> right {{1, 4}, {6, 17}, {-1, 2}, {-19, 15}, };
        vector<fraction> res {{1, 8}, {-1, 51}, {5, 151}, {-323, 525}, };
        for (unsigned int i = 0; i < left.size(); ++i)
        {
            fraction lhf(left[i]);
            if (!((lhf *= right[i]) == res[i]))
            {
                cout << "*= error at " << i << " expected " <<
                    res[i] << " instead of " << lhf << endl;
                ++errCnt;
            }
        }
    }
#endif

#if TEST_STAGE >= 15
	// operator *
    {
        vector<fraction> left {{1, 2}, {-1, 18}, {-10, 151}, {17, 35}, };
        vector<fraction> right {{1, 4}, {6, 17}, {-1, 2}, {-19, 15}, };
        vector<fraction> res {{1, 8}, {-1, 51}, {5, 151}, {-323, 525}, };
        for (unsigned int i = 0; i < left.size(); ++i)
        {
            if (!((left[i] * right[i]) == res[i]))
            {
                cout << "* error at " << i << " expected " <<
                    res[i] << " instead of " << left[i] * right[i] << endl;
                ++errCnt;
            }
        }
    }
#endif

#if TEST_STAGE >= 16
	// operator /=
    {
        vector<fraction> left {{1, 2}, {-1, 18}, {-10, 155}, {17, 35}, };
        vector<fraction> right {{1, 4}, {6, 17}, {-2, 1}, {-19, 15}, };
        vector<fraction> res {{2, 1}, {-17, 108}, {1, 31}, {-51, 133}, };
        for (unsigned int i = 0; i < left.size(); ++i)
        {
            fraction lhf(left[i]);
            if (!((lhf /= right[i]) == res[i]))
            {
                cout << "/= error at " << i << " expected " <<
                    res[i] << " instead of " << lhf << endl;
                ++errCnt;
            }
        }
    }
#endif

#if TEST_STAGE >= 17
	// operator /
    {
        vector<fraction> left {{1, 2}, {-1, 18}, {-10, 155}, {17, 35}, };
        vector<fraction> right {{1, 4}, {6, 17}, {-2, 1}, {-19, 15}, };
        vector<fraction> res {{2, 1}, {-17, 108}, {1, 31}, {-51, 133}, };
        for (unsigned int i = 0; i < left.size(); ++i)
        {
            if (!((left[i] / right[i]) == res[i]))
            {
                cout << "/= error at " << i << " expected " <<
                    res[i] << " instead of " << left[i] / right[i] << endl;
                ++errCnt;
            }
        }
    }

    if (errCnt == 0)
        maxScore = 4;
#endif

#if TEST_STAGE >= 18
	// operator / (wyjatek)
    {
        fraction fex(1, 2);
        try
        {
            cout << (fex /= 0) << endl;
            cout << "Missing exception in /= operator.\n";
            ++errCnt;
        }
        catch(invalid_argument&)
        {
            // tak powinno byc
        }
        try
        {
            cout << fex / 0 << endl;
            cout << "Missing exception in / operator.\n";
            ++errCnt;
        }
        catch(invalid_argument&)
        {
            // tak powinno byc
        }
    }
#endif

#if TEST_STAGE >= 19
	// operator !=
    {
        vector<fraction> eqtest {{1, 2}, {-1, 2}, {1, 3}, {2, 1}, {-3, 1}, {147, 255}, {-255, 147}};

        for (unsigned int i = 0; i < eqtest.size(); ++i)
            for (unsigned int j = 0; j < eqtest.size(); ++j)
            {
                fraction left(eqtest[i]);
                fraction right(eqtest[j]);

                if (left != right)
                {
                    if (i == j)
                    {
                        cout << "!= operator error reported not equal but " << left << " == " << right << endl;
                        ++errCnt;
                    }
                }
                else
                {
                    if (i != j)
                    {
                        cout << "!= operator error reported equal but " << left << " != " << right << endl;
                        ++errCnt;
                    }
                }
            }
    }

    if (errCnt == 0)
        maxScore = 5;
#endif

    if (errCnt == 0)
        cout << "No errors detected!\n";
    else
        cout << "Total number of errors: " << errCnt << endl;
    cout << "Current assignment maximum score: " << maxScore << endl;
    return 0;
}

