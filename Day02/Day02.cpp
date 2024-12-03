#include <cassert>
#include <fstream>
#include <print>
#include <sstream>
#include <string>
#include <vector>
std::string Filename = "TestInput.txt";
//std::string Filename = "Input.txt";

static bool IsSafe(const std::vector<int64_t>& InNumbers)
{
    assert(!InNumbers.empty());
    bool increasing = true, decreasing = true, smallJumps = true;
    int64_t lastNumber = InNumbers[0];
    for (int index = 1; index < InNumbers.size(); ++index)
    {
        increasing &= InNumbers[index] > lastNumber;
        decreasing &= InNumbers[index] < lastNumber;
        smallJumps &= std::abs(InNumbers[index] - lastNumber) <= 3;
        lastNumber = InNumbers[index];
    }
    return (increasing ||decreasing) && smallJumps;
}

static bool CanBeMadeSafe(const std::vector<int64_t>& InNumbers)
{
    for (int index = 0; index < InNumbers.size(); ++index)
    {
        std::vector<int64_t> copy = InNumbers;
        copy.erase(copy.begin() + index);
        if (IsSafe(copy))
            return true;
    }
    return false;
}

int main(int /*argc*/, char* /*argv*/[])
{
    std::ifstream inputFile;
    inputFile.open(Filename);

    int64_t numSafeReportsPart1 = 0;
    int64_t numSafeReportsPart2 = 0;

    std::string inputLine;
    while (inputFile.is_open() && !inputFile.eof())
    {
        std::getline(inputFile, inputLine);
        std::vector<int64_t> numbers;
        for (std::stringstream sb(inputLine); !sb.eof();)
            sb >> numbers.emplace_back();
        //std::println("Part 1: {}: is {}", inputLine, IsSafe(numbers) ? "Safe" : "Unsafe");
        //std::println("Part 2: {}: is {}", inputLine, IsSafe(numbers) || CanBeMadeSafe(numbers) ? "Safe" : "Unsafe");
        numSafeReportsPart1 += IsSafe(numbers) ? 1 : 0;
        numSafeReportsPart2 += IsSafe(numbers) || CanBeMadeSafe(numbers) ? 1 : 0;
    }

    std::println("Part 1: num of safe reports {}" , numSafeReportsPart1);
    std::println("Part 2: num of safe reports {}" , numSafeReportsPart2);
    
    return 0;
}
