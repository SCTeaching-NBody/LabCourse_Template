/**
 * @author first_name1 last_name1
 * @author first_name2 last_name2
 * @author first_name3 last_name3
 */

#include "labcourse/dummy.hpp"

#include "mpi.h"  // MPI_Init_thread, MPI_Comm_rank, MPI_Finalize

#include <cstdlib>   // EXIT_FAILURE
#include <iostream>  // std::cout, std::cerr

int main(int argc, char **argv) {
    // initialize the MPI environment
    // NOTE: if you want to use MPI together with OpenMP you SHOULD to call MPI_Init_thread instead of MPI_Init
    const int required = MPI_THREAD_FUNNELED;
    int provided;
    MPI_Init_thread(&argc, &argv, required, &provided);
    // the MPI_Init_thread doesn't report an error if the requested thread level support couldn't be satisfied
    // -> manually check the "returned" value
    if (required < provided) {
        // properly finalize the MPI environment
        MPI_Finalize();
        // exit since the thread level support could not be provided
        std::exit(EXIT_FAILURE);
    }

    // say hello
    labcourse::say_hello();

    // vector addition
    constexpr std::size_t N = 1 << 10;
    std::vector<double> a, b;

    // only root rank needs to store the full array and initialize it
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
        a.resize(N, 1.0);
        b.resize(N, 2.0);
    }

    // perform vector addition
    const std::vector<double> c = labcourse::vector_add(a, b);

    if (rank == 0) {
        // test vector addition: 1.0 + 2.0 = 3.0
        bool correct = true;
        for (const double d : c) {
            if (d != 3.0) {
                std::cerr << "Error: " << d << " != " << 3.0 << std::endl;
                correct = false;
                break;
            }
        }
        if (correct) {
            std::cout << "a + b = c is correct!" << std::endl;
        }
    }

    // properly finalize the MPI environment
    MPI_Finalize();
    return 0;
}
