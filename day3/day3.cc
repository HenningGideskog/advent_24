#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>
#include <print>
#include <vector>

using namespace std;
using subrange = std::ranges::subrange<vector<char>::iterator, vector<char>::iterator>;

string ParseNumber(vector<char>::iterator& parseIt, vector<char>::const_iterator end)
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

size_t ParseInstruction(vector<char>::iterator& parseIt, vector<char>::const_iterator end)
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

size_t ParseRange(subrange range)
{
    vector<char> mulStart{'m', 'u', 'l', '('};
    subrange findRange = std::ranges::search(range, mulStart);

    size_t result{0};
    while (findRange.begin() != range.end())
    {
        vector<char>::iterator parseIt{findRange.begin() + 4};
        result += ParseInstruction(parseIt, range.end());

        subrange rest{parseIt, range.end()};
        findRange = std::ranges::search(rest, mulStart);
    }

    return result;
}

int main()
{
    fstream input_file{"day3/input_3.txt"};
    vector<char> input{istream_iterator<char>{input_file}, istream_iterator<char>{}};
    vector<char> doString{'d', 'o', '(', ')'};
    vector<char> dontString{'d', 'o', 'n', '\'', 't', '(', ')'};

    /* Part 1 */
    size_t resultPart1{};
    resultPart1 += ParseRange(input);
    print("Part 1: {}\n", resultPart1);

    /* Part 2 */
    size_t resultPart2{};

    subrange rangeToParse{input.begin(), std::ranges::search(input, dontString).begin()};
    subrange rest{rangeToParse.end(), input.end()};
    while (rangeToParse.begin() != input.end())
    {
        resultPart2 += ParseRange(rangeToParse);

        vector<char>::iterator nextRangeBegin{std::ranges::search(rest, doString).end()};
        rest = subrange{nextRangeBegin, input.end()};

        vector<char>::iterator nextRangeEnd{std::ranges::search(rest, dontString).begin()};
        rangeToParse = subrange{nextRangeBegin, nextRangeEnd};
        rest         = subrange{rangeToParse.end(), input.end()};
    }

    print("Part 2: {}\n", resultPart2);

    return 0;
}
