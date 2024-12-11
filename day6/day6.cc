#include <algorithm>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <print>
#include <ranges>
#include <sstream>
#include <vector>

using namespace std;
namespace ranges = std::ranges;
namespace views  = std::views;

enum class GuardDirection
{
    UP,
    RIGHT,
    DOWN,
    LEFT,
    GONE
};

using State = pair<vector<char>::iterator, GuardDirection>;

struct Grid
{
    vector<char> vec;
    size_t const gridWidth;
};

Grid ParseGrid(fstream& input_file)
{
    string line;
    size_t gridWidth{};
    vector<char> grid{};
    while (getline(input_file, line))
    {
        if (gridWidth == 0)
        {
            gridWidth = line.size();
        }
        else if (gridWidth != line.size())
        {
            throw "Error: Grid width is not constant.";
        }
        stringstream ss{line};
        grid.insert(grid.end(), istream_iterator<char>{ss}, istream_iterator<char>{});
    }
    return Grid{grid, gridWidth};
}

auto RangeUp(Grid& grid, vector<char>::iterator it)
{
    return views::reverse(grid.vec) | views::drop(std::distance(it, grid.vec.end()) - 1) |
           views::stride(grid.gridWidth);
}

auto RangeRight(Grid& grid, vector<char>::iterator it)
{
    size_t dist = std::distance(grid.vec.begin(), it);
    return grid.vec | views::drop(dist) | views::take(grid.gridWidth - (dist % grid.gridWidth));
}

auto RangeDown(Grid& grid, vector<char>::iterator it)
{
    return grid.vec | views::drop(std::distance(grid.vec.begin(), it)) |
           views::stride(grid.gridWidth);
}

auto RangeLeft(Grid& grid, vector<char>::iterator it)
{
    size_t dist = std::distance(it, grid.vec.end()) - 1;
    return views::reverse(grid.vec) | views::drop(dist) |
           views::take(grid.gridWidth - dist % grid.gridWidth);
}

void Move(Grid& grid, State& currentState)
{
    if (currentState.second == GuardDirection::UP)
    {
        auto searchRange = RangeUp(grid, currentState.first);
        auto nextTurn    = ranges::find(searchRange, '#');
        if (nextTurn == searchRange.end())
        {
            currentState.second = GuardDirection::GONE;
        }
        else
        {
            currentState.second = GuardDirection::RIGHT;
        }
        currentState.first -= std::distance(searchRange.begin(), nextTurn - 1) * grid.gridWidth;
    }
    else if (currentState.second == GuardDirection::RIGHT)
    {
        auto searchRange = RangeRight(grid, currentState.first);
        auto nextTurn    = ranges::find(searchRange, '#');
        if (nextTurn == searchRange.end())
        {
            currentState.second = GuardDirection::GONE;
        }
        else
        {
            currentState.second = GuardDirection::DOWN;
        }
        currentState.first += std::distance(searchRange.begin(), nextTurn - 1);
    }
    else if (currentState.second == GuardDirection::DOWN)
    {
        auto searchRange = RangeDown(grid, currentState.first);
        auto nextTurn    = ranges::find(searchRange, '#');
        if (nextTurn == searchRange.end())
        {
            currentState.second = GuardDirection::GONE;
        }
        else
        {
            currentState.second = GuardDirection::LEFT;
        }
        currentState.first += std::distance(searchRange.begin(), nextTurn - 1) * grid.gridWidth;
    }
    else if (currentState.second == GuardDirection::LEFT)
    {
        auto searchRange = RangeLeft(grid, currentState.first);
        auto nextTurn    = ranges::find(searchRange, '#');
        if (nextTurn == searchRange.end())
        {
            currentState.second = GuardDirection::GONE;
        }
        else
        {
            currentState.second = GuardDirection::UP;
        }
        currentState.first -= std::distance(searchRange.begin(), nextTurn - 1);
    }
}

void MarkDistinctPositions(Grid& grid, vector<State> const& states)
{
    for (size_t i{}; i < states.size() - 1; i++)
    {
        if (states[i].second == GuardDirection::UP)
        {
            auto fillRange = RangeUp(grid, states[i].first) |
                             views::take(1 + std::distance(states[i + 1].first, states[i].first) /
                                                 grid.gridWidth);
            ranges::fill(fillRange, 'X');
        }
        else if (states[i].second == GuardDirection::RIGHT)
        {
            auto fillRange = RangeRight(grid, states[i].first) |
                             views::take(1 + std::distance(states[i].first, states[i + 1].first));
            ranges::fill(fillRange, 'X');
        }
        else if (states[i].second == GuardDirection::DOWN)
        {
            auto fillRange = RangeDown(grid, states[i].first) |
                             views::take(1 + std::distance(states[i].first, states[i + 1].first) /
                                                 grid.gridWidth);
            ranges::fill(fillRange, 'X');
        }
        else if (states[i].second == GuardDirection::LEFT)
        {
            auto fillRange = RangeLeft(grid, states[i].first) |
                             views::take(1 + std::distance(states[i + 1].first, states[i].first));
            ranges::fill(fillRange, 'X');
        }
    }
}

int main()
{
    fstream input_file{"day6/input_6.txt"};
    Grid grid{ParseGrid(input_file)};
    Grid gridPart2{grid};

    vector<char>::iterator start = ranges::find(grid.vec, '^');

    vector<State> states{};
    State currentState{make_pair(start, GuardDirection::UP)};
    states.push_back(currentState);

    while (currentState.second != GuardDirection::GONE)
    {
        Move(grid, currentState);
        states.push_back(currentState);
    }

    MarkDistinctPositions(grid, states);
    long nDistinctPositions{ranges::count(grid.vec, 'X')};
    print("Part 1: {}\n", nDistinctPositions);

    long nLoops{};
    for (size_t i{}; i < gridPart2.vec.size(); i++)
    {
        Grid newGrid{gridPart2};
        if (newGrid.vec[i] != '^')
        {
            newGrid.vec[i] = '#';
        }

        vector<char>::iterator newStart = ranges::find(newGrid.vec, '^');

        vector<State> newStates{};
        State newCurrentState{make_pair(newStart, GuardDirection::UP)};
        newStates.push_back(newCurrentState);

        while (newCurrentState.second != GuardDirection::GONE)
        {
            Move(newGrid, newCurrentState);
            if (ranges::find(newStates, newCurrentState) != newStates.end())
            {
                nLoops++;
                break;
            }
            newStates.push_back(newCurrentState);
        }
    }

    print("Part 2: {}\n", nLoops);

    return 0;
}
