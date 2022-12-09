#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <vector>
#include <sstream>

std::vector<std::string> split(const std::string &str, const char *sep)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);

    while (ss.good())
    {
        std::string substr;
        getline(ss, substr, *sep);
        tokens.push_back(substr);
    }

    return tokens;
}

struct Range
{
    int start;
    int end;
};

int main()
{
    std::ifstream file("./input");
    int overlaps = 0;

    if (file.is_open())
    {
        std::string line;

        Range a, b;

        while (std::getline(file, line))
        {

            std::vector<std::string> segments = split(line, ",");

            std::vector<std::string> raw_range_a = split(segments[0], "-");
            std::vector<std::string> raw_range_b = split(segments[1], "-");

            a.start = stoi(raw_range_a[0]);
            a.end = stoi(raw_range_a[1]);
            b.start = stoi(raw_range_b[0]);
            b.end = stoi(raw_range_b[1]);

            if (
                (a.start >= b.start && a.start <= b.end) ||
                (b.start >= a.start && b.end <= a.end) ||
                (a.end >= b.start && a.end <= b.end) ||
                (b.end >= a.start && b.end <= a.end))
            {
                std::cout << "overlap at " << line << std::endl;
                ++overlaps;
            }
        }

        file.close();

        printf("%d overlaps\n", overlaps);
    }

    return 0;
}