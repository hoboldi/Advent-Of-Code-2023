#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <cassert>

enum Direction {
  Up,
  Down,
  Left,
  Right
};

enum GridElement {
  EmptySpace, /* . */
  LeftMirror, /* / */
  RightMirror, /* \ */
  VerticalSplitter, /* | */
  HorizontalSplitter, /* - */
};

typedef std::vector<std::vector<GridElement>>Grid;
typedef std::vector<std::vector<bool>> EnergyGrid;
typedef std::pair<uint,uint> Coordinate;

EnergyGrid eGrid;

//slower but much more memory friendly would be with a map
std::vector<std::vector<std::vector<std::pair<Direction,bool>>>> DP;


void solveGrid(Grid& grid, Coordinate c, Direction d) {
  if(c.first >= grid.size() || c.second >= grid.at(0).size() || c.first < 0 || c.second < 0)
    return;

  GridElement element = grid.at(c.first).at(c.second);
  eGrid.at(c.first).at(c.second) = true;

  switch (d) {
  case Up:
    if(DP.at(c.first).at(c.second).at(0) == std::make_pair(Up, true))
      return;

    DP.at(c.first).at(c.second).at(0) = std::make_pair(Up, true);
    break;

  case Down:
    if(DP.at(c.first).at(c.second).at(1) == std::make_pair(Down, true))
      return;

    DP.at(c.first).at(c.second).at(1) = std::make_pair(Down, true);
    break;

  case Left:
    if(DP.at(c.first).at(c.second).at(2) == std::make_pair(Left, true))
      return;

    DP.at(c.first).at(c.second).at(2) = std::make_pair(Left, true);
    break;

  case Right:
    if(DP.at(c.first).at(c.second).at(3) == std::make_pair(Right, true))
      return;

    DP.at(c.first).at(c.second).at(3) = std::make_pair(Right, true);
    break;
  }

  if(d == Up) {
    switch (element) {
    case EmptySpace:
      solveGrid(grid,std::make_pair(c.first - 1, c.second), Up);
      return;
    case LeftMirror:
      solveGrid(grid,std::make_pair(c.first, c.second + 1), Right);
      return;
    case RightMirror:
      solveGrid(grid,std::make_pair(c.first, c.second - 1), Left);
      return;
    case VerticalSplitter:
      solveGrid(grid,std::make_pair(c.first - 1, c.second), Up);
      return;
    case HorizontalSplitter:
      solveGrid(grid,std::make_pair(c.first, c.second - 1), Left);
      solveGrid(grid,std::make_pair(c.first, c.second + 1), Right);
      return;
    }
  }

  if(d == Down) {
    switch (element) {
    case EmptySpace:
      solveGrid(grid,std::make_pair(c.first + 1, c.second), Down);
      return;
    case LeftMirror:
      solveGrid(grid,std::make_pair(c.first, c.second - 1), Left);
      return;
    case RightMirror:
      solveGrid(grid,std::make_pair(c.first, c.second + 1), Right);
      return;
    case VerticalSplitter:
      solveGrid(grid,std::make_pair(c.first + 1, c.second), Down);
      return;
    case HorizontalSplitter:
      solveGrid(grid,std::make_pair(c.first, c.second - 1), Left);
      solveGrid(grid,std::make_pair(c.first, c.second + 1), Right);
      return;
    }
  }

  if(d == Left) {
    switch (element) {
    case EmptySpace:
      solveGrid(grid,std::make_pair(c.first, c.second - 1), Left);
      return;
    case LeftMirror:
      solveGrid(grid,std::make_pair(c.first + 1, c.second), Down);
      return;
    case RightMirror:
      solveGrid(grid,std::make_pair(c.first - 1, c.second), Up);
      return;
    case VerticalSplitter:
      solveGrid(grid,std::make_pair(c.first - 1, c.second), Up);
      solveGrid(grid,std::make_pair(c.first + 1, c.second), Down);
      return;
    case HorizontalSplitter:
      solveGrid(grid,std::make_pair(c.first, c.second - 1), Left);
      return;
    }
  }

  if(d == Right) {
    switch (element) {
    case EmptySpace:
      solveGrid(grid,std::make_pair(c.first, c.second + 1), Right);
      return;
    case LeftMirror:
      solveGrid(grid,std::make_pair(c.first - 1, c.second), Up);
      return;
    case RightMirror:
      solveGrid(grid,std::make_pair(c.first + 1, c.second), Down);
      return;
    case VerticalSplitter:
      solveGrid(grid,std::make_pair(c.first - 1, c.second), Up);
      solveGrid(grid,std::make_pair(c.first + 1, c.second), Down);
      return;
    case HorizontalSplitter:
      solveGrid(grid,std::make_pair(c.first, c.second + 1), Right);
      return;
    }
  }
}


int main() {
    std::string inputName = "../../Day16/Day16.txt";
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

    Grid grid(input.size());

    for(std::size_t i = 0; i < input.size(); i++) {
      grid.at(i).resize(input.at(0).size());

      for(std::size_t j = 0; j < input.at(0).size(); j++) {
        char c = input.at(i).at(j);

        switch (c) {
        case '.':
          grid.at(i).at(j) = EmptySpace;
          break;
        case '/':
          grid.at(i).at(j) = LeftMirror;
          break;
        case '\\':
          grid.at(i).at(j) = RightMirror;
          break;
        case '|':
          grid.at(i).at(j) = VerticalSplitter;
          break;
        case '-':
          grid.at(i).at(j) = HorizontalSplitter;
          break;
        }
      }
    }

    eGrid.resize(grid.size());
    DP.resize(grid.size());
    for(std::size_t i = 0; i < grid.size(); i++) {
      eGrid.at(i).resize(grid.at(i).size(), false);
      std::vector<std::pair<Direction,bool>> dp = {std::make_pair(Up,false),std::make_pair(Down,false),std::make_pair(Left,false),std::make_pair(Right,false)};
      DP.at(i).resize(grid.at(i).size(), dp);
    }

    solveGrid(grid,std::make_pair(0,0),Right);

    uint sum = 0;

    for(std::vector<bool> line: eGrid) {
      for(bool b: line) {
        sum += b;
      }
    }

    assert(sum == 8034);
    std::cout << sum << std::endl;
}
