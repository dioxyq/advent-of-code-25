#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

auto main(int argc, char **argv) -> int {
    if (argc != 2) {
        std::cout << "usage: part1 INPUT_FILE" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    std::ifstream file(path);

    size_t password = 0;
    int position = 50;
    std::cout << "start: " << position << std::endl;

    std::string line;
    while (std::getline(file, line)) {
        int sign = 2 * (line[0] == 'R') - 1;
        int distance = atoi(line.substr(1).c_str());
        int rotation = sign * distance;
        position = (position + rotation + 100) % 100;
        password += !position;
        std::cout << rotation << " " << position << std::endl;
    }

    std::cout << "password: " << password << std::endl;
}
