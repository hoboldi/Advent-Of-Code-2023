#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <stack>

enum Spring {
  Operational,
  Damaged,
  Unknown
};

enum Start {
  mustStart,
  mustnotStart,
  canStart
};

//With dynamic programming faster solution possible.
uint solveSpring(std::deque<Spring> springs, std::deque<uint> blueprint, Start start) {



}

uint solveLine(const std::string &line) {
  std::istringstream iss(line);
  std::vector<int> returnVector(0);

  std::string springline;
  std::getline(iss, springline, ' ');
  std::string blueprintString;
  std::getline(iss, blueprintString, ' ');

  std::deque<Spring> springs(0);

  for(std::size_t j = 0; j < 4; j++) {
    for(std::size_t i = 0; i < springline.size(); i++) {
      char c = springline.at(i);
      switch (c) {
      case '.':
        springs.push_back(Operational);
        break;
      case '#':
        springs.push_back(Damaged);
        break;
      case '?':
        springs.push_back(Unknown);
        break;
      }
    }
    springs.push_back(Unknown);
  }

  for(std::size_t i = 0; i < springline.size(); i++) {
    char c = springline.at(i);
    switch (c) {
    case '.':
      springs.push_back(Operational);
      break;
    case '#':
      springs.push_back(Damaged);
      break;
    case '?':
      springs.push_back(Unknown);
      break;
    }
  }

  std::string segment;
  std::deque<uint> blueprints(0);


  for(std::size_t i = 0; i < 5; i++) {
    std::stringstream blueprintStream(blueprintString);
    while(std::getline(blueprintStream, segment, ','))
    {
      blueprints.push_back(std::stoul(segment));
    }
  }

  return solveSpring(springs,blueprints, canStart);
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

  uint sum = 0;
  uint counter = 1;

  for(std::string line: input) {
    std::cout << counter++ << std::endl;
    sum += solveLine(line);
  }

  //assert(sum == 7090);
  std::cout << sum << std::endl;
}
