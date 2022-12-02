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

        if (player == 'X') score += 0;
        else if (player == 'Y') score += 3;
        else if (player == 'Z') score += 6;

        auto compute_player_choose = [](char a, char b) {

            if (b == 'Y') return a;
            if (b == 'X') {

                if (a == 'A') return 'C';
                if (a == 'B') return 'A';
                if (a == 'C') return 'B';

            }

            if (b == 'Z') {

                if (a == 'A') return 'B';
                if (a == 'B') return 'C';
                if (a == 'C') return 'A';

            }

            throw std::runtime_error("Invalid input");
        };

        player = compute_player_choose(opponent, player);

        if (player == 'A') score += 1;
        else if (player == 'B') score += 2;
        else if (player == 'C') score += 3;

    }


    std::cout << "You scored " << score << " points" << std::endl;

    return 0;

}
