#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <map>

typedef std::pair<uint,uint> uintPair;
typedef std::pair<std::string, std::string> stringPair;
uint nextId = 0;
std::map<std::string,uint> nameToId;
std::map<uint,std::string> idToName;


struct Node {
    uint id;
    std::string name;
    uintPair idNext;
    stringPair nameNext;
};

Node lineToNode(std::string &line) {
    Node returnNode;
    returnNode.id = nextId++;
    returnNode.name = line.substr(0,3);
    returnNode.nameNext.first = line.substr(7,3);
    returnNode.nameNext.second = line.substr(12,3);
    nameToId.insert(std::make_pair(returnNode.name,returnNode.id));
    idToName.insert(std::make_pair(returnNode.id,returnNode.name));

    return returnNode;
}

int main() {
    std::string inputName = "../../Day8/Day8.txt";
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

    std::vector<Node> network(0);

    for(std::size_t i = 2; i < input.size(); i++) {
        network.push_back(lineToNode(input[i]));
    }

    for(auto & i : network) {
        i.idNext = std::make_pair(nameToId.find(i.nameNext.first)->second,nameToId.find(i.nameNext.second)->second);
    }

    uint current = nameToId.find("AAA")->second;
    uint last = nameToId.find("ZZZ")->second;
    uint allSteps = 0;
    uint step = 0;
    std::string instructions = input[0];


    while(current != last) {
        std::cout << network[current].name << std::endl;
        allSteps++;
        if(instructions[step] == 'L') {
            current = network[network[current].idNext.first].id;
        } else {
            current = network[network[current].idNext.second].id;
        }

        step = step + 1 >= instructions.size() ? step = 0 : step + 1;
    }
    std::cout << network[current].name << std::endl;

    std::cout << allSteps << std::endl;
}
