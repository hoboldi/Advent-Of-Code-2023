#include <iostream>
#include <string>

int getDigits(std::string line) {
    std::string number = "";
    for(std::size_t i = 0; i < line.size(); i++) {
        if(isdigit(line.at(i))) {
            number.push_back(line.at(i));
            break;
        }
    }
    for(int i = line.size() - 1; i >= 0; i--) {
        if(isdigit(line.at(i))) {
            number.push_back(line.at(i));
            break;
        }
    }
    return stoi(number);
}


int main() {

    u_int64_t sum = 0;
    bool toRead = true;
    int lastNumber = 0;
    int i = 0;
    while(toRead) {
        sum += (u_int64_t) lastNumber;

        std::string line;
        std::cin >> line;

        if(line == "END") {
            break;
        }

        lastNumber = getDigits(line);
    }
    std::cout << sum;
}