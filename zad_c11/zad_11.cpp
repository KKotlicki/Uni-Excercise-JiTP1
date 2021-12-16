#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include "word_counter.h"
using namespace std;
using namespace std::chrono;

bool greater_than(float a, float b)
	{ return a > b; }

template <class Typ>
void compare_values(const string& msg, const Typ& act, const Typ& prop)
{
	if (act != prop)
	{
		cerr << msg << endl;
		cerr << "    Produced: " << act << endl;
		cerr << "Proper value: " << prop << endl;
	}
}

int main()
{
	/* czesc ilustrujaca materialy z cwiczen */
    vector<int> vint = {1, 3, 5, 7, 11};
    for (const int& val : vint)
        cout << val << ' ';
    cout << endl;
	for (int & cit : vint)
		cout << cit << ' ';
	cout << endl;
    for (int idx : vint)
        cout << idx << ' ';
    cout << endl;
	// szukanie
	auto it = find(vint.begin(), vint.end(), 8);
	if (it != vint.end())
    {
		// znalezione, mozna dzialac
		(*it)++; // zwiększam na 9
    }else
        cout << "Nie znaleziono 8\n";

    vector<float> vflt = {8.9, 3.4, 1.7, 14.2, 2.3};
    sort(vflt.begin(), vflt.end(), greater_than);
    for (auto val : vflt)
        cout << val << ' ';
    cout << endl;
    sort(vflt.begin(), vflt.end());
    for (auto val : vflt)
        cout << val << ' ';
    cout << endl;
	cout << "----------- End of presentation ----------\n";


	vector<pair<string, int>> tst{
		{ "", 0 },
		{ "alina ", 1 },
		{ "helena halina helena ", 2 },
		{ "helena halina hanna halina helena ", 3 },
		{ "helena halina hanna halina helena halina ", 3 },
	};
	vector<pair<string, string>> prop{
		{ "[]", "[]" },
		{ "[[alina 1] ]", "[[alina 1] ]" },
		{ "[[halina 1] [helena 2] ]", "[[helena 2] [halina 1] ]" },
		{ "[[halina 2] [hanna 1] [helena 2] ]", "[[halina 2] [helena 2] [hanna 1] ]" },
		{ "[[halina 3] [hanna 1] [helena 2] ]", "[[halina 3] [helena 2] [hanna 1] ]" },
	};

	for (int i = 0; i < (int)tst.size(); ++i)
	{
		ostringstream msg;
		msg << "Test " << i + 1;

		word_counter wc;
		istringstream ss(tst[i].first);
		string word;
		while (ss >> word)
			wc.add_word(word);

		compare_values(msg.str(), wc.size(), tst[i].second);

		// alfabetycznie
		wc.sort_alpha();
		{
			ostringstream os;
			os << wc;
			compare_values(msg.str() + " alpha ", os.str(), prop[i].first);
			cout << wc << endl;
		}

		// wg czestosci wystapien
		wc.sort_count();
		{
			ostringstream os;
			os << wc;
			compare_values(msg.str() + " count ", os.str(), prop[i].second);
			cout << wc << endl;
		}
	}

	// wezmmy teraz wiekszy tekst na warsztat
    ifstream is("TheVoyageoftheBeagle.txt");
    if (!is.good())
    {
        cout << "Smuteczek :(\n";
        return -1;
    }

    high_resolution_clock::time_point start = high_resolution_clock::now();
    word_counter wc;

    string word;
    while (is >> word)
        wc.add_word(word);

    high_resolution_clock::time_point now = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(now - start);
    cerr << "Counting in " << time_span.count() << " seconds." << endl;


	int limit = 20;

    // alfabetycznie
	cout << "\n\nThe Voyage of Beagle by Charles Darwin first 20 words alphabetically\n\n";
	wc.sort_alpha();
	auto iter = wc.get_vector().begin();
	for (int cnt = 0; cnt < limit; ++cnt)
        cout << *iter++ << endl;

    // po czestosci wystapien
	cout << "\n\nThe Voyage of Beagle by Charles Darwin most frequent words\n\n";
	wc.sort_count();
	iter = wc.get_vector().begin();
	for (int cnt = 0; cnt < limit; ++cnt)
        cout << *iter++ << endl;

    return 0;
}
