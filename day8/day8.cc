#include <fstream>
#include <iterator>
#include <print>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

using Grid = pair<vector<char>, size_t>;

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

vector<size_t> FindAntennaPositions(char f, Grid const& grid)
{
    vector<size_t> antennas{};
    for (size_t i{}; i < grid.first.size(); i++)
    {
        if (grid.first[i] == f)
        {
            antennas.push_back(i);
        }
    }
    return antennas;
}

void FindAntinode(size_t a1, size_t a2, Grid const& grid, set<size_t>& antinodes)
{
    long gridTotalRows = grid.first.size() / grid.second;
    long gridTotalCols = grid.second;
    long row1          = a1 / grid.second;
    long row2          = a2 / grid.second;
    long col1          = a1 % grid.second;
    long col2          = a2 % grid.second;
    long rowDist       = row2 - row1;
    long colDist       = col2 - col1;

    long rowAntinode = row1 + 2 * rowDist;
    long colAntinode = col1 + 2 * colDist;

    if (rowAntinode < gridTotalRows && rowAntinode >= 0 && colAntinode < gridTotalCols &&
        colAntinode >= 0)
    {
        antinodes.insert(rowAntinode * gridTotalRows + colAntinode);
    }
}

void FindAntinodes(vector<size_t> const& antennas, Grid const grid, set<size_t>& antinodes)
{
    for (size_t i{}; i < antennas.size(); i++)
    {
        for (size_t j{}; j < antennas.size(); j++)
        {
            if (i == j)
            {
                continue;
            }
            FindAntinode(antennas[i], antennas[j], grid, antinodes);
        }
    }
}

int main()
{
    fstream input_file{"day8/input_8.txt"};
    Grid grid{ParseGrid(input_file)};

    set<char> frequencies{};
    for (char c : grid.first)
    {
        if (std::isalnum(c))
        {
            frequencies.insert(c);
        }
    }

    set<size_t> antinodes{};
    for (char f : frequencies)
    {
        vector<size_t> antennaPositions = FindAntennaPositions(f, grid);
        FindAntinodes(antennaPositions, grid, antinodes);
    }

    print("Part 1: {}\n", antinodes.size());

    return 0;
}
