#include <algorithm>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

auto main(int argc, char **argv) -> int {
    if (argc != 2) {
        std::cout << "usage: part1 INPUT_FILE" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    std::ifstream file(path);

    using op = std::function<size_t(size_t, size_t)>;

    std::vector<std::vector<size_t>> num_rows{};
    std::vector<op> ops{};
    std::vector<size_t> results;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream stream(line);
        try {
            std::stoi(line);
            int n;
            std::vector<size_t> nums{};
            while (stream >> n) {
                nums.push_back(n);
            }
            num_rows.push_back(std::move(nums));
        } catch (std::invalid_argument) {
            char c;
            while (stream >> c) {
                switch (c) {
                case '+':
                    ops.emplace_back(std::plus<size_t>{});
                    results.push_back(0);
                    break;
                case '*':
                    ops.emplace_back(std::multiplies<size_t>{});
                    results.push_back(1);
                    break;
                }
            }
        }
    }

    for (const auto &nums : num_rows) {
        const auto zip = std::views::zip(ops, nums);
        std::transform(zip.cbegin(), zip.cend(), results.cbegin(),
                       results.begin(),
                       [](const std::tuple<op, size_t> &o_n, const size_t &r) {
                           return std::get<0>(o_n)(r, std::get<1>(o_n));
                       });
    }

    size_t result = std::accumulate(results.begin(), results.end(), 0ul);

    std::cout << result << std::endl;
}
