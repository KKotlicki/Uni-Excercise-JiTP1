// Konrad Kotlicki (310958)
#pragma once
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>

using namespace std;


class word_counter
{
    map<string, int> wordsCount;
public:
    void add_words(ifstream& entry)
    {
        vector<string> words;
        copy(
                istream_iterator<string>(entry),
                istream_iterator<string>(),
                back_inserter(words));

        for(const string& word: words)
            if (wordsCount.find("f") == wordsCount.end())
                wordsCount.insert(pair<string, int>(word, 1));
            else
                wordsCount[word]++;

    };

    unsigned int size () const
    {
        return wordsCount.size();
    }

    vector<string> most_frequent (int numOfRecords)
    {
        vector<pair<string, int>> topWordsAndCounts(numOfRecords);
        vector<string> topWords;
        partial_sort_copy(wordsCount.begin(),
                               wordsCount.end(),
                               topWordsAndCounts.begin(),
                               topWordsAndCounts.end(),
                               [](pair<string, int> const& l,
                                  pair<string, int> const& r)
                               {
                                   return l.second > r.second;
                               });
        topWords.reserve(topWordsAndCounts.size());
        for(const pair<string, int>& wordAndCount: topWordsAndCounts)
            topWords.push_back(wordAndCount.first);
        return topWords;
    }
};
