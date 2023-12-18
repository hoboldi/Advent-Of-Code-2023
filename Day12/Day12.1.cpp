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

  if(springs.empty()) {
    return blueprint.empty() ? 1 : 0;
  }

  if(blueprint.empty()) {
    for(Spring s: springs) {
      if(s == Damaged) {
        return 0;
      }
    }
    return 1;
  }

  Spring startSpring = springs.front();
  springs.pop_front();
  uint startDamaged = blueprint.front();
  blueprint.pop_front();

  if(start == mustStart) {
    if(startSpring == Operational) {
      return 0;
    }

    if(startSpring == Damaged || startSpring == Unknown) {
      startDamaged--;

      if(startDamaged == 0) {
        return solveSpring(springs,blueprint,mustnotStart);
      } else {
        blueprint.push_front(startDamaged);
        return solveSpring(springs, blueprint, mustStart);
      }
    }
  }

  if(start == mustnotStart) {
    if(startSpring == Operational || startSpring == Unknown) {
      blueprint.push_front(startDamaged);
      return solveSpring(springs, blueprint, canStart);
    }

    if(startSpring == Damaged) {
      return 0;
    }
  }

  if(start == canStart) {
    if(startSpring == Operational) {
      blueprint.push_front(startDamaged);
      return solveSpring(springs, blueprint, canStart);
    }

    if(startSpring == Damaged) {
      startDamaged--;
      if(startDamaged == 0) {
        return solveSpring(springs, blueprint, mustnotStart);
      } else {
        blueprint.push_front(startDamaged);
        return solveSpring(springs, blueprint, mustStart);
      }
    }

    if(startSpring == Unknown) {
      uint versionDamaged;
      startDamaged--;
      if(startDamaged == 0) {
        versionDamaged = solveSpring(springs, blueprint, mustnotStart);
      } else {
        blueprint.push_front(startDamaged);
        versionDamaged = solveSpring(springs, blueprint, mustStart);
        blueprint.pop_front();

      }
      startDamaged++;
      blueprint.push_front(startDamaged);
      uint versionOperational = solveSpring(springs, blueprint, canStart);

      return versionDamaged + versionOperational;
    }

  }

}

uint solveLine(const std::string &line) {
  std::istringstream iss(line);
  std::vector<int> returnVector(0);

  std::string springline;
  std::getline(iss, springline, ' ');
  std::string blueprintString;
  std::getline(iss, blueprintString, ' ');

  std::deque<Spring> springs(0);

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

  std::stringstream blueprintStream(blueprintString);
  std::string segment;
  std::deque<uint> blueprints(0);


  while(std::getline(blueprintStream, segment, ','))
  {
    blueprints.push_back(std::stoul(segment));
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

    for(std::string line: input) {
      sum += solveLine(line);
    }

    assert(sum == 7090);
    std::cout << sum << std::endl;
}
