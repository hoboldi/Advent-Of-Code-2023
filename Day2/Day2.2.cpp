#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

uint lineSolver(std::string line) {
    std::string toSolve = line.substr(line.find(": ") + 2);

    std::vector<std::string> splitLine(0);
    std::string segment;

    while (std::getline(std::stringstream(toSolve), segment, ';')) {
        splitLine.push_back(segment);
        if(segment.size() + 2 > toSolve.size())
            break;
        toSolve = toSolve.substr(segment.size() + 2);
    }

    uint maxRed = 0, maxGreen = 0, maxBlue = 0;

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

        maxRed = maxRed < sumRed ? sumRed : maxRed;
        maxBlue = maxBlue < sumBlue ? sumBlue : maxBlue;
        maxGreen = maxGreen < sumGreen ? sumGreen : maxGreen;
    }
    return maxRed * maxBlue * maxGreen;
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
        sum += lineSolver(line);

        if(inputFile.eof())
            break;
    }

    std::cout << sum;
}