#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <iterator>

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

// template <class ForwardItr>
// void base_colorReduction(ForwardItr first, ForwardItr last, const std::vector<int>& node_labels, const std::vector<std::pair<int, int>>& edges, int delta)
// {
//     std::set<int> all_colors(std::begin(first), std::end(last));
//     if (all_colors.size() < delta)
//         return;
    
//     all_colors.resize(delta + 1);

//     int num_nodes = std::distance(first, last);
//     for (int i = 0; i < num_nodes; i++)
//     {
//         if (all_colors.count(first[i]))
//             continue;

//         int label = node_labels[i];

//         std::set<int> neighbor_colors;
//         for (const auto& edge : edges)
//         {
//             int u = edge.first, v = edge.second;
//             if (u == label) // TODO
//             {
//                 auto itr = std::find(std::begin(node_labels), std::end(node_labels));
//                 if (itr != node_labels.end())
//                 {
                    
//                     neighbor_colors.insert(first[v]);
//                 }
//             }
//         }

//         std::vector<int> avail_colors(delta + 1);
//         auto itr = std::set_difference(std::begin(all_colors), std::end(all_colors), std::begin(neighbor_colors), std::end(neighbor_colors), std::begin(avail_colors));
//         first[i] = *std::min_element(std::begin(avail_colors), itr);
//     }
// }

// std::vector<int> colorReduction(int N, const std::vector<std::pair<int, int>>& edges, int delta = -1)
// {
//     std::vector<int> colors(N);
//     std::iota(std::begin(colors), std::end(colors), 0);

//     if (delta < 0)
//         delta = maxDegree(N, edges);

//     base_colorReduction(std::begin(colors), std::end(colors), edges, delta);
//     return colors;
// }

std::vector<int> KWColorReduction(int N, const std::vector<std::pair<int, int>>& edges)
{
    const int delta = maxDegree(N, edges);

    std::vector<int> colors(N);
    std::iota(std::begin(colors), std::end(colors), 0);

    std::set<int> colors_set(std::begin(colors), std::end(colors));
    while (colors_set.size() > delta + 1)
    {
        const int bin_size = std::min<int>(2 * delta + 1, colors_set.size());
        const int num_bins = colors_set.size() / bin_size;

        // each bin can be processed independently
        for (int i = 0; i < num_bins; i++)
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

                std::cout << "bin_colors: ";
                for (auto c : bin_colors)
                    std::cout << c << ' ';
                std::cout << std::endl;
            }

            // nodes with bin colors
            std::vector<int> bin_nodes;
            for (int i = 0; i < N; i++)
                if (bin_colors.count(colors[i]))
                    bin_nodes.push_back(i);

            std::cout << "bin_nodes: ";
            for (auto c : bin_nodes)
                std::cout << c << ' ';
            std::cout << std::endl;

            // color reduction
            {
                std::set<int> allowed_colors;
                {
                    auto end_itr = std::begin(bin_colors);
                    std::advance(end_itr, delta + 1);

                    allowed_colors.insert(std::begin(bin_colors), end_itr);
                }

                std::cout << "allowed_colors: ";
                for (auto c : allowed_colors)
                    std::cout << c << ' ';
                std::cout << std::endl;

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
                }
            }
        }

        colors_set = std::set<int>(std::begin(colors), std::end(colors));
    }
    return colors;
}

int main(int argc, const char** argv)
{   
    int N, M;
    std::ifstream inFile(argv[1]);
    inFile >> N >> M;

    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < M; i++)
    {
        int u, v;
        inFile >> u >> v;
        edges.emplace_back(u - 1, v - 1);
    }

    // line graph
    std::vector<std::pair<int, int>> lg_edges;
    {
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

        // std::cout << "Line Graph:\n";
        // for (const auto& e : lg_edges)
        //     std::cout << e.first + 1 << ' ' << e.second + 1 << std::endl;
        // std::cout << std::endl;
    }

    auto colors = KWColorReduction(M, lg_edges);
    for (auto c : colors)
        std::cout << c << ' ';
     
    return 0;
}