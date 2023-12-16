#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>
#include <algorithm>
#include <cassert>


enum Pattern {
  Ash,
  Rock
};

typedef std::vector<std::vector<Pattern>> Patterns;

bool checkEqualityOfVector(std::vector<Pattern>& a, std::vector<Pattern>& b) {
  if(a.size() != b.size())
    return false;

  for(std::size_t i = 0; i < a.size(); i++) {
    if(a[i] != b[i])
      return false;
  }
  return true;
}

bool checkOneOFFEqualityOfVector(std::vector<Pattern>& a, std::vector<Pattern>& b) {
  if(a.size() != b.size())
    return false;

  uint counter = 0;

  for(std::size_t i = 0; i < a.size(); i++) {
    if(a[i] != b[i])
      counter++;
    if(counter > 1)
      return false;
  }
  return counter == 1;
}


uint getColomns(Patterns p){
  int indexL;
  int indexR;

  for(std::size_t i = 1; i < p.size(); i++) {

    if(checkEqualityOfVector(p.at(i - 1),p.at(i))) {
      indexL = (int)i - 2;
      indexR = (int)i + 1;

      bool isReflection = false;
      bool notUsedChange = true;
      //start check
      while(indexL >= 0 && indexR < p.size()) {
        if(checkEqualityOfVector(p.at(indexL), p.at(indexR))) {
          indexL--;
          indexR++;
        } else {
          if(notUsedChange) {
            if(checkOneOFFEqualityOfVector(p.at(indexL), p.at(indexR))) {
              notUsedChange = false;
              isReflection = true;
              indexL--;
              indexR++;
            } else {
              isReflection = false;
              break;
            }

          } else {
            isReflection = false;
            break;
          }


        }
      }

      if(isReflection)
        return i;
    }

    if(checkOneOFFEqualityOfVector(p.at(i - 1), p.at(i))) {
      indexL = (int)i - 2;
      indexR = (int)i + 1;

      bool isReflection = true;
      //start check
      while(indexL >= 0 && indexR < p.size()) {
        if(checkEqualityOfVector(p.at(indexL), p.at(indexR))) {
          indexL--;
          indexR++;
        } else {
          isReflection = false;
          break;
        }
      }

      if(isReflection)
        return i;
    }
  }

  return 0;
}


uint solvePatterns(Patterns p) {
  uint returnValue;
  returnValue = 100 * getColomns(p);
  if(returnValue != 0)
    return returnValue;
  //rotate p
  Patterns newPattern(p[0].size());
  for(std::size_t i = 0; i < newPattern.size(); i++) {
    newPattern[i].resize(p.size());
  }

  for(std::size_t i = 0; i < p.size(); i++) {
    for(std::size_t j = 0; j < p[i].size(); j++) {
      newPattern[j][i] = p[i][j];
    }
  }

  returnValue += getColomns(newPattern);
  return returnValue;
}


int main() {
  std::string inputName = "../../Day13/Day13.txt";
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

  Patterns p(0);
  uint result = 0;

  for(std::size_t i = 0; i < input.size(); i++) {
    std::vector<Pattern> line(input.at(i).size());
    for(std::size_t j = 0; j < input.at(i).size(); j++) {
      line.at(j) = input.at(i).at(j) == '.' ? Ash : Rock;
    }

    if(input.at(i).size() == 0) {
      result += solvePatterns(p);
      p.resize(0);
    } else {
      p.push_back(line);
    }
  }
  result += solvePatterns(p);


  assert(result == 31974);
  std::cout << result << std::endl;
}
