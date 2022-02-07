#include <chrono>
#include <iostream>
#include "word_counter.h"
using namespace std;
using namespace std::chrono;


int main()
{
    // wezmmy teraz wiekszy tekst na warsztat
    ifstream is("TheVoyageoftheBeagle.txt");
    if (!is.good())
    {
        cout << "Smuteczek :(\n";
        return -1;
    }

    high_resolution_clock::time_point start = high_resolution_clock::now();

    word_counter wc;
    wc.add_words(is);
    cout << wc.size() << endl;

    vector<string> topWords = wc.most_frequent(10);
    for (const string& word: topWords)
        cout << word << ' ';

    high_resolution_clock::time_point now = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(now - start);
    cerr << "Counting in " << time_span.count() << " seconds." << endl;

    return 0;
}
