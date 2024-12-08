#include <algorithm>
#include <fstream>
#include <print>
#include <vector>

using namespace std;

struct Coord
{
    size_t row;
    size_t col;
    size_t const row_upper_bound;
    size_t const col_upper_bound;
    size_t direction;
};

Coord FindGuardStart(vector<vector<char>> const& grid)
{
    for (size_t row{}; row < grid.size(); row++)
    {
        auto colIt = std::ranges::find(grid[row], '^');
        if (colIt != grid[row].end())
        {
            size_t col = std::distance(grid[row].begin(), colIt);
            return Coord{row, col, grid.size(), grid[0].size(), 0};
        }
    }

    throw "Error: did not find starting position.";
}

void TurnRight(size_t& direction)
{
    direction = (direction + 1) % 4;
}

bool GuardStep(Coord& guardPos, vector<vector<char>>& grid)
{
    if ((guardPos.direction == 0 && guardPos.row == 0) ||
        (guardPos.direction == 1 && guardPos.col == guardPos.col_upper_bound - 1) ||
        (guardPos.direction == 2 && guardPos.row == guardPos.row_upper_bound - 1) ||
        (guardPos.direction == 3 && guardPos.col == 0))
    {
        /* Exited the area. */
        return false;
    }

    if (guardPos.direction == 0 && grid[guardPos.row - 1][guardPos.col] != '#')
    {
        guardPos.row--;
        return true;
    }
    else if (guardPos.direction == 0)
    {
        TurnRight(guardPos.direction);
        return true;
    }

    if (guardPos.direction == 1 && grid[guardPos.row][guardPos.col + 1] != '#')
    {
        guardPos.col++;
        return true;
    }
    else if (guardPos.direction == 1)
    {
        TurnRight(guardPos.direction);
        return true;
    }

    if (guardPos.direction == 2 && grid[guardPos.row + 1][guardPos.col] != '#')
    {
        guardPos.row++;
        return true;
    }
    else if (guardPos.direction == 2)
    {
        TurnRight(guardPos.direction);
        return true;
    }

    if (guardPos.direction == 3 && grid[guardPos.row][guardPos.col - 1] != '#')
    {
        guardPos.col--;
        return true;
    }
    else if (guardPos.direction == 3)
    {
        TurnRight(guardPos.direction);
        return true;
    }
    throw "Error: Illegal direction.";
}

int main()
{
    std::fstream input_file{"day6/input_6.txt"};

    vector<vector<char>> grid{};
    string line;
    while (input_file >> line)
    {
        grid.push_back(vector<char>{line.begin(), line.end()});
    }

    Coord guardPos = FindGuardStart(grid);

    grid[guardPos.row][guardPos.col] = 'X';
    while (GuardStep(guardPos, grid))
    {
        grid[guardPos.row][guardPos.col] = 'X';
    }

    size_t nDistinctPositions{};
    for (auto line : grid)
    {
        nDistinctPositions += std::ranges::count(line, 'X');
    }
    print("Part 1: {}\n", nDistinctPositions);

    return 0;
}
