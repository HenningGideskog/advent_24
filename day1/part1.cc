#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
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

    std::ranges::sort(lhs);
    std::ranges::sort(rhs);

    long long result = std::inner_product(lhs.begin(), lhs.end(), rhs.begin(), 0,
            std::plus<long long>(),
            [](long long a, long long b)
                {
                    return abs(a - b);
                }
    );

    cout << result << endl;

    return 0;
}
