#include <algorithm>
#include <aoclib.hpp>
#include <fstream>
#include <functional>
#include <iostream>
#include <print>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;

pair<size_t, size_t> ParseRule(string const& line)
{
    stringstream ss{line};
    size_t first;
    char separator;
    size_t second;
    ss >> first >> separator >> second;
    return make_pair(first, second);
};

vector<size_t> ParseUpdate(string const& line)
{
    vector<size_t> update{};
    stringstream ss{line};
    size_t page;
    char delim;
    while (ss >> page)
    {
        update.push_back(page);
        ss >> delim;
    }
    return update;
}

bool RuleHolds(pair<size_t, size_t> const& rule, vector<size_t> const& update)
{
    auto firstIt  = std::ranges::find(update, rule.first);
    auto secondIt = std::ranges::find(update, rule.second);

    if (firstIt == update.end() || secondIt == update.end())
    {
        return true;
    }
    else
    {
        return firstIt < secondIt;
    }
}

bool AllRulesHold(vector<pair<size_t, size_t>> rules, vector<size_t> const& update)
{
    return std::ranges::all_of(rules, std::bind(RuleHolds, std::placeholders::_1, update));
}

size_t MiddlePage(vector<size_t> const& update)
{
    return update[update.size() / 2];
}

int main()
{
    std::fstream input_file{"day5/input_5.txt"};

    vector<pair<size_t, size_t>> rules{};
    vector<vector<size_t>> updates{};

    string line;
    while (getline(input_file, line) && line.size() > 0)
    {
        rules.push_back(ParseRule(line));
    }

    while (getline(input_file, line) && line.size() > 0)
    {
        updates.push_back(ParseUpdate(line));
    }

    size_t correctUpdateMiddlePageSum{};
    size_t fixedUpdateMiddlePageSum{};
    for (auto u : updates)
    {
        if (AllRulesHold(rules, u))
        {
            correctUpdateMiddlePageSum += MiddlePage(u);
        }
        else
        {
            auto RulesHoldCompare = [&rules](size_t a, size_t b) -> bool
            {
                return AllRulesHold(rules, vector<size_t>{a, b});
            };

            std::ranges::sort(u, RulesHoldCompare);
            if (std::ranges::all_of(rules, std::bind(RuleHolds, std::placeholders::_1, u)))
            {
                fixedUpdateMiddlePageSum += MiddlePage(u);
            }
        }
    }

    print("Part 1: {}\n", correctUpdateMiddlePageSum);
    print("Part 2: {}\n", fixedUpdateMiddlePageSum);

    return 0;
}
