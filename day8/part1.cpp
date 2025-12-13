#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Pos {
  public:
    size_t x;
    size_t y;
    size_t z;

    Pos() = default;
    Pos(Pos &other) = default;
    Pos(Pos &&other) = default;
    Pos(size_t x, size_t y, size_t z) : x(x), y(y), z(z) {}

    auto operator=(const Pos &other) -> Pos & = default;

    auto operator==(const Pos &rhs) const -> bool {
        return this->x == rhs.x and this->y == rhs.y and this->z and rhs.z;
    }

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

    size_t result = 0;
    vector<Pos> positions{};

    string line;
    while (getline(file, line)) {
        Pos pos;
        istringstream stream(line);
        stream >> pos;
        positions.push_back(std::move(pos));
    }

    set<unordered_set<Pos>> circuits{};

    Pos prev = positions.back();
    for (const auto &pos : positions) {
        Pos closest = prev;
        for (const auto &other : positions) {
            if (pos != other and
                pos.dist_square(other) < pos.dist_square(closest)) {
                closest = other;
            }
        }
        set<reference_wrapper<unordered_set<Pos>>> matching{};
        for (const auto &circuit : circuits) {
            if (circuit.contains(pos) or circuit.contains(closest)) {
                matching.insert(circuit);
            }
        }
        unordered_set<Pos> new_circuit{};
        for (const auto &circuit : matching) {
            new_circuit.merge(circuit);
            circuits.erase(circuit);
        }
        prev = pos;
    }

    // for (const auto &circuit : circuits) {
    //     cout << circuit << endl;
    // }
}
