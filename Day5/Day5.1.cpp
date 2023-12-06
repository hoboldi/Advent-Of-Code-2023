#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
#include <compare>
#include <utility>
#include <limits>

std::vector<uint> intParser(const std::string& line) {

    std::istringstream iss(line);
    std::vector<uint> returnVector(0);

    std::string split;
    while (std::getline(iss, split, ' '))
    {
        if(split == "")
            continue;
        returnVector.push_back(stoul(split));
    }

    return returnVector;
}

typedef std::pair<uint, uint> pair;


struct Node {
    uint low, high;
    uint value;
    Node* left;
    Node* right;

    Node(uint low, uint high, uint val) : low(low), high(high), value(val), left(nullptr), right(nullptr) {}
};

class RangeBinaryTree {
private:
    Node* root;

    Node* insertHelper(Node* node, uint low, uint high, uint value) {
        if (node == nullptr) {
            return new Node(low, high, value);
        }

        if (low < node->low) {
            node->left = insertHelper(node->left, low, high, value);
        } else {
            node->right = insertHelper(node->right, low, high, value);
        }

        return node;
    }

    Node* searchHelper(Node* node, uint key) {
        if (node == nullptr || (node->low <= key && node->high >= key)) {
            return node;
        }

        if (node->low > key) {
            return searchHelper(node->left, key);
        } else {
            return searchHelper(node->right, key);
        }
    }

public:
    RangeBinaryTree() : root(nullptr) {}

    void insert(uint low, uint high, uint value) {
        root = insertHelper(root, low, high, value);
    }

    Node* search(uint key) {
        Node* node = searchHelper(root, key);
        if (node != nullptr) {
            return node;
        }
        return nullptr;
    }
};

int main() {
    std::vector <std::string> input(0);

    while (true) {
        std::string line;
        getline(std::cin, line);

        if (line == "END")
            break;

        input.push_back(line);
    }

    std::vector <uint> start;
    std::vector <uint> end = intParser(input[0].substr(7));;

    for(std::size_t i = 2; i < input.size(); i++) {

        while(input[i].find("map") != std::string::npos)
            i++;

        start = end;

        RangeBinaryTree rangeBinaryTree;
        while(!input[i].empty()) {
            std::vector<uint> parsedLine = intParser(input[i]);
            rangeBinaryTree.insert(parsedLine[1],parsedLine[1] + parsedLine[2] - 1,parsedLine[0]);
            i++;
        }

        end.resize(0);

        for(uint x: start) {
            Node* node = rangeBinaryTree.search(x);
            if(node == nullptr)
                end.push_back(x);
            else
                end.push_back(node->value + x - node->low);
        }
    }

    uint min = std::numeric_limits<uint>::max();
    for(std::size_t i = 0; i < end.size(); i++)
        min = min > end[i] ? end[i] : min;

    std::cout << min;
}
