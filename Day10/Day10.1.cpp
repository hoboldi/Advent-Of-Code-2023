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

uint search(Tile current, Direction direction) {
    switch (current.type) {
        case Northsouth:
            if(direction == North && current.coordinate.x > 0 &&
               Connectable(current, map.at(current.coordinate.x - 1).at(current.coordinate.y))) {
                return search(map.at(current.coordinate.x - 1).at(current.coordinate.y),North) + 1;
            }

            if(direction == South && current.coordinate.x < map.size() - 1 &&
               Connectable(current, map.at(current.coordinate.x + 1).at(current.coordinate.y))) {
                return search(map.at(current.coordinate.x + 1).at(current.coordinate.y),South) + 1;
            }

            return std::numeric_limits<uint>::min();

        case Northeast:
            if(direction == South && current.coordinate.y < map.at(0).size() - 1 &&
               Connectable(current, map.at(current.coordinate.x).at(current.coordinate.y + 1))) {
                return search(map.at(current.coordinate.x).at(current.coordinate.y + 1),East) + 1;
            }

            if(direction == West && current.coordinate.x > 0 &&
               Connectable(current, map.at(current.coordinate.x - 1).at(current.coordinate.y))) {
                return search(map.at(current.coordinate.x - 1).at(current.coordinate.y),North) + 1;
            }

            return std::numeric_limits<uint>::min();

        case Northwest:
            if(direction == South && current.coordinate.y > 0 &&
               Connectable(current, map.at(current.coordinate.x).at(current.coordinate.y - 1))) {
                return search(map.at(current.coordinate.x).at(current.coordinate.y - 1),West) + 1;
            }

            if(direction == East && current.coordinate.x > 0 &&
               Connectable(current, map.at(current.coordinate.x - 1).at(current.coordinate.y))) {
                return search(map.at(current.coordinate.x - 1).at(current.coordinate.y),North) + 1;
            }

            return std::numeric_limits<uint>::min();

        case Southwest:
            if(direction == North && current.coordinate.y > 0 &&
               Connectable(current, map.at(current.coordinate.x).at(current.coordinate.y - 1))) {
                return search(map.at(current.coordinate.x).at(current.coordinate.y - 1),West) + 1;
            }

            if(direction == East && current.coordinate.x < map.size() - 1 &&
               Connectable(current, map.at(current.coordinate.x + 1).at(current.coordinate.y))) {
                return search(map.at(current.coordinate.x + 1).at(current.coordinate.y),South) + 1;
            }

            return std::numeric_limits<uint>::min();

        case Southeast:
            if(direction == North && current.coordinate.y < map.at(0).size() - 1 &&
               Connectable(current, map.at(current.coordinate.x).at(current.coordinate.y + 1))) {
                return search(map.at(current.coordinate.x).at(current.coordinate.y + 1),East) + 1;
            }

            if(direction == West && current.coordinate.x < map.size() - 1 &&
               Connectable(current, map.at(current.coordinate.x + 1).at(current.coordinate.y))) {
                return search(map.at(current.coordinate.x + 1).at(current.coordinate.y),South) + 1;
            }

            return std::numeric_limits<uint>::min();

        case Eastwest:
            if(direction == East && current.coordinate.y > 0 &&
               Connectable(current, map.at(current.coordinate.x).at(current.coordinate.y + 1))) {
                return search(map.at(current.coordinate.x).at(current.coordinate.y + 1),East) + 1;
            }

            if(direction == West && current.coordinate.y < map.at(0).size() &&
               Connectable(current, map.at(current.coordinate.x).at(current.coordinate.y - 1))) {
                return search(map.at(current.coordinate.x).at(current.coordinate.y - 1),West) + 1;
            }

            return std::numeric_limits<uint>::min();
        case Ground:
            return std::numeric_limits<uint>::min();
        case Start:
            return 1;
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



    if(startC.x > 0 && Connectable(map.at(startC.x).at(startC.y),map.at(startC.x - 1).at(startC.y))) {
        steps = std::max(steps,search(map.at(startC.x - 1).at(startC.y),North));
    }

    if(startC.y > 0 && Connectable(map.at(startC.x).at(startC.y),map.at(startC.x).at(startC.y - 1))) {
        steps = std::max(steps,search(map.at(startC.x).at(startC.y - 1),West));
    }

    if(startC.x < map.size() - 1 && Connectable(map.at(startC.x).at(startC.y),map.at(startC.x + 1).at(startC.y))) {
        steps = std::max(steps,search(map.at(startC.x + 1).at(startC.y),South));
    }

    if(startC.y < map.at(0).size() - 1 && Connectable(map.at(startC.x).at(startC.y),map.at(startC.x).at(startC.y + 1))) {
        steps = std::max(steps,search(map.at(startC.x).at(startC.y + 1),East));
    }


    steps /= 2;
    assert(steps == 6846);
    std::cout << steps << std::endl;
}
