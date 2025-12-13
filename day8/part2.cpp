#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Pos {
  public:
    size_t x;
    size_t y;
    size_t z;

    Pos() = default;
    // Pos(const Pos &other) = default;
    // Pos(Pos &&other) = default;
    Pos(size_t x, size_t y, size_t z) : x(x), y(y), z(z) {}

    // auto operator=(const Pos &other) -> Pos & = default;
    // auto operator=(Pos other) -> Pos { return Pos(other); }

    auto operator<=>(const Pos &rhs) const = default;

    auto operator+(const Pos &rhs) const -> Pos {
        return Pos(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
    }

    auto operator-(const Pos &rhs) const -> Pos {
        return Pos(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
    }

    auto mag_square() const -> size_t {
        return this->x * this->x + this->y * this->y + this->z * this->z;
    }

    auto dist_square(const Pos &rhs) const -> size_t {
        return (*this - rhs).mag_square();
    }
};

auto operator<<(ostream &os, const Pos &pos) -> ostream & {
    os << '(' << pos.x << ',' << pos.y << ',' << pos.z << ')';
    return os;
}

auto operator>>(istream &is, Pos &pos) -> istream & {
    is >> pos.x;
    is.get();
    is >> pos.y;
    is.get();
    is >> pos.z;
    return is;
}

static constexpr inline size_t cantor_hash(size_t a, size_t b) {
    return (a + b + 1) * (a + b) / 2 + b;
}

namespace std {
template <> struct hash<Pos> {
    size_t operator()(const Pos &s) const noexcept {
        return cantor_hash(s.x, cantor_hash(s.y, s.z));
    }
};
} // namespace std

auto main(int argc, char **argv) -> int {
    if (argc != 2) {
        cout << "usage: part1 INPUT_FILE" << endl;
        return 1;
    }

    string path = argv[1];
    ifstream file(path);

    // get all the positions
    vector<Pos> positions{};
    string line;
    while (getline(file, line)) {
        Pos pos{};
        istringstream stream(line);
        stream >> pos;
        positions.push_back(std::move(pos));
    }

    // find closest pairs
    auto dist_cmp = [](pair<Pos, Pos> &a, pair<Pos, Pos> &b) {
        return a.first.dist_square(a.second) < b.first.dist_square(b.second);
    };
    priority_queue<pair<Pos, Pos>, std::vector<pair<Pos, Pos>>,
                   decltype(dist_cmp)>
        pairs(dist_cmp);

    for (size_t i = 0; i < positions.size() - 1; ++i) {
        for (size_t j = i + 1; j < positions.size(); ++j) {
            Pos p1 = positions[i], p2 = positions[j];
            if (pairs.empty()) {
                pairs.push(pair(p1, p2));
                continue;
            }
            auto [t1, t2] = pairs.top();
            if (p1.dist_square(p2) >= t1.dist_square(t2)) {
                continue;
            }
            pairs.push(pair(p1, p2));
        }
    }

    vector<pair<Pos, Pos>> ordered_pairs{};
    ordered_pairs.reserve(pairs.size());
    for (; not pairs.empty(); pairs.pop()) {
        ordered_pairs.push_back(std::move(pairs.top()));
    }
    reverse(ordered_pairs.begin(), ordered_pairs.end());

    // construct circuits from pairs
    size_t result = 0;
    set<set<Pos>> circuits{};
    for (auto &[a, b] : ordered_pairs) {
        // find circuits that contain pair
        vector<reference_wrapper<const set<Pos>>> matching{};
        for (const auto &circuit : circuits) {
            if (circuit.contains(a) or circuit.contains(b)) {
                matching.emplace_back(circuit);
            }
        }

        // merge circuits
        set<Pos> new_circuit{};
        for (const auto &circuit : matching) {
            new_circuit.merge(set<Pos>(circuit.get()));
            circuits.erase(circuit);
        }
        new_circuit.insert(a);
        new_circuit.insert(b);
        circuits.insert(std::move(new_circuit));

        if (circuits.size() == 1 and
            circuits.begin()->size() == positions.size()) {
            result = a.x * b.x;
            break;
        }
    }

    cout << result << endl;
}
