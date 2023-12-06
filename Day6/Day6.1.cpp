#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
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

typedef std::pair<uint, uint> pair;




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

}
