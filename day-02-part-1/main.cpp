#include <iostream>
#include <sstream>
#include <queue>
#include <bits/stdc++.h>


int main(int argc, char **argv) {

    std::string input_line;
    unsigned long score = 0;

    while (std::getline(std::cin, input_line)) {

        if (input_line.empty()) {
            throw std::runtime_error("Empty line");
        }

        std::stringstream ss(input_line);
        char opponent, player;
        ss >> opponent >> player;

        if (player == 'X') score += 1;
        else if (player == 'Y') score += 2;
        else if (player == 'Z') score += 3;
        else throw std::runtime_error("Invalid player");

        auto compute_score = [](char a, char b) {
            if (a == 'A' && b == 'Y') return 6;
            if (a == 'B' && b == 'Z') return 6;
            if (a == 'C' && b == 'X') return 6;
            if ((a == 'A' && b == 'X') || (a == 'B' && b == 'Y') || (a == 'C' && b == 'Z')) return 3;
            return 0;
        };

        score += compute_score(opponent, player);

    }


    std::cout << "You scored " << score << " points" << std::endl;

    return 0;

}
