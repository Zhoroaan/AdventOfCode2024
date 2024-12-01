#include <algorithm>
#include <cassert>
#include <fstream>
#include <print>
#include <sstream>
#include <string>
#include <vector>

std::string Filename = "TestInput.txt";
//std::string Filename = "Input.txt";

static void CalculatePartOne(const std::vector<int64_t>& InLeftNumbers, const std::vector<int64_t>& InRightNumbers)
{
    int64_t totalDistance = 0;
    for (size_t i = 0; i < InLeftNumbers.size(); i++)
    {
        int64_t left = InLeftNumbers[i];
        int64_t right = InRightNumbers[i];
        int64_t distance = std::abs(left - right);
        totalDistance += distance;
    }
    
    std::println("Part 1: Total distance is {}" , totalDistance);
}

static void CalculatePartTwo(const std::vector<int64_t>& InLeftNumbers, const std::vector<int64_t>& InRightNumbers)
{
    int64_t totalDistance = 0;
    for (const int64_t& left : InLeftNumbers)
    {
        int64_t occurrences = 0;
        for (const auto& num : InRightNumbers)
        {
            if (num > left)
                break;
            if (num == left)
                occurrences++;
        }
        totalDistance += left * occurrences;
    }
    
    std::println("Part 2: Similarity score is {}" , totalDistance);
}

int main(int /*argc*/, char* /*argv*/[])
{
    std::ifstream inputFile;
    inputFile.open(Filename);
    std::string inputLine;

    std::vector<int64_t> leftNumbers, rightNumbers;

    while (inputFile.is_open() && !inputFile.eof())
    {
        std::getline(inputFile, inputLine);
        int64_t leftNumber = 0, rightNumber = 0;
        std::stringstream readLine(inputLine);
        readLine >> leftNumber >> rightNumber;
        leftNumbers.push_back(leftNumber);
        rightNumbers.push_back(rightNumber);
    }
    assert(leftNumbers.size() == rightNumbers.size());
    std::ranges::sort(leftNumbers);
    std::ranges::sort(rightNumbers);
    CalculatePartOne(leftNumbers, rightNumbers);
    CalculatePartTwo(leftNumbers, rightNumbers);
    
    return 0;
}
