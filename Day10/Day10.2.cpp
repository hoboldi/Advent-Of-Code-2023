#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <map>
#include <stack>


enum TileType {
    Northeast,
    Northsouth,
    Northwest,
    Southeast,
    Southwest,
    Eastwest,
    Ground,
    Start
};

enum Direction {
    North,
    South,
    East,
    West
};


TileType getTileType(char x) {
    switch (x) {
        case '|':
            return Northsouth;
        case 'L':
            return Northeast;
        case 'J':
            return Northwest;
        case '7':
            return Southwest;
        case 'F':
            return Southeast;
        case '-':
            return Eastwest;
        case '.':
            return Ground;
        case 'S':
            return Start;
    }
}

struct Coordinate {
    uint x, y;
};

struct Tile {
    Coordinate coordinate;
    TileType type;
};

std::vector<std::vector<Tile>> map;


bool Connectable (Tile last, Tile current) {
    switch (last.type) {
        case Northsouth:
            if(last.coordinate.x > current.coordinate.x && (current.type == Southeast || current.type == Southwest || current.type == Northsouth || current.type == Start))
                return true;

            if(last.coordinate.x < current.coordinate.x && (current.type == Northeast || current.type == Northsouth || current.type == Northwest || current.type == Start))
                return true;

            return false;
        case Northeast:
            if(last.coordinate.x > current.coordinate.x && (current.type == Southeast || current.type == Southwest || current.type == Northsouth || current.type == Start))
                return true;

            if(last.coordinate.y < current.coordinate.y && (current.type == Northwest || current.type == Eastwest || current.type == Southwest || current.type == Start))
                return true;

            return false;
        case Northwest:
            if(last.coordinate.x > current.coordinate.x && (current.type == Southeast || current.type == Southwest || current.type == Northsouth || current.type == Start))
                return true;

            if(last.coordinate.y > current.coordinate.y && (current.type == Northeast || current.type == Eastwest || current.type == Southeast || current.type == Start))
                return true;

            return false;
        case Southwest:
            if(last.coordinate.x < current.coordinate.x && (current.type == Northeast || current.type == Northsouth || current.type == Northwest || current.type == Start))
                return true;

            if(last.coordinate.y > current.coordinate.y && (current.type == Northeast || current.type == Eastwest || current.type == Southeast || current.type == Start))
                return true;

            return false;
        case Southeast:
            if(last.coordinate.x < current.coordinate.x && (current.type == Northeast || current.type == Northsouth || current.type == Northwest || current.type == Start))
                return true;

            if(last.coordinate.y < current.coordinate.y && (current.type == Northwest || current.type == Eastwest || current.type == Southwest || current.type == Start))
                return true;

            return false;
        case Eastwest:
            if(last.coordinate.y < current.coordinate.y && (current.type == Northwest || current.type == Eastwest || current.type == Southwest || current.type == Start))
                return true;

            if(last.coordinate.y > current.coordinate.y && (current.type == Northeast || current.type == Eastwest || current.type == Southeast || current.type == Start))
                return true;

            return false;
        case Ground:
            return false;
        case Start:
            if(last.coordinate.x > current.coordinate.x && (current.type == Southwest || current.type == Northsouth || current.type == Southeast))
                return true;

            if(last.coordinate.y < current.coordinate.y && (current.type == Northwest || current.type == Southwest || current.type == Eastwest))
                return true;

            if(last.coordinate.x < current.coordinate.x && (current.type == Northsouth || current.type == Northwest || current.type == Northeast))
                return true;

            if(last.coordinate.y > current.coordinate.y && (current.type == Northeast || current.type == Southeast || current.type == Eastwest))
                return true;

            return false;
    }
}

