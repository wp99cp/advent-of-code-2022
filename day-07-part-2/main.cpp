#include <iostream>
#include <cstdio>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <set>
#include <limits>

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

int min_size_above(struct folder &folder, int min_size) {

    if (folder.folder_size < min_size) return std::numeric_limits<int>::max();
    int min = folder.folder_size;

    for (struct folder f: folder.subfolders) {

        if (f.folder_size >= min_size) {
            min = std::min(min, min_size_above(f, min_size));
        }
    }

    return min;

}

int main(int argc, char **argv) {

    struct folder filesystem;

    std::string line;
    getline(std::cin, line);

    if (!is_dir_change(line)) throw std::runtime_error("Expected dir change");

    getline(std::cin, line);
    filesystem = list_dir(line);

    int min_size = filesystem.folder_size - 40000000;

    std::cout << "Sum of big folders: " << min_size_above(filesystem, min_size) << std::endl;
    return 0;

}