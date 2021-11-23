#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include <unordered_set>
#include <array>
#include <sstream>
#include <chrono>

struct coord_t {
    int x{0}, y{0}, z{0};

    coord_t()= default;
    coord_t(int x1, int y1, int z1): x(x1), y(y1), z(z1){}
    [[nodiscard]] int hash()const { return (x * 31) + (y * 37) + (z * 41); }

    bool operator==(const coord_t &otherPos) const {
        return (x == otherPos.x && y == otherPos.y && z == otherPos.z);
    }

    [[nodiscard]] bool isNeighbor(const coord_t& c) const {
        coord_t diff;
        diff.x = (x - c.x);
        diff.y = (y - c.y);
        diff.z = (z - c.z);
        if(abs(diff.x) > 1 )
            return false;
        if(abs(diff.y) > 1)
            return false;
        if(abs(diff.z) > 1)
            return false;
        if(operator==(c))
            return false;
        return true;
    }


    [[nodiscard]] std::string to_string()const {
        std::stringstream ss;
        ss << "x: " << x << " y: " << y << " z: " << z;
        return ss.str();
    }
};


template <>
struct std::hash<coord_t> {
    int operator()(const coord_t& k) const {
        return k.hash();
    }
};

std::unordered_set<coord_t> getNeighbors(coord_t coord)  {
    std::unordered_set<coord_t> result;

    int vec[] = {0, -1, 1 };
    for(auto z : vec) {
        for(auto y: vec) {
            for(auto x: vec) {
                if(x == 0 && y == 0 && z == 0) {continue;}
                auto t = coord_t{ coord.x + x, coord.y + y, coord.z + z};
                result.insert(t);
            }
        }
    }

    return result;
}

int main() {
    std::ifstream input_data("./input_data.txt");
    if (!input_data.is_open()) { return 1; }

    std::string line;
    coord_t current_pos;
    std::size_t sum_active = 0;
    const unsigned int cycles_max_count = 7;

    std::array<std::unordered_set<coord_t>, cycles_max_count> cubes;

    while(std::getline(input_data, line)) {

        for(const auto c : line) {
            if((c == '#')) {
                cubes[0].insert(current_pos);
            }
            current_pos.x++;
        }
        current_pos.x = 0;
        current_pos.y++;
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    for (unsigned int i = 1; i < cycles_max_count; i++) {
        for (auto active_cube_it = cubes[i - 1].begin(); active_cube_it != cubes[i - 1].end(); active_cube_it++) {
            const auto &active_cube = *active_cube_it;
            auto count_active_neighbors = std::count_if(cubes[i - 1].begin(), cubes[i - 1].end(),
                                                        [&active_cube](const coord_t &neighbor) {
                                                            return active_cube.isNeighbor(neighbor);
                                                        });


            if (count_active_neighbors == 2 || count_active_neighbors == 3) {
                cubes[i].insert(active_cube);
            }

            auto neighbors = getNeighbors(active_cube);
            for (auto neigh_coord: neighbors) {
                auto neighbor_of_neighbor = getNeighbors(neigh_coord);

                auto count_active_cubes = std::count_if(neighbor_of_neighbor.begin(), neighbor_of_neighbor.end(),
                                                        [&cubes, i](const coord_t &neighbor) {
                                                            return cubes[i - 1].count(neighbor) > 0;
                                                        });
                if (count_active_cubes == 3) {
                    cubes[i].insert(neigh_coord);
                }
            }
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto ms_int = duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "The answer is: " << cubes[cycles_max_count-1].size() << std::endl;
    std::cout << "Calculated in: " << ms_int.count() << " milliseconds" << std::endl;

}
