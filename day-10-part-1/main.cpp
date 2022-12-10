#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <cstring>


int main(int argc, char **argv) {

    int sum = 1;
    int sum_of_products = 0;
    size_t cycle = 1;

    std::string line;

    auto add_up = [&sum_of_products](size_t cycle, int sum){

        if (cycle % 40 == 20) {
            sum_of_products += sum * (int) cycle;
        }
    };

    while (getline(std::cin, line)) {

        add_up(cycle, sum);

        if (line.compare("noop") == 0) {
            cycle++;
            continue;
        }

        int incr = std::stoi(line.substr(4));
        cycle++;
        add_up(cycle, sum);
        cycle++;
        sum += incr;

    }


    std::cout << "Product: " << sum_of_products << std::endl;

    return 0;

}
