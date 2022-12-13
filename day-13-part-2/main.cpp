#include <iostream>
#include <algorithm>
#include <sstream>

bool ordering_relation(std::string str1, std::string str2) {

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
            return ordering_relation(str1.substr(std::to_string(num1).size()),
                                     str2.substr(std::to_string(num2).size()));
        else
            return num1 < num2;

    }


    if (str1[0] == '[' && str2[0] == '[')
        return ordering_relation(str1.substr(1), str2.substr(1));

    if (str1[0] == '[' && isdigit(str2[0])) {

        std::stringstream ss2(str2);
        int num2;
        ss2 >> num2;

        str2 = std::to_string(num2) + "]" + str2.substr(std::to_string(num2).size());
        return ordering_relation(str1.substr(1), str2);
    }

    if (str2[0] == '[' && isdigit(str1[0])) {

        std::stringstream ss1(str1);
        int num1;
        ss1 >> num1;

        str1 = std::to_string(num1) + "]" + str1.substr(std::to_string(num1).size());
        return ordering_relation(str1, str2.substr(1));
    }

    if (str1[0] == ']' && str2[0] != ']')
        return true;

    if (str1[0] == str2[0])
        return ordering_relation(str1.substr(1), str2.substr(1));


    return false;

}

int main(int argc, char **argv) {

    std::string line1;
    std::vector<std::string> lines;
    lines.emplace_back("[[2]]");
    lines.emplace_back("[[6]]");

    while (std::getline(std::cin, line1)) {

        // check if line is empty
        if (line1.empty())
            continue;

        lines.push_back(line1);
    }

    std::sort(lines.begin(), lines.end(), ordering_relation);

    size_t message = 1;
    int index = 1;
    for (auto line: lines) {

        if (line == "[[2]]" || line == "[[6]]") message *= index;

        // std::cout << line << std::endl;
        index++;

    }

    std::cout << "The sum of the indexes of pairs in the right order is: " << message << std::endl;

}
