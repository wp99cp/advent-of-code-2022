#include <iostream>
#include <sstream>

int main(int argc, char **argv) {

    std::string input_line;
    unsigned long sum = 0;
    int a, b, c, d;

    while (1) {
        int count = scanf("%d-%d,%d-%d", &a, &b, &c, &d);
        if (count != 4) break;

        // [a, b] and [c, d]
        if ((a <= c && b >= c) || (c <= a && d >= a) ||
            (a <= d && b >= d) || (c <= b && d >= b)) {
            sum++;
        }

    }

    std::cout << "The sum is " << sum << std::endl;
    return 0;

}
