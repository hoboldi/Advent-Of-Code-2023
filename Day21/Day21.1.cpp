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
  bool operator()(const Tile* a,const Tile* b){
    return a->distance > b->distance;
  }
};



typedef std::vector<std::vector<Tile>> Garden;
uint startRow;
uint startColumn;

Garden parse(std::vector<std::string>& input) {
  uint r = 0;
  uint c = 0;

  Garden garden(input.size());

  for(std::string& line: input) {
    garden.at(r).resize(input.at(r).size());
    for(char character: line) {
      Tile tile;
      tile.row = r;
      tile.column = c;

      switch (character) {
      case '.':
        tile.gardenTile = Plot;
        break;
      case '#':
        tile.gardenTile = Rock;
        break;
      case 'S':
        tile.gardenTile = Plot;
        startRow = r;
        startColumn = c;
        break;
      default:
        throw std::invalid_argument("Wrong input!");
      }

      garden.at(r).at(c) = tile;
      c++;
    }
    r++;
    c = 0;
  }

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
      if(currentTile->distance > 64)
        break;

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

uint count(Garden& garden) {
  uint number = 0;
  for(std::vector<Tile>& row: garden) {
    for(Tile& t: row) {
      if(t.distance <= 64 && t.distance % 2 == 0) {
        number++;
      }
    }
  }
  return number;
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
    Garden garden = parse(input);
    dijkstra(garden);
    uint solution = count(garden);

    assert(solution == 3649);
    std::cout << solution << std::endl;
}
