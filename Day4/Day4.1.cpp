#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>

std::vector<uint> intParser(const std::string& line) {

    std::istringstream iss(line);
    std::vector<uint> returnVector(0);

    std::string split;
    while (std::getline(iss, split, ' '))
    {
        if(split == "")
            continue;
        returnVector.push_back(stoi(split));
    }

    return returnVector;
}

uint checkScore(std::vector<uint> winningNumbers, std::vector<uint> myCards) {
    int wIndex = 0, mIndex = 0;

    uint score = 1;

    while(wIndex < winningNumbers.size() && mIndex < myCards.size()) {
        if(winningNumbers[wIndex] == myCards[mIndex]) {
            score = score << 1;
            wIndex++;
            mIndex++;
        } else {
            if(winningNumbers[wIndex] < myCards[mIndex]) {
                wIndex++;
            } else {
                mIndex++;
            }
        }
    }
    return score/2;
}


int main() {
    std::string inputName = "../../Day4/Day4.txt";
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
    uint sum = 0;

    for(size_t i = 0; i < input.size(); i++) {
        std::vector<uint> winningNumbers;
        std::vector<uint> myCards;

        input[i] = input[i].substr(input[i].find(':') + 2);
        std::string part1 = input[i].substr(0,input[i].find('|') - 1);
        std::string part2 = input[i].substr(input[i].find('|') + 2);

        winningNumbers = intParser(part1);
        myCards = intParser(part2);

        std::sort(winningNumbers.begin(),winningNumbers.end());
        std::sort(myCards.begin(),myCards.end());

        sum += checkScore(winningNumbers,myCards);
    }
    std::cout << sum;
}