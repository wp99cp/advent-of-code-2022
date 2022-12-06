#include <iostream>
#include <deque>
#include <set>


bool is_unique(std::deque<char> &deque) {


    std::set<char> set(deque.begin(), deque.end());
    return set.size() == deque.size();

}


int main(int argc, char **argv) {

    char c;
    std::deque<char> history;

    for(int pos = 0; std::cin >> c; pos++) {

        history.push_back(c);
        if (history.size() > 14) {
            history.pop_front();

            if(is_unique(history)) {
                std::cout << "Unique found at " << pos + 1 << std::endl;
                return 0;
            }

        }


    }

    return 0;

}