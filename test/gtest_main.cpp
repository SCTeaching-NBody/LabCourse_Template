/**
 * @author first_name1 last_name1
 * @author first_name2 last_name2
 * @author first_name3 last_name3
 */

#include "mpi.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[]) {
    int result = 0;

    ::testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);
    result = RUN_ALL_TESTS();
    MPI_Finalize();

    return result;
}
