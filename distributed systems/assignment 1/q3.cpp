#include <stdio.h>
#include "mpi.h"

#include <iostream>
#include <fstream>
#include <iomanip>

#include <cassert>
#include <vector>
#include <set>
#include <algorithm>
#include <numeric>

#define MPI_CHECK(expr) assert((expr) == MPI_SUCCESS)

int maxDegree(int N, const std::vector<std::pair<int, int>>& edges)
{
    std::vector<int> counts(N, 0);
    for (const auto& edge : edges)
    {
        counts[edge.first]++;
        counts[edge.second]++;
    }
    return *std::max_element(std::begin(counts), std::end(counts));
}

void mycode(int rank, int numprocs, const std::string& input_path, const std::string& output_path)
{
    int num_nodes;
    int num_edges;
    int delta;
    std::vector<std::pair<int, int>> edges;
    if (rank == 0)
    {
        std::ifstream inFile(input_path);

        int N, M;
        inFile >> N >> M;

        std::vector<std::pair<int, int>> lg_edges;
        {
            std::vector<std::pair<int, int>> edges;
            for (int i = 0; i < M; i++)
            {
                int u, v;
                inFile >> u >> v;
                edges.emplace_back(u - 1, v - 1);
            }

            for (int i = 0; i < edges.size(); i++)
            {
                const auto& e1 = edges[i];
                for (int j = 0; j < edges.size(); j++)
                {
                    if (i <= j)
                        continue;

                    const auto& e2 = edges[j];
                    if (e1.first == e2.first || e1.first == e2.second || e1.second == e2.first || e1.second == e2.second)
                        lg_edges.emplace_back(i, j);
                }
            }
        }

        num_nodes = M;
        num_edges = lg_edges.size();
        delta = maxDegree(M, lg_edges);
        edges = std::move(lg_edges);

        MPI_CHECK(MPI_Bcast(&num_nodes, 1, MPI_INT, 0, MPI_COMM_WORLD));
        MPI_CHECK(MPI_Bcast(&num_edges, 1, MPI_INT, 0, MPI_COMM_WORLD));
        MPI_CHECK(MPI_Bcast(&delta, 1, MPI_INT, 0, MPI_COMM_WORLD));

        std::vector<int> u_arr(edges.size()), v_arr(edges.size());
        for (int i = 0; i < edges.size(); i++)
        {
            u_arr[i] = edges[i].first;
            v_arr[i] = edges[i].second;
        }
        MPI_CHECK(MPI_Bcast(u_arr.data(), num_edges, MPI_INT, 0, MPI_COMM_WORLD));
        MPI_CHECK(MPI_Bcast(v_arr.data(), num_edges, MPI_INT, 0, MPI_COMM_WORLD)); 
    }

    if (rank != 0)
    {
        MPI_CHECK(MPI_Bcast(&num_nodes, 1, MPI_INT, 0, MPI_COMM_WORLD));
        MPI_CHECK(MPI_Bcast(&num_edges, 1, MPI_INT, 0, MPI_COMM_WORLD));
        MPI_CHECK(MPI_Bcast(&delta, 1, MPI_INT, 0, MPI_COMM_WORLD));

        std::vector<int> u_arr(num_edges), v_arr(num_edges);
        MPI_CHECK(MPI_Bcast(u_arr.data(), num_edges, MPI_INT, 0, MPI_COMM_WORLD));
        MPI_CHECK(MPI_Bcast(v_arr.data(), num_edges, MPI_INT, 0, MPI_COMM_WORLD));

        edges.resize(num_edges);
        for (int i = 0; i < edges.size(); i++)
            edges[i] = {u_arr[i], v_arr[i]};
    }

    std::vector<int> colors(num_nodes);
    std::iota(std::begin(colors), std::end(colors), 0); // should be more efficient than initializing once and communicating

    // find proper edge coloring
    {
        std::set<int> colors_set(std::begin(colors), std::end(colors));
        while (colors_set.size() > delta + 1)
        {
            const int bin_size = std::min<int>(2 * delta + 1, colors_set.size());
            const int num_bins = colors_set.size() / bin_size;

            // each bin can be processed independently
            // distribute bins to different processes (TODO not optimal distribution)
            std::vector<std::pair<int, int>> local_updates;
            for (int i = rank; i < num_bins; i += numprocs)
            {
                int bin_start = i * bin_size, bin_end = bin_start + bin_size;
                if (i == num_bins - 1)
                    bin_end = colors_set.size();

                // colors allowed in the bin
                std::set<int> bin_colors;
                {
                    auto start_itr = std::begin(colors_set);
                    std::advance(start_itr, bin_start);

                    auto end_itr = std::begin(colors_set);
                    std::advance(end_itr, bin_end);

                    bin_colors.insert(start_itr, end_itr);
                }

                // nodes with bin colors
                std::vector<int> bin_nodes;
                for (int i = 0; i < num_nodes; i++)
                    if (bin_colors.count(colors[i]))
                        bin_nodes.push_back(i);

                // color reduction
                {
                    std::set<int> allowed_colors;
                    {
                        auto end_itr = std::begin(bin_colors);
                        std::advance(end_itr, delta + 1);

                        allowed_colors.insert(std::begin(bin_colors), end_itr);
                    }

                    for (auto node : bin_nodes)
                    {
                        std::vector<int> neighbor_colors;
                        for (const auto& edge : edges)
                        {
                            auto u = edge.first, v = edge.second;
                            if (u == node)
                                neighbor_colors.push_back(colors[v]);
                        }

                        std::vector<int> avail_colors(delta + 1);
                        auto itr = std::set_difference(std::begin(allowed_colors), std::end(allowed_colors), std::begin(neighbor_colors), std::end(neighbor_colors), std::begin(avail_colors));
                        colors[node] = *std::min_element(std::begin(avail_colors), itr);
                        local_updates.emplace_back(node, colors[node]);
                    }
                }
            }

            // send and recieve updates
            {
                int local_count = local_updates.size();
                std::vector<int> local_u, local_v;
                for (const auto& update : local_updates)
                {
                    local_u.push_back(update.first);
                    local_v.push_back(update.second);
                }

                std::vector<int> update_counts(numprocs, 0);
                MPI_CHECK(MPI_Allgather(&local_count, 1, MPI_INT, update_counts.data(), 1, MPI_INT, MPI_COMM_WORLD));

                std::vector<int> displs(numprocs + 1);
                displs[0] = 0;
                std::partial_sum(std::begin(update_counts), std::end(update_counts), std::begin(displs) + 1);

                int total_updates = std::accumulate(std::begin(update_counts), std::end(update_counts), 0);
                std::vector<int> u_arr(total_updates), v_arr(total_updates);

                assert(local_u.size() == local_count);
                assert(local_v.size() == local_count);

                MPI_CHECK(MPI_Allgatherv(local_u.data(), local_count, MPI_INT,
                u_arr.data(), update_counts.data(), displs.data(), MPI_INT, MPI_COMM_WORLD));

                MPI_CHECK(MPI_Allgatherv(local_v.data(), local_count, MPI_INT,
                v_arr.data(), update_counts.data(), displs.data(), MPI_INT, MPI_COMM_WORLD));

                // apply updates
                for (int i = 0; i < total_updates; i++)
                    colors[u_arr[i]] = v_arr[i];
            }

            colors_set = std::set<int>(std::begin(colors), std::end(colors));
        }
    }

    if (rank == 0)
    {
        std::ofstream outFile(output_path);
        for (auto c : colors)
            outFile << c + 1 << ' ';
    }
}

int main( int argc, char **argv )
{
    MPI_Init( &argc, &argv );

    int rank, numprocs;
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &numprocs );
    
    /*synchronize all processes*/
    MPI_Barrier( MPI_COMM_WORLD );
    double tbeg = MPI_Wtime();

    /* write your code here */
    {
        assert(argc == 3);
        mycode(rank, numprocs, argv[1], argv[2]);
    }

    MPI_Barrier( MPI_COMM_WORLD );
    double elapsedTime = MPI_Wtime() - tbeg;
    double maxTime;
    MPI_Reduce( &elapsedTime, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );
    if ( rank == 0 ) {
        printf( "Total time (s): %f\n", maxTime );
    }

    /* shut down MPI */
    MPI_Finalize();
    return 0;
}