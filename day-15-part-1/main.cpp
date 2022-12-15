#include <iostream>
#include <algorithm>
#include <sstream>
#include <limits>

void extract_coord(std::string &token, int &x, int &y) {

    std::stringstream ss(token);
    while (getline(ss, token, ' ')) {
        if (token.find("x=") != std::string::npos) {
            x = std::stoi(token.substr(2));
        }
        if (token.find("y=") != std::string::npos) {
            y = std::stoi(token.substr(2));
        }
    }

}

size_t calc_manhattan(int x1, int y1, int x2, int y2) {
    return (size_t) std::abs(x1 - x2) + (size_t) std::abs(y1 - y2);
}

int main(int argc, char **argv) {

    constexpr int desired_y = 2000000;

    // sensor at (x, y) has manhattan distance
    std::vector<std::tuple<int, int, size_t>> signals;
    std::vector<int> beacon_on_y;

    int min_x = std::numeric_limits<int>::max();
    int max_x = std::numeric_limits<int>::min();

    std::string line;
    while (getline(std::cin, line)) {

        int sx, sy, bx, by;

        // split the line at 'closest'
        std::stringstream ss(line);
        std::string token;
        std::getline(ss, token, ':');
        extract_coord(token, sx, sy);
        std::getline(ss, token, ':');
        extract_coord(token, bx, by);

        min_x = std::min(min_x, bx);
        max_x = std::max(max_x, bx);

        size_t manhattan = calc_manhattan(sx, sy, bx, by);
        signals.emplace_back(sx, sy, manhattan);

        if (by == desired_y) {
            beacon_on_y.push_back(bx);
        }
        if (sy == desired_y) {
            beacon_on_y.push_back(sx);
        }

    }


    min_x -= 10'000'000;
    max_x += 10'000'000;

    std::cout << "min_x: " << min_x << std::endl;
    std::cout << "max_x: " << max_x << std::endl;

    std::vector<char> desired_xs(max_x - min_x + 1, '.');

    for (auto t: signals) {
        int sx, sy;
        size_t meas_manhattan;
        std::tie(sx, sy, meas_manhattan) = t;

        // intersect the line at y = desired_y
        // with the area spanned by the manhattan distance
        // from the sensor to the base at (sx, sy)

        for (int i = 0; i < (int) desired_xs.size(); i++) {

            int x = i + min_x;

            size_t manhattan = calc_manhattan(sx, sy, x, desired_y);
            if (manhattan <= meas_manhattan) {
                desired_xs[i] = '#';
            }

        }

    }

    for (auto x: beacon_on_y) {
        desired_xs[x - min_x] = 'B';
    }

    // count # in desired_xs
    size_t count = 0;
    for (auto c: desired_xs) {
        // std::cout << c;
        if (c == '#') {
            count++;
        }
    }

    std::cout << std::endl;
    std::cout << "count: " << count << std::endl;

}
