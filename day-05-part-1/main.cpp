#include <iostream>
#include <stack>
#include <deque>

int main(int argc, char **argv) {

    std::string input_line;
    std::stack<char, std::deque<char>> stacks[9];

    // parse stacks
    while (getline(std::cin, input_line)) {

        // empty line after stacks
        if (input_line.empty()) {
            break;
        }

        for (size_t i = 0; (i * 4 + 1) < input_line.size(); i++) {

            if (input_line[i * 4] == '[') {
                stacks[i].push(input_line[i * 4 + 1]);
            }

        }

    }


    // reverse order within each stack
    for (auto &i: stacks) {
        std::stack<char> temp;
        while (!i.empty()) {
            temp.push(i.top());
            i.pop();
        }
        i = temp;
    }


    // parse and compute instructions
    while (getline(std::cin, input_line)) {

        // parse instruction
        int count, from, to;
        sscanf(input_line.c_str(), "move %d from %d to %d", &count, &from, &to);


        // adjust indices
        from--;
        to--;


        for (int i = 0; i < count; i++) {
            stacks[to].push(stacks[from].top());
            stacks[from].pop();
        }


    }

    std::cout << "Top elements concatenated: ";
    for (auto &stack: stacks) {
        std::cout << stack.top();
    }

    std::cout << std::endl;

    return 0;

}
