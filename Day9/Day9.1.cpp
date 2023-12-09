#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <map>
#include <stack>

std::vector<int> intParser(const std::string& line) {

    std::istringstream iss(line);
    std::vector<int> returnVector(0);

    std::string split;
    while (std::getline(iss, split, ' '))
    {
        if(split == "")
            continue;
        returnVector.push_back(stoi(split));
    }

    return returnVector;
}

int extrapolation(std::vector<int> history) {
    std::vector<int> current = history;
    std::stack<int> lasts;
    bool notZeros = true;

    while(notZeros) {
        lasts.push(current[current.size() - 1]);

        notZeros = false;
        for(std::size_t i = 0; i < current.size() - 1; i++) {
            current[i] = current[i + 1] - current[i];
            if(current[i] != 0)
                notZeros = true;
        }
        current.pop_back();
    }
    int newNumber = 0;

    while(!lasts.empty()) {
        newNumber = newNumber + lasts.top();
        lasts.pop();
    }
    return newNumber;
}


int main() {
    std::string inputName = "../../Day9/Day9.txt";
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

    std::vector<std::vector<int>> history(input.size());

    for(size_t i = 0; i < input.size(); i++) {
        history[i] = intParser(input[i]);
    }

    int sum = 0;

    for(size_t i = 0; i < history.size(); i++) {
        sum += extrapolation(history[i]);
    }


    std::cout << sum << std::endl;
}
