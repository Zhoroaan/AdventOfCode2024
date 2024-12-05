#include <algorithm>
#include <fstream>
#include <print>
#include <sstream>
#include <string>
#include <vector>
std::string Filename = "TestInput.txt";
//std::string Filename = "Input.txt";

int main(int /*argc*/, char* /*argv*/[])
{
    std::ifstream inputFile;
    inputFile.open(Filename);
    std::string inputLine;
    bool part1 = true;
    std::vector<std::pair<int, int>> rules;
    std::vector<std::vector<int>> linesToCheck;
    while (inputFile.is_open() && !inputFile.eof())
    {
        std::getline(inputFile, inputLine);
        if (inputLine.empty())
            part1 = false;
        else if (part1)
        {
            std::pair<int, int>& newValue = rules.emplace_back();
            std::stringstream ss(inputLine);
            ss >> newValue.first;
            ss.ignore(1);
            ss >> newValue.second;
        }
        else
        {
            std::stringstream ss(inputLine);
            std::vector<int> newLineNumbers;
            while (!ss.eof())
            {
                ss >> newLineNumbers.emplace_back();
                ss.ignore(1);
            }
            if (!newLineNumbers.empty())
                linesToCheck.push_back(std::move(newLineNumbers));
        }
    }

    int part1Accumulator = 0;
    int part2Accumulator = 0;

    for (std::vector<int> line : linesToCheck) // Copy the vector to avoid modifying the original
    {
        bool wasEverIncorrect = false;
        bool followRule = true;
        do
        {
            for (const std::pair<int, int>& rule : rules)
            {
                followRule = true;
                auto firstFound = std::ranges::find(line, rule.first);
                auto secondFound = std::ranges::find(line, rule.second);
                if (firstFound == line.end() || secondFound == line.end())
                    continue;
                if (firstFound > secondFound)
                {
                    std::iter_swap(firstFound, secondFound);
                    followRule = false;
                    wasEverIncorrect = true;
                    break;
                }
            }
        } while (!followRule);
        
        if (wasEverIncorrect)
            part2Accumulator += line[line.size() / 2];
        else
            part1Accumulator += line[line.size() / 2];
    }
    std::println("Day 5 part 1: {}", part1Accumulator);
    std::println("Day 5 part 2: {}", part2Accumulator);
    
    return 0;
}
