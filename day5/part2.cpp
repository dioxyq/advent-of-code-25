#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <set>
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

    std::set<std::pair<size_t, size_t>> ranges{};
    std::vector<size_t> ids{};

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            break;
        }
        auto mid = line.find('-');
        auto start = atol(line.substr(0, mid).c_str());
        auto end = atol(line.substr(mid + 1).c_str());
        ranges.insert(std::pair(start, end));
    }

    size_t i = 0;
    size_t prev_end = 0;
    for (const auto &[start, end] : ranges) {
        if (prev_end > end) {
            continue;
        }
        i = std::max(prev_end, start);
        result += end - i + 1;
        prev_end = end + 1;
    }

    std::cout << result << std::endl;
}
