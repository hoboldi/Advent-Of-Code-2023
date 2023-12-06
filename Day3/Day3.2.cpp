#include <vector>
#include <iostream>
#include <string>
#include <variant>
#include <fstream>
#include <cassert>

struct digit {
    char digit;
};

struct point {};

struct symbol {};

int getNumber(std::vector<std::variant<digit,point,symbol>> line, int pos) {
    std::string number = "";
    int goLeft = pos;
    int goRight = pos;
    if(line[goLeft].index() != 0)
        return -1;

    while(line[goLeft].index() == 0) {
        number.insert(0,1,std::get<digit>(line[goLeft]).digit);
        goLeft--;
        if(goLeft < 0)
            break;
    }

    number = number.substr(0,number.size() - 1);

    while(line[goRight].index() == 0) {
        number.push_back(std::get<digit>(line[goRight]).digit);
        goRight++;
        if(goRight >= line.size())
            break;
    }
    if(number == "")
        return -1;
    return std::stoi(number);
}


int main() {
    std::string inputName = "../../Day3/Day3.txt";
    std::ifstream inputFile (inputName);
    if (!inputFile)
        throw std::runtime_error("Could not open file " + std::string(inputName));

    std::vector<std::string> input(0);

    while(true) {
        std::string line;
        getline(inputFile,line);
        input.push_back(line);

        if(inputFile.eof())
            break;
    }

    std::vector<std::vector<std::variant<digit,point,symbol>>> table(input.size());

    for(std::size_t i = 0; i < input.size(); i++) {
        for(std::size_t j = 0; j < input.at(i).size(); j++) {

            if(isdigit(input.at(i).at(j))) {
                digit d{input.at(i).at(j)};
                table.at(i).emplace_back(d);
                continue;
            }


            if(input.at(i).at(j) == '*') {
                symbol s;
                table.at(i).emplace_back(s);
                continue;
            }

            point p;
            table.at(i).emplace_back(p);
        }
    }


    uint sum = 0;

    for(std::size_t i = 0; i < table.size(); i++) {
        for(std::size_t j = 0; j < table.size(); j++) {
            if(table[i][j].index() == 2) {

                int topleft, toptop, topright, left, bottomleft, bottombottom, bottomright, right;

                if(i > 0 && j > 0) {
                    topleft = getNumber(table[i - 1], j - 1);
                }

                if(i > 0) {
                    toptop = getNumber(table[i - 1], j);
                }

                if(i > 0 && j < input.at(i).size() - 1) {
                    topright = getNumber(table[i - 1], j + 1);
                }

                if(j > 0) {
                    left = getNumber(table[i], j - 1);
                }

                if(j < input.at(j).size() - 1) {
                    right = getNumber(table[i], j + 1);
                }

                if(i < input.size() - 1 && j > 0) {
                    bottomleft = getNumber(table[i + 1], j - 1);
                }

                if(i < input.size() - 1) {
                    bottombottom = getNumber(table[i + 1], j);
                }

                if(i < input.size() - 1 && j < input.at(i).size() - 1) {
                    bottomright = getNumber(table[i + 1], j + 1);
                }

                std::vector<int>numbers(0);
                if(toptop != -1) {
                    numbers.push_back(toptop);
                } else {
                    if(topleft != -1) {
                        numbers.push_back(topleft);
                    }
                    if(topright != -1) {
                        numbers.push_back(topright);
                    }
                }

                if(left != -1) {
                    numbers.push_back(left);
                }

                if(right != -1) {
                    numbers.push_back(right);
                }

                if(bottombottom != -1) {
                    numbers.push_back(bottombottom);
                } else {
                    if(bottomleft != -1) {
                        numbers.push_back(bottomleft);
                    }
                    if(bottomright != -1) {
                        numbers.push_back(bottomright);
                    }
                }

                sum+= numbers.size() == 2 ? numbers[0] * numbers[1] : 0;
            }

        }
    }

    assert(sum == 73646890);
    std::cout << sum << std::endl;
}