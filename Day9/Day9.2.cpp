#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <map>
#include <numeric>

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
    std::string inputName = "../../Day9/Day9.txt";
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

    std::vector<uint> currents;
    for(size_t i = 0; i < network.size(); i++) {
        if(network[i].name[2] == 'A') {
            currents.push_back(network[i].id);
        }
    }

    std::vector<uint> allSteps(currents.size());
    std::vector<uint> steps(currents.size());
    std::string instructions = input[0];

    for(size_t i = 0; i < currents.size(); i++) {
        while (network[currents[i]].name[2] != 'Z') {
            allSteps[i]++;
            if(instructions[steps[i]] == 'L') {
                currents[i] = network[network[currents[i]].idNext.first].id;
            } else {
                currents[i] = network[network[currents[i]].idNext.second].id;
            }
            steps[i] = steps[i] + 1 >= instructions.size() ? steps[i] = 0 : steps[i] + 1;
        }
    }

    unsigned long long result = 1;
    for(std::size_t i = 0; i < allSteps.size(); i++) {
        result = std::lcm(result,(unsigned long long) allSteps[i]);
    }

    assert(result == 10151663816849);
    std::cout << result << std::endl;
}