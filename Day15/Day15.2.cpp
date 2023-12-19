#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>
#include <map>
#include <list>
#include <cassert>

typedef std::string Label;
typedef std::pair<Label,uint> Pair;
typedef std::list<Pair> Box;


uint hash(Label& text) {
  uint hash = 0;

  for(char c: text) {
    hash += c;
    hash *= 17;
    hash %= 256;
  }

  return hash;
}

bool boxContains(Box& box, Label& label) {
  for(Pair& p: box) {
    if(p.first == label) {
      return true;
    }
  }
  return false;
}

Pair& boxFind(Box& box, Label& label) {
  for(Pair& p: box) {
    if(p.first == label) {
      return p;
    }
  }
  throw std::invalid_argument("WHATS IN DA BOX?");
}

uint focusPower(Box& box, uint boxIndex) {
  uint index = 1;
  uint returnValue = 0;

  for(Pair& p: box) {
    returnValue += boxIndex * index++ * p.second;
  }

  return returnValue;
}

uint solveHashes(std::string& input) {
  std::stringstream inputStream(input);
  std::string segment;
  std::vector<std::string> hashes(0);


  while(std::getline(inputStream, segment, ','))
  {
    hashes.push_back(segment);
  }

  std::vector<Box> boxes(256);


  for(std::string& thisLen: hashes) {
    if(thisLen.contains('=')) {

      std::stringstream  lenStream(thisLen);

      std::getline(lenStream, segment, '=');
      Label label = segment;
      std::getline(lenStream, segment, '=');
      uint focal = std::stoul(segment);

      Box& box = boxes.at(hash(label));

      if(boxContains(box,label)) {
        Pair& p = boxFind(box,label);
        p.second = focal;
      } else {
        box.emplace_back(label,focal);
      }
    }

    if(thisLen.contains('-')) {
      std::stringstream  lenStream(thisLen);

      std::getline(lenStream, segment, '-');
      Label label = segment;

      Box& box = boxes.at(hash(label));

      if(boxContains(box,label)) {
        box.remove(boxFind(box,label));
      }
    }
  }

  uint sum = 0;
  uint index = 1;

  for(Box& box: boxes) {
    sum += focusPower(box,index++);
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

  assert(sum == 229349);
  std::cout << sum << std::endl;
}
