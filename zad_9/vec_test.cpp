#include <cassert>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include "error_messenger.h"
#include "vec.h"
using namespace std;


template <typename T>
int test_default_ctor(error_messenger& em);

template <typename T>
int test_indexing_on_empty_vec(error_messenger& em);

template <typename T>
int test_onearg_ctor(error_messenger& em, const vector<T>& values);

template <typename T>
int test_copy_ctor(error_messenger& em, const vector<T>& values);

template <typename T>
int test_inilist_ctor(error_messenger& em, const vector<T>& values);

template <typename T>
int test_push_back(error_messenger& em, const vector<T>& values);

template <typename T>
int test_pop_back(error_messenger& em, const vector<T>& values);

template <typename T>
int test_assignment(error_messenger& em, const vector<T>& values);

int main()
{
	error_messenger err;

// linia odkrywania kolejnych testów
	// konstruktor domyslny i size
	test_default_ctor<int>(err);
	test_default_ctor<string>(err);

	// sprawdzanie zakresu przy pustym wektorze
    test_indexing_on_empty_vec<int>(err);
    test_indexing_on_empty_vec<string>(err);

	// konstruktor jednoparametrowy - sprawdzenie, czy jest explicit
	// ponizsze linie powinny dac blad kompilacji, wiec beda do wykomentowania po stwierdzeniu, ze blad kompilacji jest
	{
		// vec<int> vi = 4;
		// vec<string> vs = 5;
	}

	// konstruktor jednoparametrowy - operator indeksowania; destruktor
	test_onearg_ctor<int>(err, { 1, 2 });
	test_onearg_ctor<string>(err, { "Whole Lotta Love", "Sweet Child O'Mine", "Back In Black" });
                                // wg s³uchaczy BBC Radio 2 w 2014 roku

	// konstruktor kopiujacy
    test_copy_ctor<int>(err, { 3, 5, 7, 9, 11, 13, 15 });
    test_copy_ctor<string>(err, { "Peer Gynt", "Symphony No. 5", "The Four Seasons", "Adagio for Strings", "Ride of the Valkyries" });
                        // wg London Philharmonic Orchestra w 2009 roku

    // konstruktor z list¹ inicjacyjn¹
    test_inilist_ctor<int>(err, { 4, 16, 64 });
    test_inilist_ctor<string>(err, { "Take Five", "So What", "Take the \"A\" Train" });
                                // wg s³uchaczy Jazz24

	// operacja push_back
	test_push_back<int>(err, { 1, 3, 5, 7, 11, 13, 17, 19 } );
	test_push_back<string>(err, { "Sweet Emotion", "Kashmir", "Gimme Shelter", "Back In Black", "A Day in the Life" });
                                // wg Ultimate Rock Classic

    test_pop_back<int>(err, { 3, 9, 27, 81, 243, 729 });
    test_pop_back<string>(err, { "Les Miserables", "Wicked", "The Phantom of the Opera", "West Side Story", "Blood Brothers" });
                                // wg WhatsOnStage

    test_assignment<int>(err, { 2, 4, 8, 16, 32, 64, 128, 256 });
    test_assignment<string>(err, { "L'Orfeo", "Dido and Aeneas", "Giulio Cesare", "Serse", "Orfeo ed Euridice" });
                                // wg Guardian z 2011 roku

	return 0;
}


template <typename T>
int test_default_ctor(error_messenger& em)
{
    vec<T> v;
    if (v.size() != 0)
        em.report_error("Error of size() != 0");
    if (v.capacity() != 0)
        em.report_error("Error of capacity() != 0");
    return em.get_err_count();
}

template <typename T>
int test_indexing_on_empty_vec(error_messenger& em)
{
    vec<T> v;
    for (int idx = 0; idx >= -1; --idx)
        try
        {
            v[idx];
            em.report_error("Operator [] error. Missing exception for out of range index (" + to_string(idx) + ").");
        }
        catch (out_of_range& ex)
        {
            // ten wyjatek powinien byc zgloszony
            cerr << ex.what() << endl;
        }
        catch (...)
        {
            // zadnych innych wyjatkow sie tu nie spodziewamy
            em.report_error("Operator [] error. Wrong exception type thrown for out of range index.");
        }
    return em.get_err_count();
}

