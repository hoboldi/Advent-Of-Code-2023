#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>
#include <algorithm>
#include <cassert>

typedef std::string Hand;
typedef uint Bid;
typedef std::pair<Hand,Bid> pair;

enum Strength {
    High_card,
    One_pair,
    Two_pair,
    Three_of_a_kind,
    Full_house,
    Four_of_a_kind,
    Five_of_a_kind
};

pair intParser(const std::string& line) {

    std::istringstream iss(line);
    pair returnPair;

    std::string split;
    std::getline(iss, split, ' ');
    returnPair.first = split;
    std::getline(iss, split, ' ');
    returnPair.second = std::stoul(split);

    return returnPair;
}

Strength getStrength(const Hand& hand) {
    std::string copy = hand;
    std::sort(copy.begin(),copy.end());

    uint chain = 1;
    char last = copy[0];
    std::vector<uint> chains(0);

    for(size_t i = 1; i < copy.size(); i++) {
        if(last == copy[i]) {
            chain++;
        } else {
            chains.push_back(chain);
            last = copy[i];
            chain = 1;
        }
    }
    chains.push_back(chain);

    std::sort(chains.begin(), chains.end());

    switch (chains.size()) {
        case 1:
            return Five_of_a_kind;
        case 2:
            if(chains[0] == 1)
                return Four_of_a_kind;
            else
                return Full_house;
        case 3:
            if(chains[1] == 1)
                return Three_of_a_kind;
            else
                return Two_pair;
        case 4:
            return One_pair;
        case 5:
            return High_card;
    }
}

bool stringRanker(Hand hand1, Hand hand2) {
    for(std::size_t i = 0; i < hand1.size(); i++) {
        if(hand1[i] == hand2[i])
            continue;

        switch (hand1[i]) {
            case 'A':
                return false;
            case 'K':
                if(hand2[i] == 'A')
                    return true;
                else
                    return false;
            case 'Q':
                if(hand2[i] == 'A' || hand2[i] == 'K')
                    return true;
                else
                    return false;
            case 'J':
                if(hand2[i] == 'A' || hand2[i] == 'K' || hand2[i] == 'Q')
                    return true;
                else
                    return false;
            case 'T':
                if(hand2[i] == 'A' || hand2[i] == 'K' || hand2[i] == 'Q' || hand2[i] == 'J')
                    return true;
                else
                    return false;
            default:
                return hand1[i] < hand2[i];
        }
    }
}


struct ranker
{
    inline bool operator() (const pair& pair1, const pair& pair2)
    {
        Hand hand1 = pair1.first;
        Hand hand2 = pair2.first;
        if(getStrength(hand1) == getStrength(hand2)) {
            return stringRanker(hand1,hand2);
        } else {
            return getStrength(hand1) < getStrength(hand2);
        }
    }
};


int main() {
    std::string inputName = "../../Day7/Day7.txt";
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

    std::vector<pair> hands(0);

    for(std::size_t i = 0; i < input.size(); i++) {
        pair onePair = intParser(input[i]);
        hands.push_back(onePair);
    }

    std::sort(hands.begin(),hands.end(),ranker());

    unsigned long long winnings = 0;

    for(std::size_t i = 0; i < hands.size(); i++) {
        winnings += (unsigned long long) (i + 1) * (unsigned long long) hands[i].second;
    }

    assert(winnings == 249638405);
    std::cout << winnings << std::endl;

}
