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

    // sensor at (x, y) has manhattan distance
    std::vector<std::tuple<int, int, size_t>> signals;
    std::vector<std::pair<int, int>> beacons;

    int max = 4000000;

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

        size_t manhattan = calc_manhattan(sx, sy, bx, by);
        signals.emplace_back(sx, sy, manhattan);

        beacons.emplace_back(bx, by);


    }

    // sort the signals by manhattan distance
    std::sort(signals.begin(), signals.end(), [](auto &a, auto &b) {
        return std::get<2>(a) > std::get<2>(b);
    });

    for (int x = 0; x <= max; x++) {
        for (int y = 0; y <= max; y++) {

            int is_free = true;
            for (auto t: signals) {
                int sx, sy;
                size_t meas_manhattan;
                std::tie(sx, sy, meas_manhattan) = t;

                size_t manhattan = calc_manhattan(sx, sy, x, y);
                if (manhattan <= meas_manhattan) {
                    is_free = false;

                    // skip some steps
                    y += meas_manhattan - manhattan;

                    break;
                }
            }

            if (is_free) {
                std::cout << x << " " << y << std::endl;
                std::cout << "Frequency: " << (size_t) x * 4000000 + (size_t)  y << std::endl;
            }



        }
    }


}
