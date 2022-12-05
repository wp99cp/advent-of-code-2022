#include <iostream>
#include <deque>
#include <tuple>

template<int len>
void print_queue(std::array<std::deque<char>, len> &queues) {
    for (size_t i = 0; i < queues.size(); i++) {
        std::cout << "Q " << i << ": ";
        for (auto &c: queues[i]) std::cout << "-" << c;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char **argv) {

    constexpr int NUM_QUEUES = 9;

    std::string input_line;
    std::array<std::deque<char>, NUM_QUEUES> queues;

    // parse queues
    while (getline(std::cin, input_line)) {

        // empty line after queues
        if (input_line.empty()) {
            break;
        }

        for (size_t i = 0; (i * 4 + 1) < input_line.size(); i++) {

            if (input_line[i * 4] == '[') {
                queues[i].push_front(input_line[i * 4 + 1]);
            }

        }

    }

    // print queues
    print_queue<NUM_QUEUES>(queues);

    // parse and compute instructions
    while (getline(std::cin, input_line)) {

        // parse instruction
        int count, from, to;
        int check = sscanf(input_line.c_str(), "move %d from %d to %d", &count, &from, &to);
        if (check != 3) throw std::runtime_error("invalid instruction");

        // adjust indices
        from--, to--;

        // move
        auto begin = queues[from].end() - count;
        queues[to].insert(queues[to].end(), begin, queues[from].end());
        queues[from].erase(begin, queues[from].end());

    }

    // print queues
    print_queue<NUM_QUEUES>(queues);

    std::cout << "Top elements concatenated: ";
    std::apply([](auto &&... v) { ((std::cout << v.back()), ...); }, queues);

    std::cout << std::endl; // Solution: HZFZCCWWV

    return 0;

}
