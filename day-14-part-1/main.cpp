#include <iostream>
#include <algorithm>
#include <sstream>

#define x_offset 400
#define max_x 200
#define max_y 200

bool sand_stopped(size_t x, size_t y, std::vector<std::vector<char>> &grid) {


    if (y + 1 >= max_y) return false;

    // check if below is free
    if (grid.at(y + 1).at(x - x_offset) == ' ') {
        return sand_stopped(x, y + 1, grid);
    }

    if (x - 1 - x_offset >= max_x) return false;

    if (grid.at(y + 1).at(x - 1 - x_offset) == ' ') {
        return sand_stopped(x - 1, y + 1, grid);
    }

    if (x + 1 - x_offset >= max_x) return false;

    if (grid.at(y + 1).at(x + 1 - x_offset) == ' ') {
        return sand_stopped(x + 1, y + 1, grid);
    }

    grid.at(y).at(x - x_offset) = 'o';
    return true;

}

int main(int argc, char **argv) {


    std::vector<std::vector<char>> grid = std::vector<std::vector<char>>(max_y, std::vector<char>(max_x, ' '));

    std::string line;
    while (std::getline(std::cin, line)) {

        size_t x, y;

        std::stringstream ss(line);
        ss >> x;
        ss.get();         // read comma
        ss >> y;

        std::cout << "Pair (" << x << ", " << y << ")" << std::endl;

        size_t x_next, y_next;

        // read next element
        while (ss.get() && ss.get() && ss.get() && ss.get() && ss >> x_next && ss.get() && ss >> y_next) {

            std::cout << "Pair (" << x_next << ", " << y_next << ")" << std::endl;

            std::cout << " - (" << x << ", " << y << ")" << std::endl;

            // insert line between (x, y) and (x_next, y_next) to the grid
            if (x == x_next) {

                // vertical line
                for (size_t i = std::min(y, y_next); i <= std::max(y, y_next); ++i) {
                    grid.at(i).at(x - x_offset) = '#';

                }
            } else {
                // horizontal line
                for (size_t i = std::min(x, x_next); i <= std::max(x, x_next); ++i) {
                    grid[y][i - x_offset] = '#';
                }
            }

            x = x_next;
            y = y_next;

        }

    }


    // drop sand
    size_t count;
    for (count = 0; true; count++) {

        if (!sand_stopped(500, 0, grid)) break;

    }

    for (const std::vector<char> &row: grid) {
        for (const char c: row) {
            std::cout << c;
        }
        std::cout << std::endl;

    }
    std::cout << std::endl << "======================================" << std::endl << std::endl;



    std::cout << "Count is " << count << std::endl;


}
