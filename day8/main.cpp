#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>

// With 16 trees visible on the edge and another 5 visible in the interior,
// a total of 21 trees are visible in this arrangement.

int main()
{
    std::ifstream file("./input");

    std::vector<std::vector<u_int8_t>> grid;

    std::set<std::string> visible;

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

    // Analyze
    for (int y = 0; y < grid.size(); y++)
    {
        int highest = 0;
        for (int x = 0; x < grid.size(); x++)
        {
            if (grid[y][x] > highest)
            {
                visible.insert(std::to_string(x) + " " + std::to_string(y));
                highest = grid[y][x];
            }

            if ((y == 0 || y == grid.size() - 1) || (x == 0 || x == grid.size() - 1))
            {
                visible.insert(std::to_string(x) + " " + std::to_string(y));
            }
        }

        highest = 0;
        for (int x = grid.size() - 1; x > 0; x--)
        {
            if (grid[y][x] > highest)
            {
                visible.insert(std::to_string(x) + " " + std::to_string(y));
                highest = grid[y][x];
            }
        }
    }

    for (int x = 0; x < grid.size(); x++)
    {
        int highest = 0;
        for (int y = 0; y < grid.size(); y++)
        {
            if (grid[y][x] > highest)
            {
                visible.insert(std::to_string(x) + " " + std::to_string(y));
                highest = grid[y][x];
            }
        }

        highest = 0;
        for (int y = grid.size() - 1; y > 0; y--)
        {
            if (grid[y][x] > highest)
            {
                visible.insert(std::to_string(x) + " " + std::to_string(y));
                highest = grid[y][x];
            }
        }
    }

    // Draw
    for (int y = 0; y < grid.size(); y++)
    {
        for (int x = 0; x < grid.size(); x++)
        {
            std::string key = std::to_string(x) + " " + std::to_string(y);
            std::string marker = " ";

            if (visible.find(key) != visible.end())
            {
                marker = ".";
            }

            std::cout << marker << grid[y][x] << " ";
            if (x == grid[y].size() - 1)
            {
                std::cout << std::endl;
            }
        }
    }

    std::cout << std::endl;

    std::cout << "visible trees: " << visible.size() << std::endl;

    return 0;
}