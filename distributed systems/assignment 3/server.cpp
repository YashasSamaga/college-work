#include "graph.hpp"
#include "rpc/server.h"
#include "rpc/this_handler.h"

#include <chrono>
#include <iostream>
#include <cassert>
#include <map>
#include <string>
#include <shared_mutex>
#include <mutex>

class GraphManager {
    using mutex_t = std::shared_mutex;
    using read_lock_t = std::shared_lock<mutex_t>;
    using write_lock_t = std::unique_lock<mutex_t>;

public:
    void addGraph(const std::string& id, int num_nodes) {
        write_lock_t wlk(mutex);
        if (graphs.count(id) != 0)
            rpc::this_handler().respond_error("Graph already exists");
        graphs.emplace(id, num_nodes);
    }

    void addEdge(const std::string& id, int from, int to, int weight) {
        write_lock_t wlk(mutex);
        if (graphs.count(id) == 0)
            rpc::this_handler().respond_error("Graph does not exist");

        // undirected edge
        graphs[id].addEdge(from, to, weight);
        graphs[id].addEdge(to, from, weight);
    }

    int getMSTTotalWeight(const std::string& id) {
        read_lock_t rlk(mutex);
        if (graphs.count(id) == 0) {
            return -1;
            // rpc::this_handler().respond_error("Graph does not exist");
        }

        using steady_clock = std::chrono::steady_clock;
        auto start = steady_clock::now();
        int total_weight = graphs.at(id).getMSTTotalWeight();
        auto end = steady_clock::now();
        //std::cout << "Processed request in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
        return total_weight;
    }

private:
    mutex_t mutex;
    std::map<std::string, Graph> graphs;
};

class GraphMSTServiceServer {
public:
    GraphMSTServiceServer(int port, int thread_count) : srv(port) {
        srv.bind("add_graph", [this](std::string id, int num_nodes) {
            graph_manager.addGraph(id, num_nodes);
        });

        srv.bind("add_edge", [this](std::string id, int u, int v, int w) {
            graph_manager.addEdge(id, u, v, w);
        });

        srv.bind("get_mst", [this](std::string id) {
            return graph_manager.getMSTTotalWeight(id);
        });
    
        std::cout << "Started GraphMSTServer on port " << port << " with " << thread_count << " workers." << std::endl;
        srv.async_run(thread_count);
    }

private:
    rpc::server srv;
    GraphManager graph_manager;
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " (port) [num workers]\n";
        return 0;
    }

    int port = std::stoi(argv[1]);
    int num_workers = 1;
    if (argc == 3)
        num_workers = std::stoi(argv[2]);

    GraphMSTServiceServer server(port, num_workers);
    for (;;);
    return 0;
}