#include <iostream>
#include <vector>


int main(int argc, char **argv) {

    std::vector<std::vector<short>> grid;
    std::vector<std::vector<bool>> visible;

    // read in grid
    std::string line;
    while (std::getline(std::cin, line)) {

        // grid.push_back(std::vector<short>()); leads to a bug using -O3
        grid.emplace_back();
        visible.emplace_back(line.size(), false);

        for (auto c: line) {
            auto i = (short) strtol(&c, nullptr, 10);
            grid.back().push_back(i);
            // std::cout << i << " ";
        }
        // std::cout << std::endl;
    }
    std::cout << std::endl;


    // set border to true
    for (size_t i = 0; i < grid.size(); i++) {

        visible[i][0] = true;
        visible[i][grid[i].size() - 1] = true;

        visible[0][i] = true;
        visible[grid.size() - 1][i] = true;

    }


    std::vector<short> maxs[4] = {grid[0], grid[grid.size() - 1], std::vector<short>(), std::vector<short>()};

    maxs[2].push_back(0);
    maxs[3].push_back(0);

    for (size_t j = 1; j < grid[0].size() - 1; j++) {
        maxs[2].push_back(grid[j][0]);
        maxs[3].push_back(grid[j][grid[0].size() - 1]);
    }

    // check visibility
    for (size_t i = 1; i < grid.size() - 1; i++) {

        for (size_t j = 1; j < grid[i].size() - 1; j++) {

            // std::cout << maxs[2][j] << " ";

            // visible from top
            visible[i][j] = visible[i][j] || (maxs[0][j] < grid[i][j]);
            maxs[0][j] = std::max(maxs[0][j], grid[i][j]);

            // visible from left
            visible[j][i] = visible[j][i] || (maxs[2][j] < grid[j][i]);
            maxs[2][j] = std::max(maxs[2][j], grid[j][i]);

            size_t x = grid[0].size() - 1 - i;
            size_t y = grid.size() - 1 - i;

            // visible from right
            visible[j][x] = visible[j][x] || (maxs[3][j] < grid[j][x]);
            maxs[3][j] = std::max(maxs[3][j], grid[j][x]);

            // visible from bottom
            visible[y][j] = visible[y][j] || (maxs[1][j] < grid[y][j]);
            maxs[1][j] = std::max(maxs[1][j], grid[y][j]);


        }

        // std::cout << std::endl;

    }


    long counter = 0;
    for (const std::vector<bool> &row: visible) {
        for (bool el: row) {
            std::cout << el << " ";
            if (el) counter++;
        }

        std::cout << std::endl;
    }

    std::cout << counter << std::endl; // 1807

    return 0;

}