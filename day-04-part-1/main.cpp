#include <iostream>
#include <sstream>
#include <stdio.h>

int main(int argc, char **argv) {

    std::string input_line;
    unsigned long sum = 0;

    while (std::getline(std::cin, input_line)) {

        std::stringstream ss(input_line);

        int a, b, c, d;
        scanf("%d-%d,%d-%d", &a, &b, &c, &d);

        std::cout << a << " " << b << " " << c << " " << d << " » ";
        if ((a <= c && b >= d) || (a >= c && b <= d)) {
            sum++;
        }

        std::cout << sum << std::endl;

    }


    std::cout << "The sum is " << sum << std::endl;

    return 0;

}
