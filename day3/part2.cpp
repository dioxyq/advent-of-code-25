#include <cmath>
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
        const auto NUM_DIGITS = 12;
        size_t joltage = 0;

        auto max_idx = -1;
        for (auto i = NUM_DIGITS - 1; i >= 0; --i) {
            auto max = 0;
            for (auto j = max_idx + 1; j < line.length() - i; ++j) {
                auto d = ctoi(line[j]);
                if (d > max) {
                    max_idx = j;
                    max = d;
                }
            }
            joltage += max * pow(10, i);
        }

        std::cout << joltage << std::endl;
        total_joltage += joltage;
    }

    std::cout << "total joltage: " << total_joltage << std::endl;
}
