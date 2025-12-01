#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

auto main(int argc, char **argv) -> int {
    const int DIAL_SIZE = 100;
    const int DIAL_START = 50;

    if (argc != 2) {
        std::cout << "usage: day1 INPUT_FILE" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    std::ifstream file(path);

    size_t password = 0;
    int position = DIAL_START;
    std::cout << "start: " << position << std::endl;

    std::string line;
    while (std::getline(file, line)) {
        int sign = 2 * (line[0] == 'R') - 1;
        int distance = atoi(line.substr(1).c_str());
        int rotation = sign * distance;
        int sum = position + rotation;
        password += abs(sum / DIAL_SIZE) + (sum <= 0) * (position != 0);
        position = (sum % DIAL_SIZE + DIAL_SIZE) % DIAL_SIZE;
        std::cout << rotation << " " << position << " " << password
                  << std::endl;
    }

    std::cout << "password: " << password << std::endl;
}
