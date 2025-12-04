#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

inline auto ctoi(char c) -> int { return c - '0'; }

auto main(int argc, char **argv) -> int {
    if (argc != 2) {
        std::cout << "usage: part1 INPUT_FILE" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    std::ifstream file(path);

    size_t total_joltage = 0;

    std::string line;
    while (std::getline(file, line)) {
        auto max_1 = 0;
        auto max_i_1 = 0;
        for (auto i = 0; i < line.length() - 1; ++i) {
            auto d = ctoi(line[i]);
            if (d > max_1) {
                max_i_1 = i;
                max_1 = d;
            }
        }

        auto max_2 = 0;
        for (auto i = max_i_1 + 1; i < line.length(); ++i) {
            auto d = ctoi(line[i]);
            if (d > max_2) {
                max_2 = d;
            }
        }

        auto joltage = max_1 * 10 + max_2;
        std::cout << joltage << std::endl;

        total_joltage += joltage;
    }

    std::cout << "total joltage: " << total_joltage << std::endl;
}
