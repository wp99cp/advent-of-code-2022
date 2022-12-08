#include <iostream>
#include <vector>


int main(int argc, char **argv) {

    std::vector<std::vector<short>> grid;

    // read in grid
    std::string line;
    while (std::getline(std::cin, line)) {

        grid.emplace_back();

        for (auto c: line) {
            auto i = (short) strtol(&c, nullptr, 10);
            grid.back().push_back(i);
        }

    }

    unsigned long max_scenic = 0;
    for (size_t i = 0; i < grid.size(); i++) {
        for (size_t j = 0; j < grid[i].size(); j++) {


            unsigned long scenic = !(i == 0 || j == 0 || i == grid.size() - 1 || j == grid[i].size() - 1);
            short height = grid[i][j];

            int k;
            for (k = (int) i + 1; k < (int) grid[i].size() - 1 && height > grid[k][j]; k++);
            scenic *= k - i;

            for (k = (int) i - 1; k > 0 && height > grid[k][j]; k--);
            scenic *= i - k;

            for (k = (int) j + 1; k < (int) grid.size() - 1 && height > grid[i][k]; k++);
            scenic *= k - j;

            for (k = (int) j - 1; k > 0 && height > grid[i][k]; k--);
            scenic *= j - k;

            max_scenic = std::max(max_scenic, scenic);

        }
    }

    std::cout << max_scenic << std::endl;
    return 0;

}