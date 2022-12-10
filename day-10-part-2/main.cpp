#include <iostream>
#include <vector>
#include <cstring>


int main(int argc, char **argv) {

    int sum = 1;
    int sum_of_products = 0;
    size_t cycle = 1;

    std::string line;
    std::vector<bool> picture(6 * 40, false);

    auto add_up = [&sum_of_products](size_t cycle, int sum) {
        if (cycle % 40 == 20) sum_of_products += sum * (int) cycle;
    };

    auto draw_pixel = [&picture](int cycle, int sum) {
        picture[cycle - 1] = std::abs((cycle % 40) - (sum + 1)) <= 1;
    };

    while (getline(std::cin, line)) {

        add_up(cycle, sum);
        draw_pixel(cycle, sum);

        cycle++;

        if (line == "noop") continue;

        add_up(cycle, sum);
        draw_pixel(cycle, sum);

        cycle++;
        int incr = std::stoi(line.substr( 4));
        sum += incr;

    }

    // draw the letters
    for (size_t i = 0; i < picture.size(); i++) {
        if (i % 40 == 0) std::cout << std::endl;
        std::cout << (picture[i] ? '#' : '.');
    }

    std::cout << std::endl << std::endl;
    std::cout << "Product: " << sum_of_products << std::endl;

    return 0;

}