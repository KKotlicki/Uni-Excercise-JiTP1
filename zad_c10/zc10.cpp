#include "fraction.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    fraction tst(1, 2);
    tst = tst + 2;
    cout << tst << endl;
    return 0;
}

