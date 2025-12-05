#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

auto main(int argc, char **argv) -> int {
    if (argc != 2) {
        std::cout << "usage: part1 INPUT_FILE" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    std::ifstream file(path);

    size_t result = 0;

    std::vector<std::pair<size_t, size_t>> ranges{};
    std::vector<size_t> ids{};

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            break;
        }
        auto mid = line.find('-');
        auto start = atol(line.substr(0, mid).c_str());
        auto end = atol(line.substr(mid + 1).c_str());
        ranges.emplace_back(std::pair(start, end));
    }

    while (std::getline(file, line)) {
        auto id = atol(line.c_str());
        ids.push_back(id);
    }

    for (const auto &id : ids) {
        for (const auto &[start, end] : ranges) {
            if (start <= id && id <= end) {
                ++result;
                break;
            }
        }
    }

    std::cout << result << std::endl;
}
