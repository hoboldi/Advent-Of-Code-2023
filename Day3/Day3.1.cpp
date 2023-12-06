#include <vector>
#include <iostream>
#include <string>
#include <variant>
#include <fstream>

struct digit {
    char digit;
};

struct point {};

struct symbol {};


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
    std::vector<std::vector<bool>> isNearSymbol(input.size());

    for(std::size_t i = 0; i < input.size(); i++) {
        for(std::size_t j = 0; j < input.at(i).size(); j++) {
            isNearSymbol.at(i).emplace_back(false);

            if(isdigit(input.at(i).at(j))) {
                digit d{input.at(i).at(j)};
                table.at(i).emplace_back(d);
                continue;
            }

            if(input.at(i).at(j) == '.') {
                point p;
                table.at(i).emplace_back(p);
                continue;
            }

            symbol s;
            table.at(i).emplace_back(s);
        }
    }

    for(std::size_t i = 0; i < input.size(); i++) {
        for(std::size_t j = 0; j < input.at(i).size(); j++) {

            if(i > 0 && j > 0) {
                isNearSymbol[i][j] =
                        table[i - 1][j - 1].index() == 2 || isNearSymbol[i][j];
            }

            if(i > 0) {
                isNearSymbol[i][j] =
                        table[i - 1][j].index() == 2 || isNearSymbol[i][j];
            }

            if(i > 0 && j < input.at(i).size() - 1) {
                isNearSymbol[i][j] =
                        table[i - 1][j + 1].index() == 2 || isNearSymbol[i][j];
            }

            if(j > 0) {
                isNearSymbol[i][j] =
                        table[i][j - 1].index() == 2 || isNearSymbol[i][j];
            }

            if(j < input.at(j).size() - 1) {
                isNearSymbol[i][j] =
                        table[i][j + 1].index() == 2 || isNearSymbol[i][j];
            }

            if(i < input.size() - 1 && j > 0) {
                isNearSymbol[i][j] =
                        table[i + 1][j - 1].index() == 2 || isNearSymbol[i][j];
            }

            if(i < input.size() - 1) {
                isNearSymbol[i][j] =
                        table[i + 1][j].index() == 2 || isNearSymbol[i][j];
            }

            if(i < input.size() - 1 && j < input.at(i).size() - 1) {
                isNearSymbol[i][j] =
                        table[i + 1][j + 1].index() == 2 || isNearSymbol[i][j];
            }
        }


    }
    uint sum = 0;

    for(std::size_t i = 0; i < input.size(); i++) {

        std::string number = "";
        bool nearSymbol = false;

        for (std::size_t j = 0; j < input.at(i).size(); j++) {
            if(table[i][j].index() == 0) {
                number.push_back(std::get<digit>(table[i][j]).digit);
                nearSymbol = isNearSymbol[i][j] || nearSymbol;

                if(j == table.at(i).size() - 1 && nearSymbol) {
                    sum += stoi(number);
                    nearSymbol = false;
                    number = "";
                }

            } else {
                if(nearSymbol) {
                    sum += stoi(number);
                }
                nearSymbol = false;
                number = "";
            }
        }
    }

    std::cout << sum;
}