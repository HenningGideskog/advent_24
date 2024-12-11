#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;

bool IsValidIncrease(int n)
{
    return (n > 0 && n <= 3);
}

bool IsValidDecrease(int n)
{
    return (n < 0 && n >= -3);
}

bool DiffsFormValidIncrease(vector<int> const& diffs)
{
    return std::ranges::all_of(diffs, IsValidIncrease);
}

bool DiffsFormValidDecrease(vector<int> const& diffs)
{
    return std::ranges::all_of(diffs, IsValidDecrease);
}

vector<int> CalcDiffs(vector<int> const& report)
{
    vector<int> diffs{};
    std::adjacent_difference(report.begin(), report.end(), back_inserter(diffs));
    diffs.erase(diffs.begin());
    return diffs;
}

int main()
{
    fstream input_file{"day2/input_2.txt"};

    vector<vector<int>> reports{};

    string line{};
    while (getline(input_file, line))
    {
        stringstream ss{line};
        vector<int> report{istream_iterator<int>{ss}, istream_iterator<int>{}};
        reports.push_back(report);
    }

    /* Brute force go brrrrr! */
    size_t count{};
    for (auto& r : reports)
    {
        for (size_t i{}; i < r.size(); i++)
        {
            vector<int> tr{r.begin(), r.end()};
            tr.erase(tr.begin() + i);
            vector<int> diff = CalcDiffs(tr);
            if (DiffsFormValidIncrease(diff) || DiffsFormValidDecrease(diff))
            {
                count++;
                break;
            }
        }
    }

    cout << count << endl;
    return 0;
}
