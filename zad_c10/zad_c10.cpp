// Konrad Kotlicki (310958)
#include "entry.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    int err_cnt = 0;
    // construction of entry class
    entry tst1("Yossarian");

    //operator* test
    if (*tst1 != "Yossarian")
    {
        cout << "operator* Error" << endl;
        err_cnt++;
    }

    //operator (int) test
    if ((int) tst1 != 0)
    {
        cout << "operator (int) Error" << endl;
        err_cnt++;
    }

    // operator++ test
    entry tst2 = tst1++;
    if ((int)tst1 != (int)tst2 + 1)
    {
        cout << "operator++ Error" << endl;
        err_cnt++;
    }

    // operator < test
    entry tst3("Clevinger");
    if ((tst1 < tst2) || !(tst3 < tst2))
    {
        cout << "operator< Error" << endl;
        err_cnt++;
    }

    // print operator<<
    stringstream os_test1;
    os_test1 << "[" << *tst1 << " " << (int) tst1 << "]";
    stringstream os_test2;
    os_test2 << tst1;
    while (!os_test1.eof() && !os_test2.eof())
    {
        string str1;
        string str2;
        os_test1 >> str1;
        os_test2 >> str2;
        if (str1 != str2)
        {
            cout << "operator<< Error" << endl;
            err_cnt++;
            break;
        }
    }

    // Print operator>> to check visually for mistakes
    // I do not know how to test automatically this function
    cout << "Check if operator>> works properly. Should be \"[Milo 234]\":" << endl;;
    stringstream is_test1;
    is_test1 << "Milo" << " " << "234";
    is_test1 >> tst1;
    cout << tst1 << endl << endl;

    // Tests summary
    if (err_cnt != 0) {cout << endl << "Error count:" << err_cnt;}
    else cout << "All tests passed";
    cout << endl << "End o tests" << endl;
    return 0;
}
