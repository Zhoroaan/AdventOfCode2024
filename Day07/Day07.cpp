#include <fstream>
#include <print>
#include <sstream>
#include <string>
#include <vector>
std::string Filename = "TestInput.txt";
//std::string Filename = "Input.txt";

uint64_t OrOperator(uint64_t InCurrentValue, uint64_t nextNumber)
{
    int64_t nextNumDigets = std::to_string(nextNumber).length();
    return (InCurrentValue * std::powl(10,  nextNumDigets)) + nextNumber;
}

bool TryCombine(uint64_t InCurrentValue, uint64_t InNextIndex, uint64_t InTarget,
    const std::vector<uint64_t>& InNumbers, bool bInUseOrOperator)
{
    if (InCurrentValue > InTarget)
        return false;
    uint64_t nextNumber = InNumbers[InNextIndex];
    uint64_t orResult = OrOperator(InCurrentValue, nextNumber);
    if (InNextIndex == InNumbers.size() - 1)
    {
        bool orOperatorOk = orResult == InTarget;
        return InCurrentValue + nextNumber == InTarget
            || InCurrentValue * nextNumber == InTarget
            || (bInUseOrOperator && orOperatorOk);
    }
    return TryCombine(InCurrentValue + nextNumber, InNextIndex + 1, InTarget, InNumbers, bInUseOrOperator)
        || TryCombine(InCurrentValue * nextNumber, InNextIndex + 1, InTarget, InNumbers, bInUseOrOperator)
        || (bInUseOrOperator
                && TryCombine(orResult, InNextIndex + 1, InTarget, InNumbers, bInUseOrOperator));
}

int main(int /*argc*/, char* /*argv*/[])
{
    std::ifstream inputFile;
    inputFile.open(Filename);
    std::string inputLine;
    std::vector<std::vector<uint64_t>> inputNumbers;
    
    while (inputFile.is_open() && !inputFile.eof())
    {
        std::getline(inputFile, inputLine);
        std::stringstream ss(inputLine);
        auto& newLine = inputNumbers.emplace_back();
        ss >> newLine.emplace_back();
        ss.ignore(2);
        while (!ss.eof())
        {
            ss >> newLine.emplace_back();
            ss.ignore(1);
        }
    }
    uint64_t part1Result = 0;
    uint64_t part2Result = 0;
    for (const auto& line : inputNumbers)
    {
        if (TryCombine(line[1], 2, line[0], line, false))
            part1Result += line[0];
        if (TryCombine(line[1], 2, line[0], line, true))
            part2Result += line[0];
    }
    std::println("Part 1 result: {}", part1Result);
    std::println("Part 2 result: {}", part2Result);
    
    return 0;
}
