#include <iostream>
#include <cstdio>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <set>

struct folder {
    int folder_size;
    std::vector<folder> subfolders;
};

bool is_ls(std::string &line) {
    return line.rfind("$ ls", 0) == 0;
}

bool is_dir(std::string &line) {
    return line.rfind("dir", 0) == 0;
}

bool is_dir_change(std::string &line) {
    return line.rfind("$ cd", 0) == 0;
}

bool go_up(std::string &line) {
    return line.rfind("$ cd ..", 0) == 0;
}

struct folder list_dir(std::string &line) {

    if (!is_ls(line)) throw std::runtime_error("expected ls");

    struct folder folder;
    folder.folder_size = 0;

    while (getline(std::cin, line)) {

        if (is_dir(line)) continue;
        else if (is_dir_change(line) && go_up(line)) break;
        else if (is_dir_change(line)) {        // subfolder

            getline(std::cin, line);
            const struct folder subfolder = list_dir(line);
            folder.subfolders.push_back(subfolder);
            folder.folder_size += subfolder.folder_size;

        } else {

            std::stringstream input(line);
            int file_size;
            input >> file_size;
            folder.folder_size += file_size;


        }

    }

    return folder;

}

int big_folders(struct folder &folder) {

    int sum = 0;

    if (folder.folder_size <= 100000) {
        sum += folder.folder_size;
    }

    for (struct folder f: folder.subfolders) {
        sum += big_folders(f);
    }

    return sum;
}

int main(int argc, char **argv) {

    struct folder filesystem;

    std::string line;
    getline(std::cin, line);

    if (!is_dir_change(line)) throw std::runtime_error("Expected dir change");

    getline(std::cin, line);
    filesystem = list_dir(line);

    std::cout << "Sum of big folders: " << big_folders(filesystem) << std::endl;
    return 0;

}