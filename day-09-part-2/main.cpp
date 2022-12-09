#include <iostream>
#include <vector>
#include <set>
#include <sstream>

void adjust_tail(std::pair<int, int> &head, std::pair<int, int> &tail) {

    // check if tail is in the same row as head
    if (head.second == tail.second) {
        if (std::abs(head.first - tail.first) == 2) {
            tail.first = head.first < tail.first ? tail.first - 1 : tail.first + 1;
        }
    }

        // check if tail is in the same column as head
    else if (head.first == tail.first) {
        if (std::abs(head.second - tail.second) == 2) {
            tail.second = head.second < tail.second ? tail.second - 1 : tail.second + 1;
        }
    }

        // they are diagonally positioned, then we move the tail one step diagonally towards the head
    else if (std::abs(head.first - tail.first) == 2 || std::abs(head.second - tail.second) == 2) {

        if (head.first > tail.first && head.second > tail.second) {
            tail.first++;
            tail.second++;
        } else if (head.first > tail.first && head.second < tail.second) {
            tail.first++;
            tail.second--;
        } else if (head.first < tail.first && head.second > tail.second) {
            tail.first--;
            tail.second++;
        } else if (head.first < tail.first && head.second < tail.second) {
            tail.first--;
            tail.second--;
        }

    }

        // tail must not be updated
    else {}


};

void move_head(std::pair<int, int> &head, char direction) {

    switch (direction) {
        case 'U':
            head.second++;
            break;
        case 'D':
            head.second--;
            break;
        case 'L':
            head.first--;
            break;
        case 'R':
            head.first++;
            break;
    }

};

int main(int argc, char **argv) {

    std::set<std::pair<int, int>> tail_path = {};

    std::vector<std::pair<int, int>> tails(9, {0, 0});
    std::pair<int, int> head = {0, 0};

    std::string line;
    while (getline(std::cin, line)) {

        char direction = line[0];
        int distance = std::stoi(line.substr(1));
        std::cout << direction << " " << distance << std::endl;

        for (; distance > 0; distance--) {
            move_head(head, direction);
            adjust_tail(head, tails[0]);

            for (int i = 1; i < 9; i++) {
                adjust_tail(tails[i - 1], tails[i]);
            }
            tail_path.insert(tails.back());
        }

    }

    std::cout << "The tail visited n=" << tail_path.size() << " fields." << std::endl;
    return 0;

}