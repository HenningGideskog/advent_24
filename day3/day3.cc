#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <iterator>
#include <print>
#include <vector>

using namespace std;

string ParseNumber(vector<char>::const_iterator& parseIt, vector<char>::const_iterator end)
{
    string numString{};
    for (size_t i{}; i < 3; i++)
    {
        if (parseIt != end && std::isdigit(*parseIt))
        {
            numString += *parseIt;
            parseIt++;
        }
        else if (numString.size() == 0 || parseIt == end)
        {
            return "";
        }
        else
        {
            break;
        }
    }
    return numString;
}

size_t ParseInstruction(vector<char>::const_iterator& parseIt, vector<char>::const_iterator end)
{

    string firstNumberString{ParseNumber(parseIt, end)};
    if (*parseIt != ',' || ++parseIt == end || firstNumberString == "")
    {
        return 0;
    }
    string secondNumberString{ParseNumber(parseIt, end)};
    if (*parseIt != ')' || secondNumberString == "")
    {
        return 0;
    }

    size_t firstNumber  = std::stoi(firstNumberString);
    size_t secondNumber = std::stoi(secondNumberString);

    return firstNumber * secondNumber;
}

int main()
{
    fstream input_file{"day3/input_3.txt"};
    vector<char> input{istream_iterator<char>{input_file}, istream_iterator<char>{}};
    vector<char> mulStart{'m', 'u', 'l', '('};

    using subrange     = std::ranges::subrange<vector<char>::iterator, vector<char>::iterator>;
    subrange findRange = std::ranges::search(input, mulStart);

    size_t result{0};
    while (findRange.begin() != input.end())
    {
        vector<char>::const_iterator parseIt{findRange.begin() + 4};
        result += ParseInstruction(parseIt, input.end());

        subrange rest{findRange.end(), input.end()};
        findRange = std::ranges::search(rest, mulStart);
    }

    cout << result << endl;

    return 0;
}
