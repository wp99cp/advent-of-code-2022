#include <iostream>
#include <sstream>

int main(int argc, char **argv) {

    std::string line;

    unsigned long max_calories_sum = 0;
    unsigned long calories_sum = 0;

    while (std::getline(std::cin, line)) {

        if (line.empty()) {

            // update the highest sum of calories if necessary
            max_calories_sum = (max_calories_sum < calories_sum) ? calories_sum : max_calories_sum;
            calories_sum = 0;
            continue;

        }

        // nonempty line contains exactly one integer number
        std::istringstream iss(line);

        int calories;
        iss >> calories;
        calories_sum += calories;

    }

    std::cout << "Elf with the most calories, carries: " << max_calories_sum << std::endl;

    return 0;

}