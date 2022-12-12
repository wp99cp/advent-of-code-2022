#include <iostream>
#include <deque>
#include <utility>
#include <vector>
#include <algorithm>
#include <array>
#include <assert.h>
#include <sstream>
#include <set>
#include <queue>
#include <limits>

struct Node {

    char elevation;
    size_t position;
    size_t distance_from_start = std::numeric_limits<size_t>::max();
    std::set<Node *> neighbours = std::set<Node *>();
    Node *before = nullptr;

};

bool has_small_elevation_difference(std::vector<Node> &graph, size_t a, size_t b) {
    return (((int) graph.at(a).elevation) - ((int) graph.at(b).elevation)) >= -1;
}


void insert_node(std::vector<Node> &graph, const size_t W, const size_t i, char elevation) {

    if (elevation == 'S') elevation = 'a';
    else if (elevation == 'E') elevation = 'z';

    graph.at(i).elevation = elevation;
    graph.at(i).position = i;

    // check neighbours and add edges if possible
    if (i > 0 && (i % W) != 0 && has_small_elevation_difference(graph, i, i - 1)) {
        graph.at(i).neighbours.insert(&graph.at(i - 1));
    }

    if (i > 0 && (i % W) != 0 && has_small_elevation_difference(graph, i - 1, i)) {
        graph.at(i - 1).neighbours.insert(&graph.at(i));
    }

    if (i >= W && has_small_elevation_difference(graph, i, i - W)) {
        graph.at(i).neighbours.insert(&graph.at(i - W));
    }

    if (i >= W && has_small_elevation_difference(graph, i - W, i)) {
        graph.at(i - W).neighbours.insert(&graph.at(i));
    }

}


int main(int argc, char **argv) {

    Node *start_node = nullptr, *end_node = nullptr;

    std::string line;
    getline(std::cin, line);

    const size_t W = line.size();
    std::vector<Node> graph;
    graph.resize(W * 41);

    size_t H = 0;
    do {

        for (size_t i = 0; i < line.size(); i++) {

            insert_node(graph, W, i + H * W, line[i]);
            if (line[i] == 'S') {
                start_node = &graph.at(i + H * W);
                start_node->distance_from_start = 0;
            } else if (line[i] == 'E') end_node = &graph.at(i + H * W);

        }

        H++;
    } while (getline(std::cin, line));


    assert(start_node != nullptr && end_node != nullptr);

    auto node_greater = [](Node *a, Node *b) {
        return a->distance_from_start - b->distance_from_start;
    };

    // use a shortest-path algorithm to find the fastest connection between the start and end node
    std::deque<Node *> next_nodes;
    next_nodes.push_back(start_node);

    bool found_path = false;
    while (!next_nodes.empty()) {

        // retrieve next node
        Node *current = *next_nodes.begin();
        next_nodes.pop_front();

        for (Node *n: current->neighbours) {

            if (n->distance_from_start > current->distance_from_start + 1) {
                n->distance_from_start = current->distance_from_start + 1;
                n->before = current;
                next_nodes.push_back(n);

                if (n == end_node) found_path = true;

            }

        }

    }

    std::cout << W << " " << H << std::endl;


    std::cout << "End node has elevation " << end_node->elevation << " and dist " << end_node->distance_from_start
              << std::endl;

    if (found_path) {
        std::cout << "Found Path with length " << end_node->distance_from_start << std::endl;

        char path_map[W * H];

        for (size_t i = 0; i < W * H; i++) {
            path_map[i] = ' ';
        }


        std::cout << "Path via:" << std::endl << end_node->elevation;
        Node *path = end_node->before;
        while (path != nullptr) {
            std::cout << "-" << path->elevation;
            path_map[path->position] = path->elevation;
            path = path->before;
        }
        std::cout << std::endl;

        path_map[end_node->position] = 'E';

        for (size_t i = 0; i < H; i++) {
            for (size_t j = 0; j < W; j++) {
                std::cout << path_map[i * W + j];
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;


    } else {
        std::cout << "No path found!" << std::endl;
    }

}
