#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

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

    uint score = 0;

    while(wIndex < winningNumbers.size() && mIndex < myCards.size()) {
        if(winningNumbers[wIndex] == myCards[mIndex]) {
            score++;
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
    return score;
}


int main() {
    std::vector <std::string> input(0);

    while (true) {
        std::string line;
        getline(std::cin, line);

        if (line == "END")
            break;

        input.push_back(line);
    }

    std::vector<uint> numberOfCards(input.size(), 1);

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

        uint score = checkScore(winningNumbers,myCards);
        for(std::size_t j = 1; j <= score && j + i < numberOfCards.size(); j++) {
            numberOfCards[j + i] += numberOfCards[i];
        }
    }

    uint sum = 0;
    for(std::size_t i = 0; i < numberOfCards.size(); i++)
        sum += numberOfCards[i];

    std::cout << sum;
}