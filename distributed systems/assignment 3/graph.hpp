#pragma once

#include "disjoint_sets.hpp"

#include <set>
#include <cassert>

class Graph {
public:
    Graph() = default;
    Graph(int num_nodes) : num_nodes(num_nodes) { }

    void addEdge(int from, int to, int weight) {
        edges.emplace(from, to, weight);
    }

    int getMSTTotalWeight() const {
        disjoint_sets sets(num_nodes);
        std::vector<int> count(num_nodes, 1);

        int sum = 0, edge_count = 0;
        for(const auto& edge : edges) {
            int key_from = sets.get_key(edge.from),
                key_to = sets.get_key(edge.to);

            if(key_from == key_to)
                continue;

            int count_from = count[key_from],
                count_to = count[key_to];
            sum += edge.weight;
            edge_count++;
            
            int key_combined = sets.join(key_from, key_to);	
            assert(sets.get_key(edge.from) == key_combined && sets.get_key(edge.to) == key_combined);
            count[key_combined] = count_from + count_to;
        }
        if (edge_count != num_nodes - 1)
            return -1;
        return sum;
    }

private:
    struct Edge {
        Edge(int from, int to, int weight) : from(from), to(to), weight(weight) { }
        int from;
        int to;
        int weight;
        
        bool operator<(const Edge& rhs) const {
            return weight < rhs.weight;
        }
        
        bool operator>(const Edge& rhs) const {
            return weight > rhs.weight;
        }
    };

    int num_nodes;
    std::set<Edge> edges;
};