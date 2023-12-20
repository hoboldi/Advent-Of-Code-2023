#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <limits.h>

enum Direction {
  UP,
  DOWN,
  LEFT,
  RIGHT
};

typedef std::pair<Direction, uint> Instruction;

Instruction stringToInstruction(std::string& line) {
  std::istringstream iss(line);
  Instruction digInstruction;

  std::string segment;
  std::getline(iss, segment, ' ');

  switch (segment[0]) {
  case 'U':
    digInstruction.first = UP;
    break;
  case 'D':
    digInstruction.first = DOWN;
    break;
  case 'L':
    digInstruction.first = LEFT;
    break;
  case 'R':
    digInstruction.first = RIGHT;
  }

  std::getline(iss, segment, ' ');

  digInstruction.second = stoul(segment);

  return digInstruction;
}

uint solveInstructions(std::vector<std::string> input) {
  std::vector<Instruction> instructions(input.size());
  for(std::size_t i = 0; i < input.size(); i++) {
    instructions.at(i) = stringToInstruction(input.at(i));
  }

  int area = 0;

  int lastRow = 0, lastColumn = 0;

  for(const Instruction& instruction: instructions) {
    int preRow = lastRow;
    int preColumn = lastColumn;

    switch (instruction.first) {
    case UP:
      lastRow -= instruction.second;
      break;
    case DOWN:
      lastRow += instruction.second;
      break;
    case LEFT:
      lastColumn -= instruction.second;
      break;
    case RIGHT:
      lastColumn += instruction.second;
      break;
    }

    area += (preRow + lastRow) * (preColumn - lastColumn);
    area += instruction.second;
  }

  return std::abs(area/2) + 1;
}






int main() {
    std::string inputName = "../../Day18/Day18.txt";
    std::ifstream inputFile (inputName);
    if (!inputFile)
        throw std::runtime_error("Could not open file " + std::string(inputName));

    std::vector<std::string> input(0);

    while (true) {
        std::string line;
        getline(inputFile, line);
        input.push_back(line);

        if(inputFile.eof())
            break;
    }

    uint solution = solveInstructions(input);

    assert(solution == 49578);
    std::cout << solution << std::endl;
}
