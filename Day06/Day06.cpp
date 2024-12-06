#include <cassert>
#include <fstream>
#include <print>
#include <set>
#include <string>
#include <vector>
std::string Filename = "TestInput.txt";
//std::string Filename = "Input.txt";

class MovementChar
{
public:
    void SetPosition(size_t InX, size_t InY)
    {
        X = static_cast<int>(InX);
        Y = static_cast<int>(InY);
        visited.emplace(X, Y);
    }
    void SetSize(size_t InX, size_t InY)
    {
        SizeX = static_cast<int>(InX);
        SizeY = static_cast<int>(InY);
    }

    void Rotate()
    {
        if (dirY == -1 || dirY == 1)
        {
            dirX = -dirY;
            dirY = 0;
        }
        else
        {
            dirY = dirX;
            dirX = 0;
        }
    }

    bool Move(const std::vector<std::string>& InMaze)
    {
        steps++;
        const int nextX = X + dirX;
        const int nextY = Y + dirY;
        if (nextX < 0 || nextX >= SizeX || nextY < 0 || nextY >= SizeY)
            return false;

        if (steps >= 10000)
        {
            InLoop = true;
            return false;
        }

        if (InMaze[nextY][nextX] == '#')
        {
            steps--;
            Rotate();
        }
        else
        {
            X = nextX;
            Y = nextY;
            visited.emplace(X, Y);
        }
        return true;
    }
    int steps = 0;
    std::set<std::pair<int, int>> visited;
    int X = -1, Y = -1;
    int SizeX = -1, SizeY = -1;
    int dirX = 0, dirY = -1;
    bool InLoop = false;
};

int main(int /*argc*/, char* /*argv*/[])
{
    std::ifstream inputFile;
    inputFile.open(Filename);
    std::string inputLine;
    std::vector<std::string> mazeLayout;
    MovementChar guard;
    while (inputFile.is_open() && !inputFile.eof())
    {
        auto& newLine = mazeLayout.emplace_back();
        std::getline(inputFile, newLine);

        if (size_t index = newLine.find('^'); index != std::string::npos)
        {
            std::println("Found start at {}, {}", index + 1, mazeLayout.size());
            guard.SetPosition(index, mazeLayout.size() - 1);
        }
    }
    int startX = guard.X, startY = guard.Y;
    assert(mazeLayout.size() > 0);
    guard.SetSize(mazeLayout[0].size(), mazeLayout.size());
    while (guard.Move(mazeLayout))
    {}

    std::set<std::pair<int, int>> visited = guard.visited;
    visited.erase({startX, startY});
    int loopLocationsFound = 0;
    for (const std::pair<int, int>& position : visited)
    {
        std::vector<std::string> mazeLayoutModified = mazeLayout;
        MovementChar guardModified;
        guardModified.SetPosition(startX, startY);
        guardModified.SetSize(guard.SizeX, guard.SizeY);
        mazeLayoutModified[position.second][position.first] = '#';

        while (guardModified.Move(mazeLayoutModified))
        {}

        if (guardModified.InLoop)
            loopLocationsFound++;
    }
    
    std::println("Day 6 part 1 num visited: {}", guard.visited.size());
    std::println("Day 6 part 2 loop locations found: {}", loopLocationsFound);
    
    return 0;
}
