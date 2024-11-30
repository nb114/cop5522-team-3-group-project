**Group members:** Nagaraju Brahmanapally, Chedlyne Valmyr, Pale Khan, Jack Lovett, Zachary Tisdale <br> <br>
**Purpose:** Our goal is to parallelize the Merge Sort algorithm via openMP and MPI solutions. <br> <br>


## Organization
**Root folder:** <br>
This contains the folders: MPI, openMP, outputs. It also contains the files: makefile, microtime.c, microtime.h, unoptimized.c, and this README.md.
<br></br>

**MPI:** <br>
This folder is for containing files relevant to Message-Passing Interface. It contains:
<ul>
    <li>opt3.c</li>
</ul>
<br/>

**openMP:** <br>
This folder contains files relating to parallelizing merge sort using openMP library. It contains:
<ul>
    <li>opt1.c- naieve parallelization implementation</li>
    <li>opt2.c- optimized parallelization</li>
</ul>
<br>

**outputs:** <br>
This folder contains log files which document the output for running each potential-solution. It contains:
<ul>
    <li>mpi_run_output.log</li>
    <li>omp_run_output.log</li>
    <li>unoptimized_run_output.log</li>
</ul> 
<br>

**makefile:** <br>
Compilation file used to compile the code conveniently and consistantly.
<br><br>

**microtime.h:** <br>
Provided header file for keeping track of code runtime
<br><br>

**microtime.c:** <br>
Provided file for keeping track of code runtime.
<br><br>

**unoptimized.c:** <br>
A basic serial merge sort implementation and starting point for the optimization solutions. This was copied into other files and then modified for parallelization using both openMP and MPI solutions.
<br><br>

**README.md:** <br>
You are here.
<br>
<br>


## How to run

**Compiling all** <br>
You can simply type `make` or `make all` into the terminal to compile the unoptimized, openmp, and mpi files all in one command. However, you can compile each individually, if you so choose, and will be described in their respective section.
<br></br>

**MPI** <br>
To compile for mpi, typing `make mpi_optimized` into the terminal will produce the output necessary to run. For manual execution of the code, type `mpiexec -n [numProcess] ./mpi_optimized [datasize] ` where numProcess is the number of processes to run the code on and the datasize is the size of the array to sort. However, automatic run across multiple datasizes and numProcesses can be found by running `make run_mpi`.
<br></br>

**OpenMP** <br>
To compile for OpenMP, typing `make omp_opt1` or `make omp_opt2`, with opt2 being the more-optmized version. To run manually, typing `./omp_opt1 [datasize] [numThreads]` where datasize is the size of the array to sort and numThreads is the number of threads to run it on. Replace ./omp_opt1 with ./omp_opt2 for using the second version. Automatic run is also available by typing into the terminal: `make run_omp` to test both opt1 and op2 on varying datasize and numThreads.
<br></br>

**Unoptimized** <br>
To compile for the unoptimized file, typing `make unoptimized` to get the exectuable output. Running manually is simply `./unoptimized [datasize]` and automatic running is `make run_unoptmized`.
