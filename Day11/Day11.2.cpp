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
#include <queue>

enum Weight {
    One = 1,
    Million = 1000000
};


struct Vertex {
    uint x,y;
    int id;
    Weight w;
    uint distance;
    bool visited ;

    Vertex(uint x, uint y) {
        this->x = x;
        this->y = y;
        this->id = -1;
        this->w = One;
        this->visited = false;
    }

    Vertex(uint x, uint y, int id) {
        this->x = x;
        this->y = y;
        this->id = id;
        this->w = One;
        this->visited = false;
    }
};

typedef std::vector<std::vector<Vertex>> Universe;

void setDistanceMax(Universe& universe) {
    for(std::vector<Vertex>& line: universe) {
        for(Vertex& v: line) {
            v.visited = false;
        }
    }
}

std::vector<std::vector<uint>> distances;

void BFS(Universe& universe, uint x, uint y) {
    std::queue<std::pair<uint,uint>> queue;
    queue.push(std::make_pair(x,y));

    uint startid = universe.at(x).at(y).id;

    while(!queue.empty()) {
        std::pair<uint,uint> coords = queue.front();
        queue.pop();
        Vertex thisVertex = universe.at(coords.first).at(coords.second);


        if (thisVertex.id != -1 && thisVertex.id != startid) {
            distances.at(startid).at(thisVertex.id) = thisVertex.distance;
        }
        if (coords.first > 0 && !universe.at(coords.first - 1).at(coords.second).visited) {
            universe.at(coords.first - 1).at(coords.second).distance = thisVertex.distance + thisVertex.w;
            universe.at(coords.first - 1).at(coords.second).visited = true;
            queue.push(std::make_pair(coords.first - 1,coords.second));
        }

        if (coords.second > 0 && !universe.at(coords.first).at(coords.second - 1).visited) {
            universe.at(coords.first).at(coords.second - 1).distance = thisVertex.distance + thisVertex.w;
            universe.at(coords.first).at(coords.second - 1).visited = true;
            queue.push(std::make_pair(coords.first,coords.second - 1));
        }

        if (coords.first < universe.size() - 1 && !universe.at(coords.first + 1).at(coords.second).visited) {
            universe.at(coords.first + 1).at(coords.second).distance = thisVertex.distance + thisVertex.w;
            universe.at(coords.first + 1).at(coords.second).visited = true;
            queue.push(std::make_pair(coords.first + 1,coords.second));
        }

        if (coords.second < universe.at(0).size() - 1 && !universe.at(coords.first).at(coords.second + 1).visited) {
            universe.at(coords.first).at(coords.second + 1).distance = thisVertex.distance + thisVertex.w;
            universe.at(coords.first).at(coords.second + 1).visited = true;
            queue.push(std::make_pair(coords.first,coords.second + 1));
        }
    }
}


void getDistances(Universe universe) {
    for(size_t i = 0; i < universe.size(); i++) {
        for(size_t j = 0; j < universe.at(i).size(); j++) {
            Vertex& v = universe.at(i).at(j);
            if(v.id != -1) {
                setDistanceMax(universe);
                v.distance = 0;
                v.visited = true;
                BFS(universe,v.x,v.y);
            }
        }
    }
}

int main() {
    std::string inputName = "../../Day11/Day11.txt";
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

    uint nextId{0};

    Universe universe(input.size());
    for(size_t i = 0; i < input.size(); i++) {
        for(size_t j = 0; j < input.at(i).size(); j++) {
            if(input.at(i).at(j) == '#') {
                universe.at(i).emplace_back(i,j,nextId++);
            } else {
                universe.at(i).emplace_back(i,j);
            }
        }
    }

    for(size_t i = 0; i < universe.size(); i++) {
        bool allSpace = true;

        for(size_t j = 0; j < universe.at(i).size(); j++) {
            if(universe.at(i).at(j).id != -1) {
                allSpace = false;
            }
        }

        if(allSpace) {
            for (size_t j = 0; j < universe.at(i).size(); j++) {
                universe.at(i).at(j).w = Million;
            }
        }
    }

    uint galaxies = 0;

    for(size_t i = 0; i < universe.at(0).size(); i++) {
        bool allSpace = true;

        for(size_t j = 0; j < universe.size(); j++) {
            if(universe.at(j).at(i).id != -1) {
                allSpace = false;
                galaxies++;
            }
        }

        if(allSpace) {
            for (size_t j = 0; j < universe.size(); j++) {
                universe.at(j).at(i).w = Million;
            }
        }
    }

    std::vector<uint> d(galaxies);
    distances.resize(galaxies,d);
    getDistances(universe);

    unsigned long long sum = 0;
    for(std::vector<uint> line: distances) {
        for(uint x: line) {
            sum += x;
        }
    }
    sum /= 2;

    assert(sum == 550358864332);
    std::cout << sum << std::endl;
}
