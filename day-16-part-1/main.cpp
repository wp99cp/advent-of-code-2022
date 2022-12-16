#include <iostream>
#include <algorithm>
#include <sstream>
#include <limits>
#include <cassert>
#include <set>

struct Node {

    std::vector<Node *> edges;

    std::vector<std::pair<int, Node *>> edges_direct;
    std::string name;

    int flow = 0;
    int distance = 0;

};


Node *get_node_ptr(std::string &name, std::unordered_map<std::string, Node *> &nodes) {

    Node *node;

    if (nodes.find(name) == nodes.end()) {
        node = new Node();
        node->name = name;
        nodes[name] = node;
    } else {
        node = nodes[name];
    }

    return node;

}

Node *create_graph(std::istream &input, std::unordered_map<std::string, Node *> &nodes) {

    Node *root = nullptr;

    std::string line;
    while (getline(input, line)) {

        std::string name = line.substr(6, 2);
        Node *node = get_node_ptr(name, nodes);
        if (name == "AA") {
            root = node;
        }

        // get flow rate: it's the number after "rate="
        std::string flow_rate_str = line.substr(line.find("rate=") + 5, 2);
        node->flow = std::stoi(flow_rate_str);

        // insert edges to neighbours
        std::string edges_str = line.substr(line.find("to valve") + 10);

        // iterate over every name split by ", "
        std::stringstream ss(edges_str);
        std::string neighbour_name;

        while (getline(ss, neighbour_name, ',')) {

            // remove spaces
            neighbour_name.erase(std::remove(neighbour_name.begin(), neighbour_name.end(), ' '),
                                 neighbour_name.end());

            // some parsing bug...
            if (neighbour_name.size() == 1) {
                neighbour_name += neighbour_name;
            }

            Node *neighbour = get_node_ptr(neighbour_name, nodes);
            node->edges.push_back(neighbour);

        }

    }

    assert(root != nullptr);
    return root;

}

int longest_path(Node *root, const std::set<const Node *> &visited, int time) {

    if (time < 0) return 0;

    int length = 0;

    for (const auto &dst: root->edges_direct) {

        // check if dst.second is in visited
        if (visited.find(dst.second) != visited.end()) continue;

        std::set<const Node *> copy_visited(visited.begin(), visited.end());
        copy_visited.insert(root);
        assert(copy_visited.size() - 1 == visited.size());

        int length_at_dst = longest_path(dst.second, copy_visited, time - dst.first);
        length_at_dst += root->flow * time;

        length = std::max(length, length_at_dst);


    }

    return length;

}

int main(int argc, char **argv) {

    std::unordered_map<std::string, Node *> nodes;

    Node *root = create_graph(std::cin, nodes);

    // precompute the shortest paths
    for (const auto &src: nodes) {

        Node *src_node = src.second;

        if (src_node->flow == 0 && src_node != root) continue;

        // Set distances to max int
        for (const auto &n: nodes) {
            n.second->distance = std::numeric_limits<int>::max();
        }
        src_node->distance = 0;

        // relax edges: Bellman_ford
        size_t V = nodes.size() - 1;
        for (size_t k = 0; k < V; k++) {
            for (const auto &n: nodes) {
                for (const auto &dst: n.second->edges) {

                    if (n.second->distance != std::numeric_limits<int>::max()) {
                        dst->distance = std::min(n.second->distance + 1, dst->distance);
                    }

                }
            }
        }

        std::cout << "Distances from " << src_node->name << " with flow=" << src_node->flow << ": ";

        // add edges to edges_direct
        for (const auto &n: nodes) {

            if (n.second->flow > 0 && src_node != n.second) {
                std::cout << n.second->name << "(" << n.second->distance << "), ";
                src_node->edges_direct.emplace_back(n.second->distance + 1, n.second);
            }

        }

        std::cout << std::endl;


    }

    std::cout << std::endl;

    // find the longest path
    int length = 0;
    for (auto &dst: root->edges_direct) {
        length = std::max(length, longest_path(dst.second, {root}, 30 - dst.first));
    }


    std::cout << "Longest path: " << length << std::endl;


}