std::vector<Coordinate> search(Tile current, Direction direction) {
    std::vector<Coordinate> returnValue(0);
    switch (current.type) {
        case Northsouth:
            if(direction == North && current.coordinate.x > 0 &&
               Connectable(current, map.at(current.coordinate.x - 1).at(current.coordinate.y))) {
                returnValue = search(map.at(current.coordinate.x - 1).at(current.coordinate.y),North);
                returnValue.push_back(current.coordinate);
                return returnValue;
            }

            if(direction == South && current.coordinate.x < map.size() - 1 &&
               Connectable(current, map.at(current.coordinate.x + 1).at(current.coordinate.y))) {
                returnValue = search(map.at(current.coordinate.x + 1).at(current.coordinate.y),South);
                returnValue.push_back(current.coordinate);
                return returnValue;
            }


            return returnValue;

        case Northeast:
            if(direction == South && current.coordinate.y < map.at(0).size() - 1 &&
               Connectable(current, map.at(current.coordinate.x).at(current.coordinate.y + 1))) {
                returnValue = search(map.at(current.coordinate.x).at(current.coordinate.y + 1),East);
                returnValue.push_back(current.coordinate);
                return returnValue;
            }

            if(direction == West && current.coordinate.x > 0 &&
               Connectable(current, map.at(current.coordinate.x - 1).at(current.coordinate.y))) {
                returnValue =  search(map.at(current.coordinate.x - 1).at(current.coordinate.y),North);
                returnValue.push_back(current.coordinate);
                return returnValue;
            }

            return returnValue;

        case Northwest:
            if(direction == South && current.coordinate.y > 0 &&
               Connectable(current, map.at(current.coordinate.x).at(current.coordinate.y - 1))) {
                returnValue = search(map.at(current.coordinate.x).at(current.coordinate.y - 1),West);
                returnValue.push_back(current.coordinate);
                return returnValue;
            }

            if(direction == East && current.coordinate.x > 0 &&
               Connectable(current, map.at(current.coordinate.x - 1).at(current.coordinate.y))) {
                returnValue = search(map.at(current.coordinate.x - 1).at(current.coordinate.y),North);
                returnValue.push_back(current.coordinate);
                return returnValue;
            }

            return returnValue;

        case Southwest:
            if(direction == North && current.coordinate.y > 0 &&
               Connectable(current, map.at(current.coordinate.x).at(current.coordinate.y - 1))) {
                returnValue = search(map.at(current.coordinate.x).at(current.coordinate.y - 1),West);
                returnValue.push_back(current.coordinate);
                return returnValue;
            }

            if(direction == East && current.coordinate.x < map.size() - 1 &&
               Connectable(current, map.at(current.coordinate.x + 1).at(current.coordinate.y))) {
                returnValue =  search(map.at(current.coordinate.x + 1).at(current.coordinate.y),South);
                returnValue.push_back(current.coordinate);
                return  returnValue;
            }

            return returnValue;

        case Southeast:
            if(direction == North && current.coordinate.y < map.at(0).size() - 1 &&
               Connectable(current, map.at(current.coordinate.x).at(current.coordinate.y + 1))) {
                returnValue =  search(map.at(current.coordinate.x).at(current.coordinate.y + 1),East);
                returnValue.push_back(current.coordinate);
                return returnValue;
            }

            if(direction == West && current.coordinate.x < map.size() - 1 &&
               Connectable(current, map.at(current.coordinate.x + 1).at(current.coordinate.y))) {
                returnValue = search(map.at(current.coordinate.x + 1).at(current.coordinate.y),South);
                returnValue.push_back(current.coordinate);
                return returnValue;
            }

            return returnValue;

        case Eastwest:
            if(direction == East && current.coordinate.y > 0 &&
               Connectable(current, map.at(current.coordinate.x).at(current.coordinate.y + 1))) {
                returnValue = search(map.at(current.coordinate.x).at(current.coordinate.y + 1),East);
                returnValue.push_back(current.coordinate);
                return returnValue;
            }

            if(direction == West && current.coordinate.y < map.at(0).size() &&
               Connectable(current, map.at(current.coordinate.x).at(current.coordinate.y - 1))) {
                returnValue =  search(map.at(current.coordinate.x).at(current.coordinate.y - 1),West);
                returnValue.push_back(current.coordinate);
                return returnValue;
            }

            return returnValue;
        case Ground:
            return returnValue;
        case Start:
            returnValue.push_back(current.coordinate);
            return returnValue;
    }
}


int main() {
    std::string inputName = "../../Day10/Day10.txt";
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


    Coordinate startC{0,0};
    map.resize(input.size());
    for(std::size_t i = 0; i < input.size(); i++) {
        map.at(i).resize(input.at(i).size());
        for(std::size_t j = 0; j < input.at(i).size(); j++) {
            Tile t{0,0,Southwest};
            t.coordinate.x = i;
            t.coordinate.y = j;
            t.type = getTileType(input.at(i).at(j));
            map.at(i).at(j) = t;
            if(t.type == Start)
                startC = t.coordinate;
        }
    }

    uint steps = 0;
    std::vector<Coordinate> path;

    if(startC.x > 0 && Connectable(map.at(startC.x).at(startC.y),map.at(startC.x - 1).at(startC.y))) {
        auto newpath = search(map.at(startC.x - 1).at(startC.y),North);
        uint pre = steps;
        steps = std::max(steps,(uint)newpath.size());
        path = steps != pre ? newpath : path;
    }

    if(startC.y > 0 && Connectable(map.at(startC.x).at(startC.y),map.at(startC.x).at(startC.y - 1))) {
        auto newpath = search(map.at(startC.x).at(startC.y - 1),West);
        uint pre = steps;
        steps = std::max(steps,(uint)newpath.size());
        path = steps != pre ? newpath : path;
    }

    if(startC.x < map.size() - 1 && Connectable(map.at(startC.x).at(startC.y),map.at(startC.x + 1).at(startC.y))) {
        auto newpath = search(map.at(startC.x + 1).at(startC.y),South);
        uint pre = steps;
        steps = std::max(steps,(uint)newpath.size());
        path = steps != pre ? newpath : path;
    }

    if(startC.y < map.at(0).size() - 1 && Connectable(map.at(startC.x).at(startC.y),map.at(startC.x).at(startC.y + 1))) {
        auto newpath = search(map.at(startC.x).at(startC.y + 1),East);
        uint pre = steps;
        steps = std::max(steps,(uint)newpath.size());
        path = steps != pre ? newpath : path;
    }



    int sum = 0;
    for(std::size_t i = 0; i < path.size(); i++) {
        Coordinate n1 = path.at(i);
        Coordinate n2 = path.at((i+1) % path.size());
        int x1, y1;
        x1 = n1.x;
        y1 = n1.y;
        int x2, y2;
        x2 = n2.x;
        y2 = n2.y;
        sum +=  (x1 * y2 - y1 * x2);
    }
    int numberOfInsides = std::abs(sum/2) - (int) path.size()/2 + 1;

    assert(numberOfInsides == 325);
    std::cout << numberOfInsides  << std::endl;
}
