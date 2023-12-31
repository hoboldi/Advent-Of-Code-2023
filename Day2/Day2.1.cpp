#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>

const uint red = 12, green = 13, blue = 14;

bool lineSolver(std::string line) {
    std::string toSolve = line.substr(line.find(": ") + 2);

    std::vector<std::string> splitLine(0);
    std::string segment;

    while (std::getline(std::stringstream(toSolve), segment, ';')) {
        splitLine.push_back(segment);
        if(segment.size() + 2 > toSolve.size())
            break;
        toSolve = toSolve.substr(segment.size() + 2);
    }


    for(std::size_t i = 0; i < splitLine.size(); i++) {

        uint sumRed = 0, sumGreen = 0, sumBlue = 0;

        while (std::getline(std::stringstream(splitLine.at(i)), segment, ',')) {

            std::string number;

            if(segment.find("red") != -1) {
                std::getline(std::stringstream(segment), number, ' ');
                sumRed += std::stoi(number);
            }

            if(segment.find("green") != -1) {
                std::getline(std::stringstream(segment), number, ' ');
                sumGreen += std::stoi(number);
            }

            if(segment.find("blue") != -1) {
                std::getline(std::stringstream(segment), number, ' ');
                sumBlue += std::stoi(number);
            }

            if(segment.size() + 2 > splitLine.at(i).size())
                break;
            splitLine.at(i) = splitLine.at(i).substr(segment.size() + 2);

        }

        if(sumRed > red || sumBlue > blue || sumGreen > green)
            return false;

    }
    return true;
}



int main() {
    std::string inputName = "../../Day2/Day2.txt";
    std::ifstream inputFile (inputName);
    if (!inputFile)
        throw std::runtime_error("Could not open file " + std::string(inputName));

    uint sum = 0;
    uint i = 0;

    while(true) {
        std::string line;
        std::getline(inputFile, line);

        i++;
        sum += lineSolver(line) ? i : 0;

        if(inputFile.eof())
            break;
    }

    assert(sum == 2512);
    std::cout << sum << std::endl;
}