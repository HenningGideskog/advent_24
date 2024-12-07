#include <algorithm>
#include <aoclib.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;

bool monotoneIncrease(int n)
{
    return (n > 0 && n <= 3);
}

bool monotoneDecrease(int n)
{
    return (n < 0 && n >= -3);
}

int main()
{
    fstream input_file{"day2/input_2.txt"};

    vector<vector<int>> reports{};

    string line{};
    while (getline(input_file, line))
    {
        stringstream ss{line};
        list<int> report{istream_iterator<int>{ss}, istream_iterator<int>{}};
        std::adjacent_difference(report.begin(), report.end(), report.begin());
        report.pop_front();
        reports.push_back(vector<int>{report.begin(), report.end()});
    }

    size_t count{};
    for (auto& r : reports)
    {
        if (std::ranges::all_of(r, monotoneIncrease) || std::ranges::all_of(r, monotoneDecrease))
        {
            count++;
        }
    }

    cout << count << endl;

    return 0;
}
