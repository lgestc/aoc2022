#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
#include <vector>

const static uint8_t win = {6};
const static uint8_t draw = {3};
const static uint8_t loss = {0};

const static uint8_t rock = {1};
const static uint8_t paper = {2};
const static uint8_t scissors = {3};

u_int8_t result(std::string &key)
{
    static std::map<std::string, uint8_t> m;

    // generate static reference map once (if empty)
    if (m.empty())
    {
        m["A X"] = {loss + scissors};
        m["A Y"] = {draw + rock};
        m["A Z"] = {win + paper};

        m["B X"] = {loss + rock};
        m["B Y"] = {draw + paper};
        m["B Z"] = {win + scissors};

        m["C X"] = {loss + paper};
        m["C Y"] = {draw + scissors};
        m["C Z"] = {win + rock};
    }

    if (m.find(key) != m.end())
    {
        return m[key];
    }

    return 0;
}

int main()
{
    std::ifstream file("./input");

    u_int32_t total = {0};

    if (file.is_open())
    {
        std::string line;

        while (std::getline(file, line))
        {
            u_int8_t res = result(line);

            total += res;

            std::cout << line << " result: " << unsigned(res) << std::endl;
        }

        file.close();
    }

    std::cout << "total: " << total << std::endl;

    return 0;
}