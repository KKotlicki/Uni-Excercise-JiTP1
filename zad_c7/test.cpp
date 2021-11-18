#include "simpleDate.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    int er1_count = 0;
    int er2_count = 0;
    for(int a=2019; a < 2022; a++)
    {
        for(int b=1; b < 13; b++)
        {
            for(int c=1; c < 32; c++)
            {
                try{simpleDate test_object(c, b, a); test_object.next_day(); test_object.get_day(); test_object.get_month(); test_object.get_year();}
                catch(const simpleDate::invalid_argument){er1_count++;}
                catch(const simpleDate::invalid_operation){er2_count++;};
                try{simpleDate test_object(c, b, a); test_object.prev_day();}
                catch(const simpleDate::invalid_argument){}
                catch(const simpleDate::invalid_operation){er2_count++;};
            };
        };
    };
    cout << er1_count << " : " << er2_count << endl;




    /*try
    {
        simpleDate deflt;
        deflt.print();
        cout << deflt.year() << endl;
    }
    catch(const simpleDate::invalid_argument)
    {
        cerr << "Error at 1" << endl;
    };

    try
    {
        simpleDate ax(30, 12, 2019);
        ax.print();
        cout << ax.year() << endl;
    }
    catch(const simpleDate::invalid_argument)
    {
        cerr << "Error at 2" << endl;
    };


    try{
        simpleDate ax(31, 12, 2020);
        ax.next_day();
        ax.print();}
    catch(const simpleDate::invalid_operation)
    {
        cerr << "Error at 3" << endl;
    }


    try{
        simpleDate ax(1, 3, 2020);
        ax.prev_day();
        ax.print();}
    catch(const simpleDate::invalid_operation)
    {
        cerr << "Error at 4" << endl;
    }
    cout <<  endl << "END!" <<  endl;*/
    return 0;
}
