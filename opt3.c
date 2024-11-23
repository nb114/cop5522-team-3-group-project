#include <microtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mpi.h>

// Function prototypes
void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);
int *generateRandomNumbers(int n);

void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int leftArr[n1], rightArr[n2];

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArr[], if any
    while (i < n1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArr[], if any
    while (j < n2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        // Calculate the midpoint
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int *generateRandomNumbers(int n)
{
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand();
    }
    return arr;
}

int main(int argc, char **argv)
{
    // if (argc != 2)
    // {
    //     fprintf(stderr, "Usage: %s <number_of_elements>\n", argv[0]);
    //     return 1;
    // }
    int comm_sz, my_rank, n;
    double start_time, end_time, elapsed_time;
    int* arr = NULL, *local_arr = NULL;


    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0) {
        n = atoi(argv[1]);
        arr = generateRandomNumbers(n);
        start_time = microtime();
    }

    // local_n is the number of elements to be sent to each process
    int local_n = n / comm_sz;
    local_arr = (int *)malloc(local_n * sizeof(int));

    // scatter data to all nodes
    MPI_Scatter(arr, local_n, MPI_INT, local_arr, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    // each localy call mergeSort
    mergeSort(local_arr, 0, local_n-1);

    // gather the results
    MPI_Gather(local_arr, local_n, MPI_INT, arr, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    // wait for processes to finish
    MPI_Barrier(MPI_COMM_WORLD);

    if (my_rank == 0) {
        // Print results
        end_time = microtime();
        merge(arr, 0, n/2, n); // one final merge to ensure it's all aligned correctly.
        
        elapsed_time = end_time - start_time;
        printf("\nTime = %g us\n", elapsed_time);
        printf("Timer Resolution = %g us\n", getMicrotimeResolution());
        printf("Performance = %g Gflop/s\n", 2.0 * n * n * 1e-3 / elapsed_time);

        // Print min and max of the sorted array for verification
        printf("Min value: %d\n", arr[0]);
        printf("Max value: %d\n\n", arr[n - 1]);
    }

    MPI_Finalize();

    free(arr);

    return 0;
}