template <typename T>
int test_onearg_ctor(error_messenger& em, const vector<T>& values)
{
    vec<T> v(values.size());
    if (v.size() != (int) values.size())
        em.report_error("Error of size() != " + to_string(values.size()));
    if (v.capacity() != v.size())
        em.report_error("Error of capacity() != " + to_string(v.size()));
    for (unsigned int i = 0; i < values.size(); ++i)
    {
        v[i] = values[i];
    }
    for (unsigned int idx = 0; idx < values.size(); ++idx)
    {
        try
        {
            T val = v[idx];
            if (val != values[idx])
                em.report_error("Operator [] error. Written != Read.");
            val = v[idx + v.size()];
            em.report_error("Operator [] error. Missing exception for out of range index (" + to_string(idx+v.size()) + ").");
        }
        catch (out_of_range& ex)
        {
            // ten wyjatek powinien byc zgloszony
            cerr << ex.what() << endl;
        }
    }
    return em.get_err_count();
}

template <typename T>
int test_copy_ctor(error_messenger& em, const vector<T>& values)
{
    vec<T> v(values.size());
    if (v.size() != (int) values.size())
        em.report_error("Error of size() != " + to_string(values.size()));
    if (v.capacity() != v.size())
        em.report_error("Error of capacity() != " + to_string(v.size()));
    for (unsigned int i = 0; i < values.size(); ++i)
    {
        v[i] = values[i];
    }

    vec<T> vcpy(v);
    for (unsigned int idx = 0; idx < values.size(); ++idx)
    {
        if (vcpy[idx] != values[idx])
            em.report_error("Copy constructor error.");
    }
    return em.get_err_count();
}

template <typename T>
int test_inilist_ctor(error_messenger& em, const vector<T>& values)
{
    assert(values.size() > 2);
    {
        vec<T> v { values[0], values[1], values[2] };
        if (v.size() != 3)
            em.report_error("Error in initializer list ctor size() != " + to_string(values.size()));
        for (int i = 0; i < v.size(); ++i)
        {
            if (v[i] != values[i])
                em.report_error("Initializer list ctor error.");
        }
    }

    {
        vec<T> v { values[0], values[1], values[2], values[0], values[1], values[2], values[0], values[1], values[2] };
        if (v.size() != 9)
            em.report_error("Error in initializer list ctor size() != " + to_string(values.size()));
        for (int i = 0; i < v.size(); ++i)
        {
            if (v[i] != values[i % 3])
                em.report_error("Initializer list ctor error.");
        }
    }

    return em.get_err_count();
}

template <typename T>
int test_push_back(error_messenger& em, const vector<T>& values)
{
    assert(values.size() > 2);
    for (int sz = 1; sz < 17; sz +=3)
    {
        vec<T> v;
        v.push_back(values[0]);
        if (v.capacity() != v.growSizeBy)
            em.report_error("Error of capacity() != " + to_string(v.growSizeBy));
        for (int i = 1; i < sz; ++i)
            v.push_back(values[i % values.size()]);

        if (v.size() != sz)
            em.report_error("Error in size() after push_back().");

        for (int i = 0; i < sz; ++i)
            if (v[i] != values[i % values.size()])
                em.report_error("Value error after push_back().");
    }
    return em.get_err_count();
}

template <typename T>
int test_pop_back(error_messenger& em, const vector<T>& values)
{
    assert(values.size() > 2);
    for (int sz = 1; sz < 22; sz += 4)
    {
        vec<T> v;
        for (int i = 0; i < sz; ++i)
            v.push_back(values[i % values.size()]);

        for (int step = v.size(); step > 0; --step)
        {
            T val = v.pop_back();
            if (val != values[(step - 1) % values.size()])
                em.report_error("pop_back() value error.");
            for (int i = 0; i < v.size(); ++i)
                if (v[i] != values[i % values.size()])
                    em.report_error("Error in vector values after pop_back().");
        }
        try
        {
            v.pop_back();
            em.report_error("pop_back error. Missing exception for empty vec pop_back.");
        }
        catch (out_of_range& ex)
        {
            // ten wyjatek powinien byc zgloszony
            cerr << ex.what() << endl;
        }
    }
    return em.get_err_count();
}

template <typename T>
int test_assignment(error_messenger& em, const vector<T>& values)
{
    assert(values.size() > 2);
    for (int sz = 1; sz < 17; sz +=3)
    {
        vec<T> vdest(42);
        vec<T> v;
        for (int i = 0; i < sz; ++i)
            v.push_back(values[i % values.size()]);

        vdest = v;
        if (vdest.size() != sz)
            em.report_error("Error in size() after assignment.");

        for (int i = 0; i < sz; ++i)
            if (vdest[i] != values[i % values.size()])
                em.report_error("Value error after assignment.");

        vdest = vdest;
        if (vdest.size() != sz)
            em.report_error("Error in size() after assignment.");

        for (int i = 0; i < sz; ++i)
            if (vdest[i] != values[i % values.size()])
                em.report_error("Value error after assignment.");
    }
    return em.get_err_count();
}
