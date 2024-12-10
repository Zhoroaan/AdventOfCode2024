#include <chrono>
#include <fstream>
#include <iostream>
#include <print>
#include <set>
#include <string>
#include <vector>

std::string Filename = "TestInput.txt";
//std::string Filename = "Input.txt";

class Timer
{
public:
    Timer(const std::string& InName)
        : Name(InName){}

    ~Timer()
    {
        auto duration = std::chrono::high_resolution_clock::now() - StartTime;
        std::cout << Name << " took: " << std::chrono::duration_cast<std::chrono::microseconds>(duration).count() << "µs\n";
    }
protected:
    std::string Name;
    std::chrono::time_point<std::chrono::steady_clock> StartTime = std::chrono::high_resolution_clock::now();
};

static int64_t GetNumberFromChar(char InChar)
{
    return InChar - '0';
}

int64_t GetTrailRating(int64_t InLastValue, int InX, int InY, const std::vector<std::string>& InMap, std::set<std::pair<int, int>>& InVisited)
{
    if (InX < 0 || InX >= static_cast<int64_t>(InMap[0].size()) || InY < 0 || InY >= static_cast<int64_t>(InMap.size()))
        return 0;
    int64_t currentValue = GetNumberFromChar(InMap[InY][InX]);
    if (currentValue == 9 && InLastValue == 8)
    {
        InVisited.emplace(InX,  InY);
        return 1;
    }

    if (currentValue != InLastValue + 1)
        return 0;

    int64_t rating = 0;
    rating += GetTrailRating(currentValue, InX + 1, InY, InMap, InVisited);
    rating += GetTrailRating(currentValue, InX, InY + 1, InMap, InVisited);
    rating += GetTrailRating(currentValue, InX - 1, InY, InMap, InVisited);
    rating += GetTrailRating(currentValue, InX, InY - 1, InMap, InVisited);
    return rating;
}

int main(int /*argc*/, char* /*argv*/[])
{
    Timer main("Main");
    std::ifstream inputFile;
    inputFile.open(Filename);
    std::vector<std::string> inputData;
    while (inputFile.is_open() && !inputFile.eof())
    {
        std::getline(inputFile, inputData.emplace_back());
    }

    int64_t part1TrailScore = 0;
    int64_t part2TrailRating = 0;
    for (int y = 0; y < inputData.size(); ++y)
    {
        for (int x = 0; x < inputData[y].size(); ++x)
        {
            if (inputData[y][x] == '0')
            {
                std::set<std::pair<int, int>> visited;
                part2TrailRating += GetTrailRating(-1, x, y, inputData, visited);
                part1TrailScore += visited.size();
            }
        }
    }
    
    std::println("Day 10 part 1 score: {}", part1TrailScore);
    std::println("Day 10 part 2 rating: {}", part2TrailRating);
    
    return 0;
}
