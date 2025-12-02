#include <algorithm>
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

    std::string line;
    std::getline(file, line);

    size_t sum = 0;

    auto substr_start = line.begin();
    auto substr_end = std::find(substr_start, line.end(), ',');
    while (substr_start < line.end()) {
        auto substr_mid = std::find(substr_start, line.end(), '-');

        auto start = atol(std::string(substr_start, substr_mid).c_str());
        auto end = atol(std::string(substr_mid + 1, substr_end).c_str());

        std::cout << start << "-" << end << std::endl;

        for (auto i = start; i <= end; ++i) {
            auto n = std::to_string(i);
            auto len = n.length();
            auto prev_sum = sum;

            for (auto m = 2; m <= len && sum == prev_sum; ++m) {
                if (len % m != 0) {
                    continue;
                }

                auto quotient = len / m;
                auto first = n.substr(0, quotient);

                auto j = quotient;
                for (; j < len && first == n.substr(j, quotient);
                     j += quotient) {
                }

                if (j >= len) {
                    sum += i;
                    std::cout << n << std::endl;
                }
            }
        }

        std::cout << std::endl;

        substr_start = substr_end + 1;
        substr_end = std::find(substr_start, line.end(), ',');
    }

    std::cout << sum << std::endl;
}
