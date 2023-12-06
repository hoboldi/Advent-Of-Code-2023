#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

int getDigits(std::string line) {
    std::string number = "";
    for(std::size_t i = 0; i < line.size(); i++) {
        if(isdigit(line.at(i))) {
            number.push_back(line.at(i));
            break;
        }
    }
    for(int i = line.size() - 1; i >= 0; i--) {
        if(isdigit(line.at(i))) {
            number.push_back(line.at(i));
            break;
        }
    }
    return stoi(number);
}


int main() {
    u_int64_t sum = 0;
    bool toRead = true;
    int lastNumber = 0;
    int i = 0;

    std::string inputName = "../../Day1/Day1.txt";
    std::ifstream inputFile (inputName);
    if (!inputFile)
        throw std::runtime_error("Could not open file " + std::string(inputName));

    while(toRead) {
        sum += (u_int64_t) lastNumber;

        std::string line;
        inputFile >> line;

        lastNumber = getDigits(line);

        if(inputFile.eof())
            break;
    }
    sum += (u_int64_t) lastNumber;

    assert(sum == 54304);
    std::cout << sum << std::endl;
}