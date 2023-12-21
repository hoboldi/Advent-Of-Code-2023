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

typedef std::pair<Direction, long long> Instruction;

Instruction stringToInstruction(std::string& line) {
  std::istringstream iss(line);
  Instruction digInstruction;

  std::string segment;
  std::getline(iss, segment, ' ');
  std::getline(iss, segment, ' ');
  std::getline(iss, segment, ' ');

  switch (segment[7]) {
  case '0':
    digInstruction.first = RIGHT;
    break;
  case '1':
    digInstruction.first = DOWN;
    break;
  case '2':
    digInstruction.first = LEFT;
    break;
  case '3':
    digInstruction.first = UP;
    break;
  }

  digInstruction.second =  stoll(segment.substr(2,5), nullptr, 16);

  return digInstruction;
}

long long solveInstructions(std::vector<std::string> input) {
  std::vector<Instruction> instructions(input.size());
  for(std::size_t i = 0; i < input.size(); i++) {
    instructions.at(i) = stringToInstruction(input.at(i));
  }

  long long area = 0;

  long long lastRow = 0, lastColumn = 0;

  for(const Instruction& instruction: instructions) {
    long long preRow = lastRow;
    long long preColumn = lastColumn;

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

  long long solution = solveInstructions(input);

  assert(solution == 52885384955882);
  std::cout << solution << std::endl;
}
