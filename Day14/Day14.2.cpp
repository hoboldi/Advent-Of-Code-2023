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

void rotateMatrix(Map &matrix) {
  if (matrix.empty() || matrix.size() != matrix[0].size()) {
    std::cout << "Invalid matrix format!" << std::endl;
    return;
  }

  int n = matrix.size(); // Assuming square matrix

  // Create a new matrix to store the rotated elements
  Map rotatedMatrix(n, std::vector<Element>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      rotatedMatrix[j][n - 1 - i] = matrix[i][j];
    }
  }

  // Copy the rotated matrix back to the original matrix
  matrix = rotatedMatrix;
}

void printMatrix(const Map &matrix) {
  for (const auto &row : matrix) {
    for (const auto &element : row) {
      switch (element) {
      case 0:
        std::cout << "O";
        break;
      case 1:
        std::cout << ".";
        break;
      case 2:
        std::cout << "#";
        break;
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

//brute force :( could be improved with cycle detection
uint runCycle (Map map) {
  uint result = 0;

  rotateMatrix(map);
  rotateMatrix(map);

  for(std::size_t k = 0; k < 4 * 1000000000; k++) {

    std::cout << 4 * 1000000000 - k <<  std::endl;

    rotateMatrix(map);

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
    }
  }
  rotateMatrix(map);
  rotateMatrix(map);
  printMatrix(map);

  for(std::size_t i = 0; i < map.size(); i++)
  {
    for(std::size_t j = 0; j < map[i].size(); j++) {
      if(map[i][j] == RoundRock)
        result += map[j].size() - i;
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

  Map map(input.size());
  for(std::vector<Element>& line: map ) {
    line.resize(input[0].size());
  }

  for(std::size_t i = 0; i < input.size(); i++) {
    for(std::size_t j = 0; j < input[0].size(); j++) {
      switch (input[i][j]) {
      case '.':
        map[i][j] = Space;
        break;
      case '#':
        map[i][j] = CubeRock;
        break;
      case 'O':
        map[i][j] = RoundRock;
        break;
      }
    }
  }

  uint result = runCycle(map);




  //assert(result == 110407);
  std::cout << result << std::endl;
}
