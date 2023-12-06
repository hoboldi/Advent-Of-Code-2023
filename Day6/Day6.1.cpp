#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>

std::vector<uint> intParser(const std::string& line) {

    std::istringstream iss(line);
    std::vector<uint> returnVector(0);

    std::string split;
    while (std::getline(iss, split, ' '))
    {
        if(split == "")
            continue;
        returnVector.push_back(stoul(split));
    }

    return returnVector;
}


int main() {
    std::string inputName = "../../Day6/Day6.txt";
    std::ifstream inputFile (inputName);
    if (!inputFile)
        throw std::runtime_error("Could not open file " + std::string(inputName));

    std::vector <std::string> input(0);

    while (true) {
        std::string line;
        getline(inputFile, line);
        input.push_back(line);

        if(inputFile.eof())
            break;
    }

    std::vector<uint> times = intParser(input[0].substr(5));
    std::vector<uint> distances = intParser(input[1].substr(9));

    uint result = 1;

    for(size_t i = 0; i < times.size(); i++) {
        uint numberOfPossibleWins = 0;

        for(size_t j = 0; j <= times[i]; j++) {
            uint traveledDistance = (times[i] - j) * j;
            numberOfPossibleWins = traveledDistance > distances[i] ? numberOfPossibleWins + 1 : numberOfPossibleWins;
        }

        result *= numberOfPossibleWins;
    }

    std::cout << result;
}
