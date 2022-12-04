#include <iostream>
#include <sstream>
#include <queue>
#include <bits/stdc++.h>


int main(int argc, char **argv) {

    std::string input_line;
    unsigned long sum = 0;

    std::set<int> members[3];


    int member_id = -1;

    while (std::getline(std::cin, input_line)) {

        if (input_line.empty()) {
            throw std::runtime_error("Empty line");
        }

        member_id++;

        std::stringstream ss(input_line);

        auto get_priority = [](char c) {

            const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
            int priority = alphabet.find(c);
            return priority + 1;

        };

        char i;
        while (ss >> i) {
            members[member_id].insert(get_priority(i));
        }

        if (member_id == 2) {

            std::set<int> res1, res2;
            set_intersection(members[0].begin(), members[0].end(), members[1].begin(), members[1].end(),
                             inserter(res1, res1.begin()));
            set_intersection(res1.begin(), res1.end(), members[2].begin(), members[2].end(),
                             inserter(res2, res2.begin()));

            int partial_sum = accumulate(res2.begin(), res2.end(), 0);
            sum += partial_sum;
            std::cout << "Partial sum: " << partial_sum << std::endl;
            member_id = -1;

            members[0].clear();
            members[1].clear();
            members[2].clear();

        }


    }


    std::cout << "The sum is " << sum << std::endl;

    return 0;

}
