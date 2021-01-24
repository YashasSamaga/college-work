#include <stdio.h>
#include "mpi.h"

#include <iostream>
#include <fstream>
#include <iomanip>

#include <cassert>
#include <algorithm>

#define MPI_CHECK(expr) assert((expr) == MPI_SUCCESS)

void mycode(int rank, int numprocs, const std::string& input_path, const std::string& output_path)
{
    int N;
    if (rank == 0)
    {
        std::ifstream inFile(input_path);
        assert(inFile);
        inFile >> N;
    }

    // N is already set in root process; elsewhere, we obtain from the broadcast
    MPI_CHECK(MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD));

    double local_sum = 0.0;
    int max_numprocs = std::min(N, numprocs);
    if (rank < max_numprocs)
    {
        int stride = N / max_numprocs;
        int start = rank * stride + 1;
        int end = start + stride;
        if (rank == max_numprocs - 1)
            end = N + 1;

        for (int i = start; i < end; i++)
            local_sum += 1.0/(i * i);
    }

    double global_sum = 0.0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        std::ofstream outFile(output_path);
        assert(outFile);
        outFile << std::fixed << std::setprecision(6);
        outFile << global_sum;
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