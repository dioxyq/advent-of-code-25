#include <fstream>
#include <iostream>
#include <set>
#include <string>

auto main(int argc, char **argv) -> int {
    if (argc != 2) {
        std::cout << "usage: part1 INPUT_FILE" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    std::ifstream file(path);

    size_t result = 0;
    std::set<std::size_t> positions{};

    std::string line;

    std::getline(file, line);
    positions.insert(line.find('S'));

    while (std::getline(file, line)) {
        std::set<size_t> to_erase{};
        for (const auto pos : positions) {
            if (line[pos] == '^') {
                ++result;
                if (pos > 0) {
                    positions.insert(pos - 1);
                }
                if (pos < line.length() - 1) {
                    positions.insert(pos + 1);
                }
                to_erase.insert(pos);
            }
        }
        for (const auto pos : to_erase) {
            positions.erase(pos);
        }
    }

    std::cout << result << std::endl;
}
