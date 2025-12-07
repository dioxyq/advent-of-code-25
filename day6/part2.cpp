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

    std::vector<std::vector<std::string>> num_cols{};
    std::vector<std::pair<size_t, size_t>> start_end;
    std::vector<op> ops{};
    std::vector<size_t> results;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream stream(line);
        try {
            std::stoi(line);
            std::string s;
            size_t num_start = line.find_first_not_of(' ', 0);
            for (size_t i = 0; stream >> s; ++i) {
                size_t num_end =
                    std::min(line.find_first_of(' ', num_start), line.length());
                size_t num_len = num_end - num_start;

                if (i >= num_cols.size()) {
                    num_cols.emplace_back(std::vector<std::string>(num_len));
                    start_end.emplace_back(std::pair(num_start, num_end));
                }
                if (num_start < start_end[i].first) {
                    num_cols[i].insert_range(
                        num_cols[i].begin(),
                        std::vector<std::string>(start_end[i].first - num_start,
                                                 std::string{}));
                    start_end[i].first = num_start;
                }
                if (num_end > start_end[i].second) {
                    num_cols[i].append_range(std::vector<std::string>(
                        num_end - start_end[i].second, std::string{}));
                    start_end[i].second = num_end;
                }

                size_t diff = num_start - start_end[i].first;
                for (size_t j = 0; j < num_len; ++j) {
                    num_cols[i][j + diff].push_back(s[j]);
                }

                num_start = line.find_first_not_of(' ', num_end);
            }
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

    const auto zip = std::views::zip(ops, num_cols);
    std::transform(zip.cbegin(), zip.cend(), results.cbegin(), results.begin(),
                   [](const std::tuple<op, std::vector<std::string>> &o_n,
                      const size_t &r) {
                       op o = std::get<0>(o_n);
                       return std::accumulate(
                           std::get<1>(o_n).cbegin(), std::get<1>(o_n).cend(),
                           r, [&o](const size_t &v, const std::string &s) {
                               return o(v, std::stoi(s));
                           });
                   });

    size_t result = std::accumulate(results.begin(), results.end(), 0ul);

    std::cout << result << std::endl;
}
