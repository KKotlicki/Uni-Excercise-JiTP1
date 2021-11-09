#include "mayan.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
    vector<unsigned int>decimal = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 123, 0, 1234113};
    vector<string>mayan = {"3723AI4F", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "10", "11", "12", "13", "14", "15", "16", "17", "ii", "2a0000000"};
    cout << "type: " << "- value "<< "- decimal" << "- mayan" << endl;
    for(int i = 0; i < (int) decimal.size(); i++)
    {
        /*try
        {
            uint2mayan(decimal[i]);
        }
        catch (const runtime_error& ex) {
            cerr << ex.what() << " in uint2mayan at " << decimal[i] << " - " << mayan[i] << endl;
        };
        try
        {
            mayan2uint(mayan[i]);
        }
        catch (const runtime_error& ex) {
            cerr << ex.what() << " in mayan2uint at " << decimal[i] << " - " << mayan[i] << endl;
        };*/

        if(uint2mayan(decimal[i]) != mayan[i])
        {
            cout << "uint2mayan: " << uint2mayan(decimal[i]) << " - " << decimal[i] << " - " << mayan[i] << endl;
        };
        if(mayan2uint(mayan[i]) != decimal[i])
        {
            cout << "mayan2uint: " << mayan2uint(mayan[i]) << " - " << decimal[i] << " - " << mayan[i] << endl;
        };

    };
    vector<unsigned int>decimal_d = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 4294967295, 66};
    vector<char>mayan_d = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '`', '@', '/'};
    for(int i = 0; i < (int) decimal_d.size(); i++)
    {
        try
        {
            uint2md(decimal_d[i]);
        }
        catch (const runtime_error& ex) {
            cerr << ex.what() << " in uint2md at " << decimal_d[i] << " - " << mayan_d[i] << endl;
        };
        try
        {
            md2uint(mayan_d[i]);
        }
        catch (const runtime_error& ex) {
            cerr << ex.what() << " in md2uint at " << decimal_d[i] << " - " << mayan_d[i] << endl;
        };
    }
    return 0;
}
