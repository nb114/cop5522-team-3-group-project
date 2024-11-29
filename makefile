CC=gcc
CFLAG= -Wall -I. -O3
OMP_FLAG= -fopenmp -Wall -I. -O3
MPI_CC=mpicc
MPI_CFLAG= -Wall -I. -O3
MPI_EXEC=mpiexec
MPI_EXEC_FLAG= -n

PROBLEM_SIZE=2048 4096 8192 16384
THREADS=1 2 4 8 10

OMP_TARGETS=omp_opt1 omp_opt2
MPI_TARGET=mpi_optimized
TARGETS=unoptimized $(OMP_TARGETS) $(MPI_TARGET)

all: $(TARGETS)

unoptimized: unoptimized.o microtime.o
	$(CC) -o $@ $^

unoptimized.o: unoptimized.c microtime.h
	$(CC) $(CFLAG) -c $<

microtime.o: microtime.c microtime.h
	$(CC) $(CFLAG) -c $<

omp_opt1: openMP/opt1.o microtime.o
	$(CC) $(OMP_FLAG) -o $@ $^

openMP/opt1.o: openMP/opt1.c microtime.h
	$(CC) $(OMP_FLAG) -c $< -o $@

omp_opt2: openMP/opt2.o microtime.o
	$(CC) $(OMP_FLAG) -o $@ $^

openMP/opt2.o: openMP/opt2.c microtime.h
	$(CC) $(OMP_FLAG) -c $< -o $@

# Add targets for OpenMP and MPI
openmp: openMP/opt1.o microtime.o
	$(CC) $(OMP_FLAG) -o $@ $^

mpi_optimized: MPI/opt3.o microtime.o
	$(MPI_CC) -o $@ $^

MPI/opt3.o: MPI/opt3.c microtime.h
	$(MPI_CC) $(MPI_CFLAG) -c $< -o $@

run_unoptimized: unoptimized
	mkdir -p outputs  # Create the outputs directory if it doesn't exist
	for arg in $(PROBLEM_SIZE); do \
		echo "Running $$target with argument $$arg"| tee -a outputs/unoptimized_run_output.log; \
		./unoptimized $$arg | tee -a outputs/unoptimized_run_output.log; \
		echo "==================="| tee -a outputs/unoptimized_run_output.log; \
	done; \

run_omp: $(OMP_TARGETS)
	mkdir -p outputs  # Create the outputs directory if it doesn't exist
	for target in $(OMP_TARGETS); do \
		for num_thread in $(THREADS); do \
			for arg in $(PROBLEM_SIZE); do \
				echo "Running $$target with argument $$arg: and $$num_thread" | tee -a outputs/omp_run_output.log; \
				./$$target $$arg $$num_thread | tee -a outputs/omp_run_output.log; \
				echo "===================" | tee -a outputs/omp_run_output.log; \
			done; \
		done; \
	done;

run_mpi: $(MPI_TARGET)
	mkdir -p outputs  # Create the outputs directory if it doesn't exist
	for proc in $(THREADS); do \
		for size in $(PROBLEM_SIZE); do \
			echo "Running $$target with $$proc processes and number of elements $$size" | tee -a outputs/mpi_run_output.log; \
			$(MPI_EXEC) $(MPI_EXEC_FLAG) $$proc ./$(MPI_TARGET) $$size $$size | tee -a outputs/mpi_run_output.log; \
			echo "===================" | tee -a outputs/mpi_run_output.log; \
		done; \
	done; \


clean:
	rm -f *.o */*.o *~ core $(TARGETS)
clean_outputs:
	rm -rf outputs
