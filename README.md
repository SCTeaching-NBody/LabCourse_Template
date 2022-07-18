# LabCourse: Solar System Simulation - C++ CMake Template

**TODO: add your own descriptions**

This template repository can be used as baseline for the lab course **Solar System Simulation** https://github.com/SCTeaching-NBody/LabCourse_Slides.

## Building the Code

```sh
cd "path_to_cloned_directory"
mkdir build && cd build
cmake ..
cmake --build .
```

## Running the Code

The dummy example code can be run via SLURM:

```sh
OMP_NUM_THREADS=4 srun -N 4 ./simulate
```

and should output something like (note that the order may change in each run):

```text
Hello from OpenMP thread 0 out of 4 from MPI process 3 out of 4
Hello from OpenMP thread 1 out of 4 from MPI process 3 out of 4
Hello from OpenMP thread 2 out of 4 from MPI process 3 out of 4
Hello from OpenMP thread 3 out of 4 from MPI process 3 out of 4
Hello from OpenMP thread 0 out of 4 from MPI process 1 out of 4
Hello from OpenMP thread 1 out of 4 from MPI process 1 out of 4
Hello from OpenMP thread 2 out of 4 from MPI process 1 out of 4
Hello from OpenMP thread 3 out of 4 from MPI process 1 out of 4
Hello from OpenMP thread 0 out of 4 from MPI process 2 out of 4
Hello from OpenMP thread 1 out of 4 from MPI process 2 out of 4
Hello from OpenMP thread 3 out of 4 from MPI process 2 out of 4
Hello from OpenMP thread 2 out of 4 from MPI process 2 out of 4
Hello from OpenMP thread 0 out of 4 from MPI process 0 out of 4
Hello from OpenMP thread 2 out of 4 from MPI process 0 out of 4
Hello from OpenMP thread 1 out of 4 from MPI process 0 out of 4
Hello from OpenMP thread 3 out of 4 from MPI process 0 out of 4
a + b = c is correct!
```

## Testing

The tests can be build using
```sh
cmake -DWITH_TESTS=ON ..
```
which is on by default. It automatically builds the GoogleTest framework (can be changed to another framework if desired).

To run the tests use
```sh
ctest
```
