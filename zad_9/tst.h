#ifndef WORD_COUNTER_H_INCLUDED
#define WORD_COUNTER_H_INCLUDED

//Tymon Kwiatkowski
//319272

#include <map>
#include <string>
#include <vector>
#include <algorithm>

bool comp(const std::pair<std::string,int>& lhs, const std::pair<std::string,int>& rhs)
{
    return lhs.second > rhs.second;
}

class word_counter{
private:
    std::map<std::string, int> class_map;

public:
    word_counter()
    {
        std::map<std::string, int> temp;
        class_map = temp;
    }
    /*void print()

    {
        for (std::pair<std::string, int> const &elem: class_map)
        {
            std::cout << '(' << elem.first << ", " << elem.second << ") ";
        }
        std::cout << "\n\n";
    }*/
    void add_words(std::istream &is)
    {
        std::string line = "";
        while (is)
        {
            is >> line;
            if(line != "")
                class_map[line]++;
            line = "";
        }
    }

    int size()
    {
        return class_map.size();
    }

    std::vector<std::string> most_frequent(int n)
    {
        std::vector<std::pair<std::string, int>>results;
        for (auto const& it : class_map)
        {
            results.push_back(it);
        }

        std::sort(results.begin(), results.end(), comp);

        std::vector<std::string> returnee;
        for (auto const& it : results)
        {
            if(n <= 0)
                break;
            n--;
            returnee.push_back(it.first);
        }
        return returnee;
    }

    friend std::ostream& operator<<(std::ostream &os, const word_counter& right)
    {
        for (auto &i : right.class_map)
        {
            os << "(" << i.first << ", " << i.second << ") ";
        }
        return os;
    }
};

#endif // WORD_COUNTER_H_INCLUDED
