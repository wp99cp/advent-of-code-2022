#include <iostream>
#include <sstream>
#include <queue>
#include <bits/stdc++.h>


int main(int argc, char **argv) {

    constexpr size_t SUM_OF_TOP_N = 3;

    std::string input_line;
    std::priority_queue<unsigned long, std::deque<unsigned long>, std::greater<>> max_sums;
    unsigned long calories_sum = 0;

    while (std::getline(std::cin, input_line)) {

        if (input_line.empty()) {

            // remove the min element and push the new sum
            max_sums.push(calories_sum);

            if (max_sums.size() > SUM_OF_TOP_N)
                max_sums.pop();

            calories_sum = 0;
            continue;

        }

        // nonempty input_line contains exactly one integer number
        std::istringstream iss(input_line);

        int calories;
        iss >> calories;
        calories_sum += calories;

    }

    // compute the accumulated sum of the top N sums
    unsigned long accumulated_max_calories_sum = 0;
    for (; !max_sums.empty(); max_sums.pop()) {
        accumulated_max_calories_sum += max_sums.top();
    }

    std::cout << "Elf with the most calories, carries: " << accumulated_max_calories_sum << std::endl;

    return 0;

}
