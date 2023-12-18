#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>
#include <algorithm>
#include <cassert>

uint hash(std::string text) {
  uint hash = 0;

  for(char c: text) {
    hash += c;
    hash *= 17;
    hash %= 256;
  }

  return hash;
}

uint solveHashes(std::string input) {
  std::stringstream inputStream(input);
  std::string segment;
  std::vector<std::string> hashes(0);


  while(std::getline(inputStream, segment, ','))
  {
    hashes.push_back(segment);
  }

  uint sum = 0;

  for(std::string thisHash: hashes) {
    sum += hash(thisHash);
  }

  return sum;
}


int main() {
  std::string inputName = "../../Day15/Day15.txt";
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

  uint sum = solveHashes(input.at(0));




  std::cout << sum << std::endl;
}
