#include <fstream>
#include <map>
#include <print>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <vector>
std::string Filename = "TestInput.txt";
//std::string Filename = "Input.txt";

int main(int /*argc*/, char* /*argv*/[])
{
    std::ifstream inputFile;
    inputFile.open(Filename);
    std::vector<std::string> inputData;
    
    while (inputFile.is_open() && !inputFile.eof())
    {
        std::getline(inputFile, inputData.emplace_back());
    }
    int sizeX = static_cast<int>(inputData[0].size());
    int sizeY = static_cast<int>(inputData.size());
    std::map<char, std::vector<std::pair<int, int>>> antennaLocations;
    for (size_t y = 0; y < inputData.size(); ++y)
    {
        for (size_t x = 0; x < inputData[y].size(); ++x)
        {
            if (inputData[y][x] == '.')
                continue;
            antennaLocations[inputData[y][x]].emplace_back(static_cast<int>(x), static_cast<int>(y));
        }
    }
    std::set<std::pair<int, int>> part1ResonanceLocations;
    std::set<std::pair<int, int>> part2ResonanceLocations;
    for (const auto& val : antennaLocations | std::views::values)
    {
        for (int compareIndex = 0; compareIndex < val.size(); ++compareIndex)
        {
            for (int compareOther = compareIndex + 1; compareOther < val.size(); ++compareOther)
            {
                const auto& current = val[compareIndex];
                const auto& compare = val[compareOther];
                std::pair<int, int> diff = {compare.first - current.first, compare.second - current.second};
                std::pair<int, int> resonancePos1 = {current.first - diff.first, current.second - diff.second};
                std::pair<int, int> resonancePos2 = {compare.first + diff.first, compare.second + diff.second};
                part2ResonanceLocations.emplace(current.first, current.second);
                part2ResonanceLocations.emplace(compare.first, compare.second);
                if (resonancePos1.first >= 0 && resonancePos1.first < sizeX && resonancePos1.second >= 0 && resonancePos1.second < sizeY)
                {
                    part1ResonanceLocations.emplace(resonancePos1);
                }
                if (resonancePos2.first >= 0 && resonancePos2.first < sizeX && resonancePos2.second >= 0 && resonancePos2.second < sizeY)
                {
                    part1ResonanceLocations.emplace(resonancePos2);
                }
                for (int step = 1; current.first - diff.first * step >= 0 && current.first - diff.first * step < sizeX
                    && current.second - diff.second * step >= 0 && current.second - diff.second * step < sizeY; ++step)
                {
                    int x = current.first - diff.first * step;
                    int y = current.second - diff.second * step;
                    part2ResonanceLocations.emplace(x, y);
                }

                for (int step = 1; compare.first + diff.first * step >= 0 && compare.first + diff.first * step < sizeX
                    && compare.second + diff.second * step >= 0 && compare.second + diff.second * step < sizeY; ++step)
                {
                    int x = compare.first + diff.first * step;
                    int y = compare.second + diff.second * step;
                    part2ResonanceLocations.emplace(x, y);
                }
            }
        }
    }
    int32_t part1ResonanceCount = 0;
    for (const std::pair<int, int>& data : part1ResonanceLocations)
    {
        part1ResonanceCount++;
        //std::println("Antenna resonance at {} {}", data.first, data.second);
    }
    int32_t part2ResonanceCount = 0;
    for (const std::pair<int, int>& data : part2ResonanceLocations)
    {
        part2ResonanceCount++;
        std::println("Antenna resonance at {} {}", data.first, data.second);
    }
    
    std::println("Day 8 Part 1 unique locations: {}", part1ResonanceCount);
    std::println("Day 8 Part 2 unique locations: {}", part2ResonanceCount);
    
    return 0;
}
