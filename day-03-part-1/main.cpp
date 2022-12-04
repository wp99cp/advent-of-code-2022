#include <iostream>
#include <sstream>
#include <queue>
#include <bits/stdc++.h>


int main(int argc, char **argv) {

    std::string input_line;
    unsigned long sum = 0;

    while (std::getline(std::cin, input_line)) {

        if (input_line.empty()) {
            throw std::runtime_error("Empty line");
        }

        std::stringstream ss(input_line);

        auto get_priority = [](char c) {

            const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
            int priority = alphabet.find(c);
            return priority + 1;

        };

        std::set<int> part_1;
        std::set<int> part_2;


        int length = input_line.size();
        assert(length % 2 == 0);

        char i;
        for (int counter = 0; ss >> i; counter++) {

            if (counter < length / 2) {
                part_1.insert(get_priority(i));
            } else {
                part_2.insert(get_priority(i));
            }
        }

        std::vector<int> intersection;
        set_intersection(part_1.begin(), part_1.end(), part_2.begin(), part_2.end(),
                         std::back_inserter(intersection));

        int partial_sum = accumulate(intersection.begin(), intersection.end(), 0);
        sum += partial_sum;
    }


    std::cout << "The sum is " << sum << std::endl;

    return 0;

}
