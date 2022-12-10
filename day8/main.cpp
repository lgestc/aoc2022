#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>

typedef std::vector<std::vector<u_int8_t>> Grid;

int score(Grid &grid, int x, int y)
{
    uint8_t h = grid[y][x];

    int score_l = 0;
    int score_r = 0;
    int score_t = 0;
    int score_d = 0;

    bool skip_l = false;
    bool skip_r = false;
    bool skip_t = false;
    bool skip_d = false;

    for (int i = 1; i < grid.size(); i++)
    {
        // right
        if (x + i < grid.size() && !skip_r)
        {
            int th = grid[y][x + i];

            if (th < h)
            {
                score_r += 1;
            }
            else if (th == h)
            {
                score_r += 1;
                skip_r = true;
            }
            else
            {
                skip_r = true;
            }
        }

        // left
        if (x - i >= 0 && !skip_l)
        {
            int th = grid[y][x - i];

            if (th < h)
            {
                score_l += 1;
            }
            else if (th == h)
            {
                score_l += 1;
                skip_l = true;
            }
            else
            {
                skip_l = true;
            }
        }

        // top
        if (y + i < grid.size() && !skip_t)
        {
            int th = grid[y + i][x];

            if (th < h)
            {
                score_t += 1;
            }
            else if (th == h)
            {
                score_t += 1;
                skip_t = true;
            }
            else
            {
                skip_t = true;
            }
        }

        if (y - i >= 0 && !skip_d)
        {
            int th = grid[y - i][x];

            if (th < h)
            {
                score_d += 1;
            }
            else if (th == h)
            {
                score_d += 1;
                skip_d = true;
            }
            else
            {
                skip_d = true;
            }
        }
    }

    return score_l * score_r * score_d * score_t;
}

int main()
{
    std::ifstream file("./input");

    Grid grid;

    // Parse file into 2d array
    if (file.is_open())
    {
        std::string line;

        while (std::getline(file, line))
        {
            std::vector<uint8_t> row;
            for (int i = 0; i < line.length(); i++)
            {
                row.push_back(line[i]);
            }

            grid.push_back(row);
        }

        file.close();
    }

    int top_score = 0;

    // Analyze interior trees only
    for (int y = 1; y < grid.size() - 1; y++)
    {
        for (int x = 1; x < grid.size() - 1; x++)
        {
            int s = score(grid, x, y);

            if (s > top_score)
            {
                top_score = s;
            }
        }
    }

    std::cout << std::endl;

    std::cout << top_score << std::endl;

    return 0;
}