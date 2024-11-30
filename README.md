Group members: Nagaraju Brahmanapally, Chedlyne Valmyr, Pale Khan, Jack Lovett, Zachary Tisdale
Purpose: Our goal is to take the merge sort algorithm and try to optimise its runtime by using both openMP and MPI solutions. 
The organization of the project is as follows:


Root folder:
    This contains the folders: MPI, openMP, outputs. It also contains the files: makefile, microtime.c, microtime.h, unoptimized.c, and this README.md. 


MPI:
    This folder is for containing files relevant to Message-Passing Interface. It contains:
      - opt3.c


openMP:
    This folder contains files relating to parallelizing merge sort using openMP library. It contains:
      - opt1.c
      - opt2.c


outputs:
    This folder contains log files which document the output for running each potential-solution. It contains:
      - mpi_run_output.log
      - omp_run_output.log
      - unoptimized_run_output.log


makefile:
    Compilation file used to compile the code in an easy way.


microtime.h
    Provided header file for keeping track of code runtime


microtime.c
    Provided file for keepign track of code runtime.


unoptimized.c
    The provided code and starting point for the optimization solutions. This was copied into other files and then edited using both openMP and MPI as potential solutions.


README.md:
    You are here.