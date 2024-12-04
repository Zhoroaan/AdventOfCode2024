#include <fstream>
#include <print>
#include <string>
#include <vector>
std::string Filename = "TestInput.txt";
//std::string Filename = "Input.txt";

struct Part1Iterator
{
    Part1Iterator(int InX, int InY, int InXDiff, int InYDiff, int InMaxX, int InMaxY, const std::string& InSearchString, const std::vector<std::string>& InSearchData)
        : X(InX), Y(InY), XDiff(InXDiff), YDiff(InYDiff), MaxX(InMaxX), MaxY(InMaxY), SearchString(InSearchString)
    {
        const bool noDiff = XDiff == 0 && YDiff == 0;
        if (noDiff || InX < 0 || InX > MaxX || InY < 0 || InY > MaxY)
            IsValid = false;
        else
            IsValid = InSearchData[InY][InX] == SearchString[0];
    }
    void Next(const std::vector<std::string>& InSearchData)
    {
        if (!IsValid)
            return;
        X += XDiff;
        Y += YDiff;
        Steps++;
        if (X < 0 || X > MaxX || Y < 0 || Y > MaxY)
        {
            IsValid = false;
            return;
        }

        char t = InSearchData[Y][X];
        IsValid &= InSearchData[Y][X] == SearchString[Steps];
    }

    void RunSearch(const std::vector<std::string>& InData)
    {
        for (int steps = 0; steps < SearchString.size() - 1; ++steps)
        {
            Next(InData);
            if (!IsValid)
                break;
        }
    }
    int X, Y;
    int XDiff, YDiff;
    int MaxX, MaxY;
    std::string SearchString;
    bool IsValid = true;
    int Steps = 0;
};

struct Part2Iterator
{
    Part2Iterator(int InX, int InY,int InMaxX, int InMaxY, const std::vector<std::string>& InSearchData)
        : X(InX)
        , Y(InY)
    , MaxX(InMaxX),
     MaxY(InMaxY)
    {
    }

    void RunSearch(const std::vector<std::string>& InData)
    {
        if (!IsValidPosition(X, Y))
        {
            IsValid = false;
            return;
        }
        IsValid &= InData[Y][X] == 'A';
        if (!IsValid)
            return;
        
        std::string leftToRight = {InData[Y-1][ X-1], InData[Y+1][X+1]};
        std::string rightToLeft = {InData[Y+1][ X-1], InData[Y-1][X+1]};
        constexpr auto searchRange = {"MS", "SM"};
        IsValid &= std::ranges::find(searchRange, leftToRight) != searchRange.end()
                    && std::ranges::find(searchRange, rightToLeft) != searchRange.end();
    }

    bool IsValidPosition(int InX, int InY) const
    {
        return InX - 1 >= 0 && InX + 1 <= MaxX && InY -1 >= 0 && InY + 1 <= MaxY;
    }
    
    int X, Y;
    int MaxX;
    int MaxY;
    std::string SearchString;
    bool IsValid = true;
    int Steps = 0;
};

int main(int /*argc*/, char* /*argv*/[])
{
    std::ifstream inputFile;
    inputFile.open(Filename);
    std::vector<std::string> inputData;
    while (inputFile.is_open() && !inputFile.eof())
    {
        std::getline(inputFile, inputData.emplace_back());
    }

    int64_t part1Found = 0;
    int64_t part2Found = 0;
    
    const std::string part1SearchString = "XMAS";
    int sizeY = static_cast<int>(inputData.size());
    for (int ySearch = 0; ySearch < sizeY; ++ySearch)
    {
        int sizeX = static_cast<int>(inputData[ySearch].size());
        for (int xSearch = 0; xSearch < sizeX; ++xSearch)
        {
            for (int y = -1; y <= 1; ++y)
            {
                for (int x = -1; x <= 1; ++x)
                {
                    Part1Iterator part1Iterator(xSearch, ySearch, x, y, sizeX-1, sizeY-1, part1SearchString, inputData);
                    part1Iterator.RunSearch(inputData);
                    if (part1Iterator.IsValid)
                        part1Found++;
                }
            }
            Part2Iterator part2Iterator(xSearch, ySearch, sizeX-1, sizeY-1, inputData);
            part2Iterator.RunSearch(inputData);
            if (part2Iterator.IsValid)
                part2Found++;
        }
    }

    std::println("Day 4 number found Part 1 {}", part1Found);
    std::println("Day 4 number found Part 2 {}", part2Found);
    
    return 0;
}
