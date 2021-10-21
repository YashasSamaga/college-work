#include "rpc/client.h"
#include "rpc/rpc_error.h"

#include <iostream>
#include <sstream>
#include <cassert>
#include <chrono>

class GraphMSTServiceClient {
public:
    GraphMSTServiceClient(const std::string& server_ip, int server_port) : client(server_ip, server_port) {
        client.set_timeout(5000);
    }

    void addGraph(const std::string& id, int num_nodes) {
        client.call("add_graph", id, num_nodes);
    }

    void addEdge(const std::string& id, int from, int to, int weight) {
        assert(from > 0);
        assert(to > 0);
        client.call("add_edge", id, from - 1, to - 1, weight);
    }

    int getMSTTotalWeight(const std::string& id) {
        return client.call("get_mst", id).as<int>();
    }

private:
    rpc::client client;
};

void process_command(GraphMSTServiceClient& client, std::istringstream& is) {
    std::string cmd;
    is >> cmd;

    if (cmd == "add_graph") {
        std::string id;
        int n;
        if (is >> id >> n) {
            std::cout << "Sending request to add a graph " << id << " with " << n << " nodes\n";
            client.addGraph(id, n);
            std::cout << "Graph " << id << " with " << n << " nodes was added successfully\n";
        } else {
            std::cout << "Usage: add_graph [graph id] [num nodes]\n";
        }
    } else if (cmd == "add_edge") {
        std::string id;
        int u, v, w;
        if (is >> id >> u >> v >> w) {
            std::cout << "Sending request to add a edge (" << u << ", " << v << " : " << w << ") to graph " << id << "\n";
            client.addEdge(id, u, v, w);
            std::cout << "Edge (" << u << ", " << v << ", " << w << ") added to graph " << id << " successfully\n";
        } else {
            std::cout << "Usage: add_edge [graph id] [node1] [node2] [weight]\n";
        }
    } else if (cmd == "get_mst") {
        std::string id;
        if (is >> id) {
            std::cout << "Sending request for total weight of MST of graph " << id << "\n";
            auto total_weight = client.getMSTTotalWeight(id);
            std::cout << "Server returned total MST weight for graph " << id << " as " << total_weight << '\n';
        } else {
            std::cout << "Usage: get_mst [graph id]\n";   
        }
    } else {
        std::cout << "Error: Unknown command\n";
        std::cout << "Available Commands: add_graph, add_edge, get_mst\n";
    }
}

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " (ip) (port)\n";
        return 0;
    }

    std::string server_ip = argv[1];
    int server_port = std::stoi(argv[2]);

    GraphMSTServiceClient client(server_ip, server_port);
    std::cout << "Started client (server: " << server_ip <<  ":" << server_port << ")" << std::endl;
    
    std::string line;
    std::cout << "> ";
    while (std::getline(std::cin, line)) {
        std::istringstream is(line);
        
        try {
            using steady_clock = std::chrono::steady_clock;
            auto start = steady_clock::now();
            process_command(client, is);
            auto end = steady_clock::now();
            std::cout << "Recieved response in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
        } catch (rpc::timeout &t) {
            std::cout << "Request Timeout: " << t.what() << std::endl;
        } catch (rpc::rpc_error &e) {
            std::cout << "RPC Error: " << e.what() << '\n';
            std::cout << "RPC Name: " << e.get_function_name() << '\n';
            std::cout << "Error Message: " << e.get_error().as<std::string>();
        }
        std::cout << "\n> ";
    }
    std::cout << "\nRecieved EOF. Exiting\n";
    return 0;
}