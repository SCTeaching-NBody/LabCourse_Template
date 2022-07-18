/**
 * @file
 * @author first_name1 last_name1
 * @author first_name2 last_name2
 * @author first_name3 last_name3
 *
 * @brief An example dummy header.
 */

#pragma once

#include <vector>  // std::vector

namespace labcourse {

/**
 * @brief Simple dummy function showcasing some MPI and OpenMP functionality.
 * @details Prints a hello message from each OpenMP thread on each MPI rank with the respective thread and process ids.
 */
void say_hello();

/**
 * @brief Performs a vector addition `a + b = c` using MPI and OpenMP.
 * @details Only the MPI root rank stores the full vectors @p a and @p b and the result vector `c`!
 * @param[in] a the first vector
 * @param[in] b the second vector
 * @exception std::runtime_error if `a.size() != b.size()`
 * @return `a + b` (`[[nodiscard]]`)
 */
[[nodiscard]] std::vector<double> vector_add(const std::vector<double> &a, const std::vector<double> &b);

}  // namespace labcourse
