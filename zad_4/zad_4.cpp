#include "gidate.h"
#include <cassert>
#include <iostream>
#include <iomanip>
using namespace std;

ostream& operator<<(ostream& os, const vector<int>& src)
{
    assert(src.size() >= 3);
    os << src[2] << '-' << setfill('0') << setw(2) << src[1] << '-' << src[0];
    return os;
}

int main()
{
    int totalErrors = 0;

    // constructor exceptions tests
    cout << "gi_date ctor with invalid dates\n";
    vector<vector <int>> invDate = {
        {-1, 2, 2019}, {4, -2, 2020}, {1, 11, -3}, {0, 3, 2017}, {28, 0, 2020}, {1, 1, 0},
        {2, 2, 2017}, {4, 3, 2023}, {87, 11, 2019}, {12, 34, 2018}, {29, 2, 2019},
        {31, 4, 2018}, {31, 6, 2020}, {31, 11, 2019}, {12, 11, 765}, {12, 13, 2017},
        {28, 2, 2017}, {1, 3, 2022}, {31, 9, 2018}, {30, 2, 2019}, {2, 2, 2022} };

    int errCnt = 0;
    for (unsigned int i = 0; i < invDate.size(); i++)
    {
        try
        {
            gi_date d1(invDate[i][0], invDate[i][1], invDate[i][2]);
            cout << "\tMissing exception in ctor test: " << i << " for "
                << invDate[i] << endl;
            ++errCnt;
        }
        catch (invalid_argument& )
        {

        }
    }
    if (errCnt == 0)
        cout << "OK\n";
    else
        cout << "**** " << errCnt << " error(s)\n";
    totalErrors += errCnt;


    // gi_date ctor & get_xxx tests with valid dates

    vector<vector <int>> vDate = {
        {31, 1, 2019}, {28, 2, 2019}, {1, 3, 2019}, {2, 4, 2019}, {3, 5, 2019}, {4, 6, 2019}, {5, 7, 2019},
        {6, 8, 2019}, {7, 9, 2019}, {8, 10, 2019}, {9, 11, 2019}, {10, 12, 2019},
        {11, 1, 2020}, {12, 2, 2020}, {29, 2, 2020}, {13, 3, 2020}, {14, 4, 2020}, {15, 5, 2020}, {16, 6, 2020},
        {17, 7, 2020}, {18, 8, 2020}, {19, 9, 2020}, {20, 10, 2020}, {21, 11, 2020}, {22, 12, 2020},
        {23, 1, 2021}, {24, 2, 2021}, {25, 3, 2021}, {26, 4, 2021}, {27, 5, 2021},  {28, 6, 2021},
        {29, 7, 2021}, {30, 8, 2021}, {30, 9, 2021}, {31, 10, 2021}, {30, 11, 2021}, {31, 12, 2021}
        };

    cout << "gi_date ctor with valid dates\n";
    errCnt = 0;
    for (unsigned int i = 0; i < vDate.size(); i++)
    {
        try
        {
            gi_date d1(vDate[i][0], vDate[i][1], vDate[i][2]);
            if (d1.get_day() != vDate[i][0] || d1.get_month() != vDate[i][1] || d1.get_year() != vDate[i][2])
            {
                cout << "\tInvalid date created in test: " << i << " for "
                        << vDate[i] << " (gi_date contains: " << d1 << " instead)\n";
                ++errCnt;
            }
        }
        catch (invalid_argument&)
        {
            cout << "\tUnexpected exception in create test: " << i << " for "
                << vDate[i] << endl;
            ++errCnt;
        }
    }
    if (errCnt == 0)
        cout << "OK\n";
    else
        cout << "**** " << errCnt << " error(s)\n";
    totalErrors += errCnt;

    // == operator tests
    cout << "gi_date == operator tests\n";
    errCnt = 0;
    for (unsigned int idxleft = 0; idxleft < vDate.size(); ++idxleft)
    {
        for (unsigned int idxright = 0; idxright < vDate.size(); ++idxright)
        {
            gi_date left(vDate[idxleft][0], vDate[idxleft][1], vDate[idxleft][2]);
            gi_date right(vDate[idxright][0], vDate[idxright][1], vDate[idxright][2]);
            if (idxleft != idxright)
            {
                // different dates
                if (left == right)
                {
                    cout << "\t(==) Not equal: " << left << " and " << right << endl;
                    ++errCnt;
                }
            }
            else
            {
                // the same date
                if ( ! (left == right))
                {
                    cout << "\t(==) Equal: " << left << " and " << right << endl;
                    ++errCnt;
                }
            }
        }
    }
    if (errCnt == 0)
        cout << "OK\n";
    else
        cout << "**** " << errCnt << " error(s)\n";
    totalErrors += errCnt;

    vector<vector <int>> nxtDate = {
        {1, 1, 2019}, {13, 4, 2019}, {24, 7, 2019}, {30, 10, 2019},
        {8, 2, 2020}, {12, 5, 2020}, {20, 8, 2020}, {29, 11, 2020},
        {5, 3, 2021}, {19, 6, 2021}, {29, 9, 2021}, {30, 12, 2021},
        {31, 1, 2019}, {28, 2, 2019}, {29, 2, 2020}, {28, 2, 2021}, {31, 3, 2019}, {30, 4, 2020}, {31, 5, 2021},
        {30, 6, 2019}, {31, 7, 2020}, {31, 8, 2021}, {30, 9, 2019}, {31, 10, 2020}, {30, 11, 2021},
        {31, 12, 2019}, {31, 12, 2020},
        };
    vector<vector <int>> nxtRes = {
        {2, 1, 2019}, {14, 4, 2019}, {25, 7, 2019}, {31, 10, 2019},
        {9, 2, 2020}, {13, 5, 2020}, {21, 8, 2020}, {30, 11, 2020},
        {6, 3, 2021}, {20, 6, 2021}, {30, 9, 2021}, {31, 12, 2021},
        {1, 2, 2019}, {1, 3, 2019}, {1, 3, 2020}, {1, 3, 2021}, {1, 4, 2019}, {1, 5, 2020}, {1, 6, 2021},
        {1, 7, 2019}, {1, 8, 2020}, {1, 9, 2021}, {1, 10, 2019}, {1, 11, 2020}, {1, 12, 2021},
        {1, 1, 2020}, {1, 1, 2021},
        };


    // gi_date next_day tests
    cout << "gi_date next_day\n";
    errCnt = 0;
    for (unsigned int i = 0; i < nxtDate.size(); i++)
    {
        gi_date d1(nxtDate[i][0], nxtDate[i][1], nxtDate[i][2]);
        gi_date result(nxtRes[i][0], nxtRes[i][1], nxtRes[i][2]);
        d1.next_day();
        if (d1 != result)
        {
            cout << "\tError after next_day in test: " << i << " for " <<
                nxtDate[i] << " (simpleDate contains: " << d1 << " instead)\n";
            ++errCnt;
        }
    }
    if (errCnt == 0)
        cout << "OK\n";
    else
        cout << "**** " << errCnt << " error(s)\n";
    totalErrors += errCnt;

    vector<vector <int>> prvDate = {
        {9, 1, 2019}, {13, 4, 2019}, {24, 7, 2019}, {31, 10, 2019},
        {8, 2, 2020}, {12, 5, 2020}, {20, 8, 2020}, {30, 11, 2020},
        {5, 3, 2021}, {19, 6, 2021}, {29, 9, 2021}, {31, 12, 2021},
        {2, 1, 2019}, {1, 2, 2020}, {1, 3, 2019}, {1, 3, 2020}, {1, 3, 2021}, {1, 4, 2019}, {1, 5, 2020}, {1, 6, 2019},
        {1, 7, 2020}, {1, 8, 2021}, {1, 9, 2019}, {1, 10, 2020}, {1, 11, 2021}, {1, 12, 2019},
        {1, 1, 2020}, {1, 1, 2021},
        };
    vector<vector <int>> prvRes = {
        {8, 1, 2019}, {12, 4, 2019}, {23, 7, 2019}, {30, 10, 2019},
        {7, 2, 2020}, {11, 5, 2020}, {19, 8, 2020}, {29, 11, 2020},
        {4, 3, 2021}, {18, 6, 2021}, {28, 9, 2021}, {30, 12, 2021},
        {1, 1, 2019}, {31, 1, 2020}, {28, 2, 2019}, {29, 2, 2020}, {28, 2, 2021}, {31, 3, 2019}, {30, 4, 2020}, {31, 5, 2019},
        {30, 6, 2020}, {31, 7, 2021}, {31, 8, 2019}, {30, 9, 2020}, {31, 10, 2021}, {30, 11, 2019},
        {31, 12, 2019}, {31, 12, 2020},
        };

    // gi_date prev_day tests
    cout << "gi_date prev_day\n";
    errCnt = 0;
    for (unsigned int i = 0; i < prvDate.size(); i++)
    {
        try
        {
            gi_date d1(prvDate[i][0], prvDate[i][1], prvDate[i][2]);
            gi_date result(prvRes[i][0], prvRes[i][1], prvRes[i][2]);

            d1.prev_day();
            if (d1 != result)
            {
                cout << "\tError after prev_day in test: " << i << " for " << prvDate[i]
                    << " (simpleDate contains: " << d1 << " instead)\n";
                ++errCnt;
            }
        }
        catch (invalid_argument&)
        {
            cout << "\tUnexpected exception in create test: " << i << " for " <<
                prvDate[i][0] << "-" << prvDate[i][1] << "-" << prvDate[i][2] << endl;
            ++errCnt;
        }
    }
    if (errCnt == 0)
        cout << "OK\n";
    else
        cout << "**** " << errCnt << " error(s)\n";
    totalErrors += errCnt;

    // counting forward and backward
    vector<int> date_shift_values = {1, 7, 13, 37, 53, 71, 97, 163, 251, 367, 419, 557, 733, 971, 1095 };

    cout << "gi_date counting forward and backward\n";
    errCnt = 0;
    for (unsigned int idx = 0; idx < date_shift_values.size(); idx++)
    {
        gi_date uno(1, 1, 2019);
        gi_date due(uno);
        gi_date tre(due);

        // checking next_day() and +=
        for (int rep = 0; rep < date_shift_values[idx]; rep++)
            uno.next_day();
        due += date_shift_values[idx];
        if (!(uno == due))
        {
            cout << "\tError in += for " << date_shift_values[idx] << " result " << due << " instead of " << uno << endl;
            errCnt++;
        }
        // checking -
        int res = uno - tre;
        if (res != date_shift_values[idx])
        {
            cout << "Error in - operator: expected " << date_shift_values[idx]
                << "  received " << res << endl;
            errCnt++;
        }

        // outside range counting
        gi_date last_day(31, 12, 2021);
        tre = due;
        due += 1096 - date_shift_values[idx];

        if (due != last_day)
        {
            cout << "+= not at the last day." << endl;
            errCnt++;
        }

        gi_date first_day(1, 1, 2019);
        due = tre;
        due += - 2 * date_shift_values[idx];
        if (due != first_day)
        {
            cout << "+= not at the first day." << endl;
            errCnt++;
        }

        // checking prev_day() and +=
        due = uno = gi_date(31, 12, 2021);
        for (int rep = 0; rep < date_shift_values[idx]; rep++)
            uno.prev_day();
        due += -date_shift_values[idx];
        if (!(uno == due))
        {
            cout << "\tError in -= for " << -date_shift_values[idx] << " result " << due << " instead of " << uno << endl;
            errCnt++;
        }
    }
    if (errCnt == 0)
        cout << "OK\n";
    else
        cout << "**** " << errCnt << " error(s)\n";
    totalErrors += errCnt;


    cout << "\nAll tests completed ";
    if (totalErrors == 0)
        cout << "without errors.\n";
    else
        cout << "with " << totalErrors << " error(s).\n";

    return 0;
}
