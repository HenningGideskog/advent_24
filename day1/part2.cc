#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
int main()
{
    fstream input_file {"day1/input_1.txt"};

    long long left;
    long long right;
    vector<long long> lhs{};
    vector<long long> rhs{};
    
    while (input_file >> left >> right)
    {
        lhs.push_back(left);
        rhs.push_back(right);
    }

    long long result{};
    for (long long n : lhs)
    {
        result += std::ranges::count(rhs, n) * n;
    }

    cout << result << endl;

    return 0;
}
