#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>

unsigned int countTrees(const std::vector<std::string>& land_map, std::size_t x_add, std::size_t y_add) {

    std::size_t land_map_width = land_map[0].size();   //all strings have the same length
    unsigned count_trees = 0;
    std::size_t x = x_add;
    std::size_t y = y_add;

    while(y < land_map.size()) {
        size_t slice_count = x / land_map_width;
        if( land_map[y][x - land_map_width*slice_count] == '#') {
            count_trees++;
        }
        x+=x_add;
        y+=y_add;
    }
    return count_trees;
}

int main() {
    std::ifstream map_tree("./input_data.txt");
    if(!map_tree.is_open()) return 1;

    std::string line;
    std::vector<std::string> land_map;
    while(std::getline(map_tree, line)) {
        land_map.push_back(line);
    }
    map_tree.close();

    std::cout << "Count of trees is: " << countTrees(land_map, 3,1);
    return 0;
}


