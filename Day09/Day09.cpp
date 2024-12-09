#include <chrono>
#include <fstream>
#include <print>
#include <string>
#include <vector>
//std::string Filename = "TestInput.txt";
std::string Filename = "Input.txt";

static int64_t GetNumberFromChar(char InChar)
{
    return InChar - '0';
}

static void Part1Compact(std::vector<int64_t>& InOutPart1Numbers)
{
    for (int index = static_cast<int>(InOutPart1Numbers.size()) -1; index >= 0; --index)
    {
        if (InOutPart1Numbers[index] == -1)
            continue;
        
        for (int start = 0; start < index; ++start)
        {
            if (InOutPart1Numbers[start] == -1)
            {
                InOutPart1Numbers[start] = InOutPart1Numbers[index];
                InOutPart1Numbers[index] = -1;
            }
        }
    }
}

static int FindNumberOfFree(const std::vector<int64_t>& InOutPart2Numbers, int InIndex)
{
    int count = 1;
    for (int x = InIndex - 1; x >= 0; --x)
    {
        if (InOutPart2Numbers[x] != InOutPart2Numbers[InIndex])
            break;
        count++;
    }
    return count;
}

static void Part2Compact(std::vector<int64_t>& InOutPart2Numbers)
{
    for (int index = static_cast<int>(InOutPart2Numbers.size()) -1; index >= 0; --index)
    {
        if (InOutPart2Numbers[index] == -1)
            continue;
        int count = FindNumberOfFree(InOutPart2Numbers, index);
        
        for (int start = 0; start < index; ++start)
        {
            if (InOutPart2Numbers[start] != -1)
                continue;

            int freeCount = 1;

            for (int freeSearch = start + 1; freeSearch < index; ++freeSearch)
            {
                if (InOutPart2Numbers[freeSearch] != -1)
                    break;
                freeCount++;
            }

            if (freeCount < count)
                continue;
            
            const int64_t moveValue = InOutPart2Numbers[index];
            for (int copy = 0; copy < count; ++copy)
            {
                InOutPart2Numbers[start + copy] = moveValue;
                InOutPart2Numbers[index - copy] = -1;
            }
            break;
        }
        index -= count - 1;
    }
}

int main(int /*argc*/, char* /*argv*/[])
{
    std::ifstream inputFile;
    inputFile.open(Filename);
    std::string inputLine;
    std::getline(inputFile, inputLine);
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int64_t> part1Numbers;
    for (int index = 0; index < inputLine.size(); ++index)
    {
        int64_t value = index % 2 == 0 ? index / 2 : -1;
        for (int repeats = 0; repeats <  GetNumberFromChar(inputLine[index]); ++repeats)
            part1Numbers.push_back(value);
    }
    std::vector<int64_t> part2Numbers = part1Numbers;
    Part1Compact(part1Numbers);
    Part2Compact(part2Numbers);

    int64_t part1Sum = 0;
    int64_t part2Sum = 0;
    for (int index = 0; index < static_cast<int>(part1Numbers.size()); ++index)
    {
        if (part1Numbers[index] != -1)
            part1Sum += part1Numbers[index] * index;

        if (part2Numbers[index] != -1)
            part2Sum += part2Numbers[index] * index;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::println("Day 9 part 1: {}", part1Sum);
    std::println("Day 9 part 2: {}", part2Sum);
    std::println("Execution time: {0}ms", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    
    return 0;
}
