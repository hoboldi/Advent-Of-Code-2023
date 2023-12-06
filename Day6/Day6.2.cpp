#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>
#include <cassert>

ulong intParser(const std::string& line) {

    std::istringstream iss(line);
    std::string returnNumber;

    std::string split;
    while (std::getline(iss, split, ' '))
    {
        if(split == "")
            continue;
        returnNumber += split;
    }

    return stoull(returnNumber);
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

    ulong time = intParser(input[0].substr(5));
    ulong distance = intParser(input[1].substr(9));
    ulong numberOfPossibleWins = 0;

    for(size_t i = 0; i <= time; i++) {
        ulong traveledDistance = (time - i) * i;
        numberOfPossibleWins = traveledDistance > distance ? numberOfPossibleWins + 1 : numberOfPossibleWins;
    }

    assert(numberOfPossibleWins == 316800);
    std::cout << numberOfPossibleWins << std::endl;
}
