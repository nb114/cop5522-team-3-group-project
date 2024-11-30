**Group members:** Nagaraju Brahmanapally, Chedlyne Valmyr, Pale Khan, Jack Lovett, Zachary Tisdale <br> <br>
**Purpose:** Our goal is to take the merge sort algorithm and try to optimise its runtime by using both openMP and MPI solutions. <br> <br>
The organization of the project is as follows:
<br></br>

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
    <li>opt1.c</li>
    <li>opt2.c</li>
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
Compilation file used to compile the code in an easy way.
<br><br>

**microtime.h:** <br>
Provided header file for keeping track of code runtime
<br><br>

**microtime.c:** <br>
Provided file for keeping track of code runtime.
<br><br>

**unoptimized.c:** <br>
The provided code and starting point for the optimization solutions. This was copied into other files and then edited using both openMP and MPI as potential solutions.
<br><br>

**README.md:** <br>
You are here.