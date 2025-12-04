#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

inline auto count_neighbours(std::vector<std::vector<bool>> &grid, size_t i,
                             size_t j) -> int {
    static const std::vector<std::pair<size_t, size_t>> OFFSETS = {
        std::pair(-1, -1), std::pair(0, -1), std::pair(1, -1), std::pair(-1, 0),
        std::pair(1, 0),   std::pair(-1, 1), std::pair(0, 1),  std::pair(1, 1),
    };

    auto count = 0;
    for (const auto &offset : OFFSETS) {
        try {
            const bool v = grid.at(i + offset.first).at(j + offset.second);
            count += v;
        } catch (const std::out_of_range &e) {
        }
    }

    return count;
}

auto main(int argc, char **argv) -> int {
    if (argc != 2) {
        std::cout << "usage: part1 INPUT_FILE" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    std::ifstream file(path);

    size_t total_valid_positions = 0;
    std::vector<std::vector<bool>> tp_positions{};

    auto i = 0;
    std::string line;
    while (std::getline(file, line)) {
        std::vector<bool> row;
        row.reserve(line.length());

        for (auto j = 0; j < line.length(); ++j) {
            row.push_back(line[j] == '@');
        }

        tp_positions.push_back(std::move(row));

        ++i;
    }

    std::vector<std::pair<size_t, size_t>> removed{};

    auto height = i;
    do {
        removed.clear();

        for (auto i = 0; i < height; ++i) {
            for (auto j = 0; j < tp_positions[i].size(); ++j) {
                if (tp_positions[i][j] and
                    count_neighbours(tp_positions, i, j) < 4) {
                    tp_positions[i][j] = false;
                    removed.emplace_back(std::pair(i, j));
                    ++total_valid_positions;
                }
            }
        }
    } while (!removed.empty());

    std::cout << "total valid positions: " << total_valid_positions
              << std::endl;
}
