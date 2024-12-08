#include <fstream>
#include <functional>
#include <iterator>
#include <print>
#include <sstream>
#include <vector>

using namespace std;

struct Coord
{
    size_t& row;
    size_t& col;
    size_t const row_upper_bound;
    size_t const col_upper_bound;
};

bool MoveEast(Coord coord)
{
    return (++coord.col < coord.col_upper_bound);
}

bool MoveWest(Coord coord)
{
    return (coord.col-- > 0);
}

bool MoveNorth(Coord coord)
{
    return (coord.row-- > 0);
}

bool MoveSouth(Coord coord)
{
    return (++coord.row < coord.row_upper_bound);
}

bool MoveNE(Coord coord)
{
    return (MoveNorth(coord) && MoveEast(coord));
}

bool MoveNW(Coord coord)
{
    return (MoveNorth(coord) && MoveWest(coord));
}

bool MoveSW(Coord coord)
{
    return (MoveSouth(coord) && MoveWest(coord));
}

bool MoveSE(Coord coord)
{
    return (MoveSouth(coord) && MoveEast(coord));
}

using MoveFunction = std::function<bool(Coord)>;

bool Search(size_t row, size_t col, MoveFunction advance, vector<vector<char>> const& grid)
{
    Coord coord{row, col, grid.size(), grid[0].size()};

    vector<char> xmas = {'M', 'A', 'S'};
    for (char c : xmas)
    {
        if (!advance(coord) || c != grid[row][col])
        {
            return false;
        }
    }
    return true;
}

bool IsMasCross(size_t row, size_t col, vector<vector<char>> const& grid)
{
    Coord coord{row, col, grid.size(), grid[0].size()};

    char NE{};
    char SW{};
    if (!MoveNE(coord) || (grid[row][col] != 'M' && grid[row][col] != 'S'))
    {
        return false;
    }
    else
    {
        NE = grid[row][col];
    }
    if (!MoveSW(coord) || !MoveSW(coord) || (grid[row][col] != 'M' && grid[row][col] != 'S'))
    {
        return false;
    }
    else
    {
        SW = grid[row][col];
        MoveNE(coord);
    }
    if (SW == NE)
    {
        return false;
    }

    char NW{};
    char SE{};
    if (!MoveNW(coord) || (grid[row][col] != 'M' && grid[row][col] != 'S'))
    {
        return false;
    }
    else
    {
        NW = grid[row][col];
    }
    if (!MoveSE(coord) || !MoveSE(coord) || (grid[row][col] != 'M' && grid[row][col] != 'S'))
    {
        return false;
    }
    else
    {
        SE = grid[row][col];
    }
    if (SE == NW)
    {
        return false;
    }

    return true;
}

int main()
{
    std::fstream input_file{"day4/input_4.txt"};

    vector<vector<char>> grid;
    std::string line;
    size_t gridWidth{};
    while (std::getline(input_file, line))
    {
        std::stringstream ss{line};
        vector<char> gridLine{std::istream_iterator<char>{ss}, std::istream_iterator<char>{}};
        grid.push_back(gridLine);

        if (gridWidth == 0)
        {
            gridWidth = line.size();
        }
        else if (gridWidth != line.size())
        {
            print("ERROR: Grid is not constant width.");
        }
    }

    vector<MoveFunction> moveFunctions{MoveEast, MoveWest, MoveNorth, MoveSouth,
                                       MoveNW,   MoveNE,   MoveSW,    MoveSE};

    size_t nXmas{};
    size_t nMasCross{};
    for (size_t row{}; row < grid.size(); row++)
    {
        for (size_t col{}; col < grid[row].size(); col++)
        {
            /* Part 1 */
            for (auto move : moveFunctions)
            {
                if (grid[row][col] == 'X' && Search(row, col, move, grid))
                {
                    nXmas++;
                }
            }

            /* Part 2 */
            if (grid[row][col] == 'A' && IsMasCross(row, col, grid))
            {
                nMasCross++;
            }
        }
    }
    print("Part 1: {}\n", nXmas);
    print("Part 2: {}\n", nMasCross);

    return 0;
}
