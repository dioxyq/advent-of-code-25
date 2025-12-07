#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <string>

auto main(int argc, char **argv) -> int {
    if (argc != 2) {
        std::cout << "usage: part1 INPUT_FILE" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    std::ifstream file(path);

    std::map<std::size_t, std::size_t> counts{};

    std::string line;

    std::getline(file, line);
    size_t start = line.find('S');
    counts[start] = 1;

    while (std::getline(file, line)) {
        std::set<size_t> to_erase{};
        for (const auto [pos, count] : counts) {
            if (line[pos] == '^') {
                counts[pos - 1] += counts[pos];
                counts[pos + 1] += counts[pos];
                to_erase.insert(pos);
            }
        }
        for (const auto pos : to_erase) {
            counts.erase(pos);
        }
    }

    size_t result = std::accumulate(
        counts.begin(), counts.end(), 0ul,
        [](const size_t acc, const std::pair<size_t, size_t> &pc) {
            return acc + pc.second;
        });

    std::cout << result << std::endl;
}
