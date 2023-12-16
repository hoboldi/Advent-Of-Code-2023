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
#include <queue>

uint solveLine(const std::string &line) {
  std::istringstream iss(line);
  std::vector<int> returnVector(0);

  std::string springs;
  std::getline(iss, springs, ' ');
  std::string blueprint;
  std::getline(iss, blueprint, ' ');

  


}



int main() {
    std::string inputName = "../../Day12/Day12.txt";
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

    for(std::string line: input) {
      solveLine(line);
    }



}
