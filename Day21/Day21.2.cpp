#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <queue>

enum GardenTile {
  Rock,
  Plot
};

struct Tile {
  GardenTile gardenTile;
  uint distance = std::numeric_limits<uint>::max()/2;
  uint row;
  uint column;
};

class Compare {
public:
  bool operator()(Tile* a, Tile* b){
    return a->distance > b->distance;
  }
};



typedef std::vector<std::vector<Tile>> Garden;
uint startRow;
uint startColumn;

Garden parse(std::vector<std::string>& input, uint num) {
  Garden garden(input.size() * num);

  for(std::size_t i = 0; i < input.size() * num; i++) {
    garden.at(i).resize(input.at(0).size() * num);

    for(std::size_t j = 0; j < input.at(0).size() * num; j++) {
      uint indexi = i % input.size();
      uint indexj = j % input.at(0).size();
      char character = input.at(indexi).at(indexj);

      Tile tile;
      tile.row = i;
      tile.column = j;

      switch (character) {
      case '.':
        tile.gardenTile = Plot;
        break;
      case '#':
        tile.gardenTile = Rock;
        break;
      case 'S':
        tile.gardenTile = Plot;
        startRow = i;
        startColumn = j;
        break;
      default:
        throw std::invalid_argument("Wrong input!");
      }

      garden.at(i).at(j) = tile;
    }
  }
  startRow -= ((num - 1) / 2) * 131;
  startColumn -= ((num - 1 ) / 2) * 131;

  return garden;
}

std::vector<Tile*> getNeighbours(Garden& garden, uint row, uint column) {
  std::vector<Tile*> returnVector(0);
  if(row > 0) {
    returnVector.push_back(&(garden.at(row - 1).at(column)));
  }

  if(row < garden.size() - 1) {
    returnVector.push_back(&(garden.at(row + 1).at(column)));
  }

  if(column > 0) {
    returnVector.push_back((&(garden.at(row).at(column - 1))));
  }

  if(column < garden.at(0).size() - 1) {
    returnVector.push_back(&(garden.at(row).at(column + 1)));
  }

  return returnVector;
}

void dijkstra(Garden& garden) {
  std::priority_queue<Tile*,std::vector<Tile*>,Compare> queue;
  Tile* startTile = &(garden[startRow][startColumn]);
  startTile->distance = 0;
  queue.push(startTile);

  while(!queue.empty()) {
    Tile* currentTile = queue.top();

    queue.pop();

    auto neighbours = getNeighbours(garden, currentTile->row, currentTile->column);

    for(Tile* t: neighbours) {
      if(t->distance > currentTile->distance + 1 && t->gardenTile == Plot) {
        queue.push(t);
        t->distance = currentTile->distance + 1;
      }
    }

  }
}

unsigned long long count(Garden& garden, unsigned long long num) {
  unsigned long long number = 0;
  for(std::vector<Tile>& row: garden) {
    for(Tile t: row) {
      if(t.distance <= num && t.distance % 2 == 1) {
        std::cout << "O";
        number++;
      } else {
        std::cout << ".";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  return number;
}

unsigned long long polynomialFit(unsigned long long x1, unsigned long long y1, unsigned long long x2, unsigned long long y2, unsigned long long x3, unsigned long long y3, unsigned long long x) {
  return y1
         +(y2 - y1) / (x2 - x1) * (x - x1)
         +((y3 - y2) / ((x3 - x2) * (x3 - x1)) - (y2 - y1) / ((x2 - x1) * (x3 - x1))) * (x - x1) * (x - x2);
}

unsigned long long solve(unsigned long long size, std::vector<std::string> input) {
  Garden garden;
  unsigned long long steps = 26501365;
  garden = parse(input, 1);
  dijkstra(garden);
  unsigned long long y1 = count(garden, size / 2);
  garden = parse(input, 3);
  dijkstra(garden);
  unsigned long long y2 = count(garden, (size / 2) + size);
  garden = parse(input, 5);
  dijkstra(garden);
  unsigned long long y3 = count(garden, size / 2 + 2 * size);
  return polynomialFit(0, y1, 1, y2, 2, y3, (steps - (size / 2)) / size);
}


int main() {
  std::string inputName = "../../Day21/Day21.txt";
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

  unsigned long long solution = solve(input.size(), input);

  //assert(solution == 331208);
  std::cout << solution << std::endl;
}
