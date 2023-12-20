#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <cassert>
#include <queue>

struct Node {
  uint distance = std::numeric_limits<uint>::max()/2;
  uint weight;
  uint x;
  uint y;
  Node* last = nullptr;
};

enum Direction {
  Up,
  Down,
  Left,
  Right
};

enum Counter {
  Null = 0,
  One = 1,
  Two = 2,
  Three = 3
};

struct State {
  uint distance;
  int x;
  int y;
  Direction direction;
  Counter counter;
};

class Compare {
public:
  bool operator()(State a, State b){
    return a.distance < b.distance;
  }
};

std::vector<std::vector<Node>> nodes;

Node* getUpNode(int x, int y) {
  if(x >= 1) {
    return &(nodes.at(x - 1).at(y));
  }
  return nullptr;
}

Node* getDownNode(int x, int y) {
  if(x < nodes.size() - 1) {
    return &(nodes.at(x + 1).at(y));
  }
  return nullptr;
}

Node* getLeftNode(int x, int y) {
  if(y >= 1) {
    return &(nodes.at(x).at(y- 1));
  }
  return nullptr;
}

Node* getRightNode(int x, int y) {
  if(y < nodes.at(0).size() - 1) {
    return &(nodes.at(x).at(y + 1));
  }
  return nullptr;
}

void solveNodes() {

}



int main() {
    std::string inputName = "../../Day17/Day17.txt";
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

    nodes.resize(input.size());

    for(std::size_t i = 0; i < input.size(); i++) {
      nodes.at(i).resize(input.at(i).size());
      for(std::size_t j = 0; j < nodes.at(i).size(); j++) {
        char c = input.at(i).at(j);
        nodes.at(i).at(j).weight = (uint)c - (uint)'0';
      }
    }

    solveNodes();

    uint solution = nodes.at(nodes.size() - 1).at(nodes.at(0).size() - 1).distance;

    auto thisNode = &(nodes.at(nodes.size() - 1).at(nodes.at(0).size() - 1));

    while(thisNode->last != nullptr) {
      std::cout << thisNode->distance << std::endl;
      thisNode = thisNode->last;
    }


    //assert(sum == 8034);
    std::cout << solution << std::endl;
}
