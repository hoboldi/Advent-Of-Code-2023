#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>
#include <algorithm>
#include <cassert>

enum Element {
  RoundRock = 0,
  Space = 1,
  CubeRock = 2
};

typedef std::vector<std::vector<Element>> Map;

//sort not necessary could be done in linear time for example with two pointer approach
uint tiltNorth (Map& map) {
  uint result = 0;

  for(std::size_t i = 0; i < map.size(); i++)
  {
    uint last = 0;
    for(std::size_t j = 0; j < map[i].size(); j++) {
      if(map[i][j] == CubeRock) {
        std::sort(map[i].begin() + last,map[i].begin() + (uint) j);
        last = j + 1;
      }
    }

    std::sort(map[i].begin() + last,map[i].end());

    for(std::size_t j = 0; j < map[i].size(); j++) {
      if(map[i][j] == RoundRock)
        result += map[i].size() - j;
    }
  }

  return result;
}



int main() {
  std::string inputName = "../../Day14/Day14.txt";
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

  Map map(input[0].size());
  for(std::vector<Element>& line: map ) {
    line.resize(input.size());
  }

  for(std::size_t i = 0; i < input.size(); i++) {
    for(std::size_t j = 0; j < input[0].size(); j++) {

      switch (input[i][j]) {
      case '.':
        map[j][i] = Space;
        break;
      case '#':
        map[j][i] = CubeRock;
        break;
      case 'O':
        map[j][i] = RoundRock;
        break;
      }

    }
  }

  uint result = tiltNorth(map);




  assert(result == 110407);
  std::cout << result << std::endl;
}
