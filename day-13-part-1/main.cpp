#include <iostream>
#include <algorithm>
#include <sstream>

bool compare_strings(std::string str1, std::string str2) {

    if ((str1.size() == str2.size() && str1.empty()) || str2.empty())
        return true;

    if (str2.empty())
        return false;

    if (isdigit(str1[0]) && isdigit(str2[0])) {

        std::stringstream ss1(str1);
        std::stringstream ss2(str2);

        int num1, num2;
        ss1 >> num1;
        ss2 >> num2;

        if (num1 == num2)
            return compare_strings(str1.substr(std::to_string(num1).size()), str2.substr(std::to_string(num2).size()));
        else
            return num1 < num2;

    }


    if (str1[0] == '[' && str2[0] == '[')
        return compare_strings(str1.substr(1), str2.substr(1));

    if (str1[0] == '[' && isdigit(str2[0])) {

        std::stringstream ss2(str2);
        int num2;
        ss2 >> num2;

        str2 = std::to_string(num2) + "]" + str2.substr(std::to_string(num2).size());
        return compare_strings(str1.substr(1), str2);
    }

    if (str2[0] == '[' && isdigit(str1[0])) {

        std::stringstream ss1(str1);
        int num1;
        ss1 >> num1;

        str1 = std::to_string(num1) + "]" + str1.substr(std::to_string(num1).size());
        return compare_strings(str1, str2.substr(1));
    }

    if (str1[0] == ']' && str2[0] != ']')
        return true;

    if (str1[0] == str2[0])
        return compare_strings(str1.substr(1), str2.substr(1));


    return false;

}

int main(int argc, char **argv) {

    std::string line1;
    std::string line2;

    long unsigned int sum = 0;

    for (size_t index = 1; std::getline(std::cin, line1) && std::getline(std::cin, line2); index++) {

        if (compare_strings(line1, line2)) {
            sum += index;
        } else {
            std::cout << std::endl << "Lines NOT equal: " << std::endl << line1 << std::endl << line2 << std::endl;
        }


        // read in an empty line
        std::getline(std::cin, line1);

    }

    std::cout << "The sum of the indexes of pairs in the right order is: " << sum << std::endl;

}
