/**
 * @author first_name1 last_name1
 * @author first_name2 last_name2
 * @author first_name3 last_name3
 */

#include "labcourse/dummy.hpp"

#include "mpi.h"  // MPI_Comm_size, MPI_Comm_rank, MPI_Barrier, MPI_Bcast, MPI_Scatter, MPI_Gather
#include "omp.h"  // omp_get_num_threads, omp_get_thread_num

#include <cstddef>    // std::size_t
#include <iostream>   // std::cout, std::flush
#include <sstream>    // std::stringstream
#include <stdexcept>  // std::runtime_error
#include <vector>     // std::vector

namespace labcourse {

void say_hello() {
    // query the number of MPI ranks (i.e., the number of MPI processes) and the id of the current MPI rank
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // number of MPI processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // id of current MPI process

    // NOTE: the loop and std::stringstream only needed to properly serialize the output
    for (int i = 0; i < size; ++i) {
        if (i == rank) {
// spawn a parallel OpenMP section
#pragma omp parallel default(none) shared(std::cout) firstprivate(size, rank)
            {
                // query the number of OpenMP threads and the id of the current OpenMP thread
                const int num_threads = omp_get_num_threads();
                const int thread_num = omp_get_thread_num();
                // output our hello message
                std::stringstream ss;
                ss << "Hello from OpenMP thread " << thread_num << " out of " << num_threads
                   << " from MPI process " << rank << " out of " << size << '\n';
                std::cout << ss.str() << std::flush;  // make sure the message is printed immediately
            }
        }
        // wait until all MPI threads are here, i.e., until the MPI rank i has print his hello message
        MPI_Barrier(MPI_COMM_WORLD);
    }
}

std::vector<double> vector_add(const std::vector<double> &a, const std::vector<double> &b) {
    // check whether the vectors a and b have the same size
    if (a.size() != b.size()) {
        throw std::runtime_error{ "The two vectors a and b have different sizes!" };
    }

    // retrieve MPI specific information
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // number of MPI processes
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // id of current MPI process

    std::vector<double> c;
    // resize vector only on the root rank
    if (rank == 0) {
        c.resize(a.size());
    }

    // since only the root rank knows the size of c, it must broadcast this infomation to all other ranks
    int N = static_cast<int>(c.size());
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // determine on how many elements each MPI process will work and create the working vectors
    const int n = N / size;  // assume: N % size == 0
    std::vector<double> sa(n), sb(n), sc(n, 0.0);

    // scatter full arrays from the root rank to all other ranks
    MPI_Scatter(a.data(), n, MPI_DOUBLE, sa.data(), n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(b.data(), n, MPI_DOUBLE, sb.data(), n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

// perform c = a + b on the subarrays using OpenMP
#pragma omp parallel for default(none) shared(sa, sb, sc)
    for (std::size_t i = 0; i < sc.size(); ++i) {
        sc[i] = sa[i] + sb[i];
    }

    // gather results from subarrays on the root rank to the full result array c
    MPI_Gather(sc.data(), n, MPI_DOUBLE, c.data(), n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    return c;
}

}  // namespace labcourse
