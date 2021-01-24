#include <stdio.h>
#include "mpi.h"

#include <iostream>
#include <fstream>
#include <iomanip>

#include <cassert>
#include <vector>
#include <algorithm>

#define MPI_CHECK(expr) assert((expr) == MPI_SUCCESS)

template <class RandomItr>
void qsort(RandomItr first, RandomItr last) {
    if(first == last)
        return;

    auto pivot = first[(last - first)/2]; // use midpoint
    RandomItr lt1 = std::partition(first, last, [&](auto v) { return v < pivot; });
    RandomItr gte2 = std::partition(lt1, last, [&](auto v) { return v <= pivot; });
    qsort(first, lt1);
    qsort(gte2, last);
};

void mycode(int rank, int numprocs, const std::string& input_path, const std::string& output_path)
{
    int max_numprocs = 0;
    
    std::vector<int> sizes(numprocs, 0), displs(numprocs, 0); // only used at root
    std::vector<int> nums; // only used at root

    std::vector<int> local_nums;
    if (rank == 0) {
        std::ifstream inFile(input_path);

        int N;
        inFile >> N;
        max_numprocs = std::min(N, numprocs);
        
        nums.resize(N);
        for (int i = 0; i < N; i++)
            inFile >> nums[i];

        int stride = N / max_numprocs;
        std::vector<int> start_points(max_numprocs), end_points(max_numprocs);
        for (int i = 0; i < max_numprocs; i++)
        {
            start_points[i] = i * stride;
            end_points[i] = i == max_numprocs - 1 ? N : start_points[i] + stride;
        }

        for (int i = 0; i < max_numprocs - 1; i++)
        {
            int previous_pivot = i == 0 ? 0 : end_points[i - 1] + 1;
            int pivot = end_points[i];
            std::nth_element(std::begin(nums) + previous_pivot, std::begin(nums) + pivot, std::end(nums));
        }

        for (int i = 0; i < max_numprocs; i++)
        {
            displs[i] = start_points[i];
            sizes[i] = end_points[i] - start_points[i];
        }

        int local_size;
        MPI_CHECK(MPI_Scatter(sizes.data(), 1, MPI_INT, &local_size, 1, MPI_INT, 0, MPI_COMM_WORLD));
        local_nums.resize(local_size);

        MPI_CHECK(MPI_Scatterv(nums.data(), sizes.data(), displs.data(), MPI_INT,
            local_nums.data(), local_nums.size(),  MPI_INT, 0, MPI_COMM_WORLD));
    }

    if (rank != 0)
    {
        int local_size;
        MPI_CHECK(MPI_Scatter(nullptr, 0, MPI_INT, &local_size, 1, MPI_INT, 0, MPI_COMM_WORLD));
        local_nums.resize(local_size);

        MPI_CHECK(MPI_Scatterv(nullptr, nullptr, nullptr, MPI_INT, local_nums.data(), local_nums.size(), MPI_INT, 0, MPI_COMM_WORLD));
    }

    qsort(std::begin(local_nums), std::end(local_nums));

    MPI_CHECK(MPI_Gatherv(local_nums.data(), local_nums.size(), MPI_INT, nums.data(), sizes.data(), displs.data(), MPI_INT, 0, MPI_COMM_WORLD));
    if (rank == 0)
    {
        std::ofstream outFile(output_path);
        for (int i = 0; i < nums.size(); i++)
            outFile << nums[i] << ' ';
        assert(std::is_sorted(std::begin(nums), std::end(nums)));
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