// Konrad Kotlicki (310958)
#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <sstream>
#include <vector>
#include "entry.h"

bool sort_by_cnt(const entry& left, const entry& right)
{
    return (int)left - (int)right > 0;
}

class word_counter
{
    std::vector<entry> words;
public:
    add_word(const std::string& word)
    {
        auto it = find(words.begin(), words.end(), word);
        if (it == words.end())
        {
            words.emplace_back(word);
            words.back()++;
        }
        else
            (*it)++;
    };

    int size()const
    {
        return words.size();
    }

    void sort_alpha()
    {
        std::sort(words.begin(), words.end());
    }

    void sort_count()
    {
        std::sort(words.begin(), words.end(), sort_by_cnt);
    }

    const std::vector<entry>& get_vector() const
    {
        return words;
    }

    friend std::ostream& operator<<(std::ostream& os, word_counter& wc)
    {
        const std::vector<entry>& word_entry = wc.get_vector();
        os << '[';
        for (const auto & i : word_entry)
            os << i << ' ';
        os << ']';
        return os;
    }

};
