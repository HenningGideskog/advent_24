#include <algorithm>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <tuple>
#include <vector>

using namespace std;
using Equation = tuple<bool, long long, vector<long>>;

vector<Equation> ParseInput(fstream& input)
{
    vector<Equation> parsedInput{};
    string line;

    bool correct{false};
    long long sum;
    long operand;

    char discard{};
    while (getline(input, line))
    {
        stringstream ss{line};

        vector<long> operands{};
        ss >> sum >> discard;
        while (ss >> operand)
        {
            operands.push_back(operand);
        }

        parsedInput.push_back(make_tuple(correct, sum, operands));
    }

    return parsedInput;
}

long long Concatenate(long left, long right)
{
    string leftString{to_string(left)};
    string rightString{to_string(right)};
    return stoll(leftString + rightString);
}

void BruteForceEquationTwoOp(Equation& eq)
{
    unsigned multiplyBitmask{};
    vector<long> const& operands = get<2>(eq);
    size_t nOperands             = operands.size();

    long long targetSum{get<1>(eq)};
    long long currentSum{};

    while (!(multiplyBitmask & (1UL << nOperands)))
    {
        currentSum = operands[0];
        for (size_t i{}; i < nOperands - 1; i++)
        {
            if (multiplyBitmask & (1UL << i))
            {
                currentSum *= operands[i + 1];
            }
            else
            {
                currentSum += operands[i + 1];
            }
        }
        if (currentSum == targetSum)
        {
            get<0>(eq) = true;
            return;
        }
        multiplyBitmask++;
    }
}

enum class Operator
{
    ADD,
    MULTIPLY,
    CONCATENATE
};

void AdvanceOperators(vector<Operator>& vec)
{
    for (Operator& o : vec)
    {
        if (o == Operator::ADD)
        {
            o = Operator::MULTIPLY;
            return;
        }
        else if (o == Operator::MULTIPLY)
        {
            o = Operator::CONCATENATE;
            return;
        }
        else if (o == Operator::CONCATENATE)
        {
            o = Operator::ADD;
        }
    }
}

void BruteForceEquationThreeOp(Equation& eq)
{
    if (get<0>(eq))
    {
        return;
    }
    vector<long> const& operands = get<2>(eq);
    size_t nOperands             = operands.size();
    vector<Operator> operators(nOperands, Operator::ADD);

    long long targetSum{get<1>(eq)};
    long long currentSum{};

    while (operators[nOperands - 1] == Operator::ADD)
    {
        currentSum = operands[0];
        for (size_t i{}; i < nOperands - 1; i++)
        {
            if (operators[i] == Operator::ADD)
            {
                currentSum += operands[i + 1];
            }
            else if (operators[i] == Operator::MULTIPLY)
            {
                currentSum *= operands[i + 1];
            }
            else if (operators[i] == Operator::CONCATENATE)
            {
                currentSum = Concatenate(currentSum, operands[i + 1]);
            }
        }
        if (currentSum == targetSum)
        {
            get<0>(eq) = true;
            return;
        }
        AdvanceOperators(operators);
    }
}

int main()
{
    fstream input_file{"day7/input_7.txt"};
    vector<Equation> input{ParseInput(input_file)};

    std::ranges::for_each(input, BruteForceEquationTwoOp);

    size_t sumTrueEquationsTwoOp{};
    for (auto eq : input)
    {
        if (get<0>(eq))
        {
            sumTrueEquationsTwoOp += get<1>(eq);
        }
    }

    print("Part 1: {}", sumTrueEquationsTwoOp);

    std::ranges::for_each(input, BruteForceEquationThreeOp);

    size_t sumTrueEquationsThreeOp{};
    for (auto eq : input)
    {
        if (get<0>(eq))
        {
            sumTrueEquationsThreeOp += get<1>(eq);
        }
    }

    print("Part 2: {}", sumTrueEquationsThreeOp);

    return 0;
}
