#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

char checkWordDigit(std::string line) {
    switch (line.size()) {
        case 3:
            if(line == "one")
                return '1';
            if(line == "two")
                return '2';
            if(line == "six")
                return '6';
            return -1;
        case 4:
            if(line == "four")
                return '4';
            if(line == "five")
                return '5';
            if(line == "nine")
                return '9';
            return -1;
        case 5:
            if(line == "three")
                return '3';
            if(line == "seven")
                return '7';
            if(line == "eight")
                return '8';
            return -1;
    }
    return -1;
}


int getDigits(std::string line) {
    std::string number = "";
    for(std::size_t i = 0; i < line.size(); i++) {

        if(isdigit(line.at(i))) {
            number.push_back(line.at(i));
            break;
        }

        if(i + 3 >= line.size())
            continue;
        if(checkWordDigit(line.substr(i,3)) != -1) {
            number.push_back(char(checkWordDigit(line.substr(i,3))));
            break;
        }

        if(i + 4 >= line.size())
            continue;
        if(checkWordDigit(line.substr(i,4)) != -1) {
            number.push_back(char(checkWordDigit(line.substr(i,4))));
            break;
        }

        if(i + 5 >= line.size())
            continue;
        if(checkWordDigit(line.substr(i,5)) != -1) {
            number.push_back(char(checkWordDigit(line.substr(i,5))));
            break;
        }

    }

    for(int i = line.size() - 1; i >= 0; i--) {
        if(isdigit(line.at(i))) {
            number.push_back(line.at(i));
            break;
        }

        if(i - 2 < 0)
            continue;
        if(checkWordDigit(line.substr(i - 2,3)) != -1) {
            number.push_back(char(checkWordDigit(line.substr(i - 2,3))));
            break;
        }

        if(i - 3 < 0)
            continue;
        if(checkWordDigit(line.substr(i - 3,4)) != -1) {
            number.push_back(checkWordDigit(line.substr(i - 3,4)));
            break;
        }

        if(i - 4 < 0)
            continue;
        if(checkWordDigit(line.substr(i - 4,5)) != -1) {
            number.push_back(char(checkWordDigit(line.substr(i - 4,5))));
            break;
        }
    }
    return stoi(number);
}


int main() {
    std::string inputName = "../../Day1/Day1.txt";
    std::ifstream inputFile (inputName);
    if (!inputFile)
        throw std::runtime_error("Could not open file " + std::string(inputName));

    u_int64_t sum = 0;
    bool toRead = true;
    int lastNumber = 0;
    int i = 0;
    while(toRead) {
        sum += (u_int64_t) lastNumber;

        std::string line;
        inputFile >> line;

        lastNumber = getDigits(line);

        if(inputFile.eof())
            break;
    }
    sum += (u_int64_t) lastNumber;

    assert(sum == 54418);
    std::cout << sum << std::endl;
}