#include <iostream>
#include <deque>
#include <utility>
#include <vector>
#include <algorithm>
#include <array>
#include <assert.h>
#include <sstream>

struct Monkey {

    std::deque<long long> items;

    std::function<long long(long long)> operation;

    long long division_check;
    long long monkey_id_next;
    long long monkey_id_prev;

    size_t inspected_items = 0;

    Monkey(
            std::deque<long long> &_items,
            std::function<long long(long long)> _operation,
            long long _division_check,
            long long _monkey_id_next,
            long long _monkey_id_prev) :
            items(std::move(_items)),
            operation(std::move(_operation)),
            division_check(_division_check),
            monkey_id_next(_monkey_id_next),
            monkey_id_prev(_monkey_id_prev) {}

};

void parse_items(const std::string &line, std::deque<long long> &items);

std::function<long long(long long)> parse_operation(const std::string &line);

long long parse_monkey(std::vector<Monkey> &monkeys, std::string &line);

int main(int argc, char **argv) {

    std::vector<Monkey> monkeys;

    std::string line;
    long long modulo = 1;
    while (getline(std::cin, line)) {
        modulo *= parse_monkey(monkeys, line);
    }

    std::cout << "Monkeys: " << monkeys.size() << " modulo: " << modulo << std::endl;


    // do 20 rounds
    for (long long i = 0; i < 10'000; i++) {

        for (auto &monkey: monkeys) {

            if (monkey.items.empty()) {
                continue;
            }

            while (!monkey.items.empty()) {

                long long item = monkey.items.front();
                monkey.items.pop_front();

                // apply operation
                item = monkey.operation(item);
                item = item % modulo;

                if (item % monkey.division_check == 0) {
                    monkeys[monkey.monkey_id_next].items.push_back(item);
                } else {
                    monkeys[monkey.monkey_id_prev].items.push_back(item);
                }

                monkey.inspected_items++;

            }

        }

    }

    std::cout << "Monkey 0 inspected items: " << monkeys[0].inspected_items << std::endl;
    std::cout << "Monkey 1 inspected items: " << monkeys[1].inspected_items << std::endl;
    std::cout << "Monkey 2 inspected items: " << monkeys[2].inspected_items << std::endl;
    std::cout << "Monkey 3 inspected items: " << monkeys[3].inspected_items << std::endl;


    std::cout << std::endl;

    // get top two monkeys ranked by inspected_items
    std::sort(monkeys.begin(), monkeys.end(), [](const Monkey &a, const Monkey &b) {
        return a.inspected_items > b.inspected_items;
    });



    std::cout << monkeys[0].inspected_items * monkeys[1].inspected_items << std::endl;

    return 0;

}

long long parse_monkey(std::vector<Monkey> &monkeys, std::string &line) {


    // assert that line begins with "Monkey "
    assert(line.substr(0, 6) == "Monkey");

    // parse items the monkey is holding at the beginning
    getline(std::cin, line);
    std::deque<long long> items;
    parse_items(line, items);

    // parse operation
    getline(std::cin, line);
    std::function<long long(long long)> operation = parse_operation(line);

    // parse division check
    getline(std::cin, line);
    long long division_check = std::stoi(line.substr(21));

    // parse monkey id of next monkey
    getline(std::cin, line);
    long long monkey_id_next = std::stoi(line.substr(29));

    // parse monkey id of previous monkey
    getline(std::cin, line);
    long long monkey_id_prev = std::stoi(line.substr(30));

    // Monkey
    monkeys.emplace_back(items, operation, division_check, monkey_id_next, monkey_id_prev);

    // ignore empty line
    getline(std::cin, line);
    return division_check;

}

std::function<long long(long long)> parse_operation(const std::string &line) {
    std::stringstream ss = std::stringstream(line.substr(23));
    char op;
    ss >> op;
    ss.ignore(); // ignore space

    auto apply_operation = [op](long long x1, long long x2) {

        switch (op) {
            case '+':
                return x1 + x2;
            case '*':
                return x1 * x2;
            default:
                assert(false);
        }

    };

    // check if ss followed by " old" or by a number
    if (ss.peek() == 'o') {

        return [apply_operation](long long x) {
            return apply_operation(x, x);
        };

    } else {
        long long number;
        ss >> number;

        return [apply_operation, number](long long x) {
            return apply_operation(x, number);
        };

    }
}

void parse_items(const std::string &line, std::deque<long long> &items) {
    std::stringstream ss(line.substr(18));
    for (long long item; ss >> item;) {
        items.push_back(item);
        if (ss.peek() == ',')
            ss.ignore();
    }
}
