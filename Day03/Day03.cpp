#include <fstream>
#include <iostream>
#include <print>
#include <regex>
#include <string>
const std::string Filename = "TestInput.txt";
//const std::string Filename = "Input.txt";

int main(int /*argc*/, char* /*argv*/[])
{
    std::ifstream inputFile;
    inputFile.open(Filename);
    
    std::string text(std::istreambuf_iterator(inputFile), {});

    // Find strings matching mul(number, number) or "do()" or "don't()"
    std::regex matchRe(R"(mul\(\d+,\d+\)|do\(\)|don't\(\))");
    auto matchStart = std::sregex_iterator(text.begin(), text.end(), matchRe);
    auto matchEnd = std::sregex_iterator();

    int64_t part1Value = 0;
    int64_t part2Value = 0;
    bool enabled = true;
    for (std::sregex_iterator i = matchStart; i != matchEnd; ++i) {
        const std::smatch& match = *i;
        std::string match_str = match.str();
        if (match_str == "do()")
            enabled = true;
        else if (match_str == "don't()")
            enabled = false;
        else
        {
            int64_t a, b;
            sscanf_s(match_str.c_str(), "mul(%lld,%lld)", &a, &b);
            part1Value += a * b;
            if (enabled)
                part2Value += a * b;
        }
    }
    std::println("Day 03 Part 1: {}", part1Value);
    std::println("Day 03 Part 2: {}", part2Value);
    
    return 0;
}
