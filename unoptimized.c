#include <microtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <number_of_elements>\n", argv[0]);
        return 1;
    }

    double start_time, end_time, elapsed_time;
    int n = atoi(argv[1]);
    int *arr = generateRandomNumbers(n);

    // Measure sorting time
    start_time = microtime();
    mergeSort(arr, 0, n - 1);
    end_time = microtime();

    elapsed_time = end_time - start_time;

    // Print results
    printf("\nTime = %g us\n", elapsed_time);
    printf("Timer Resolution = %g us\n", getMicrotimeResolution());
    printf("Performance = %g Gflop/s\n", 2.0 * n * n * 1e-3 / elapsed_time);

    // Print min and max of the sorted array for verification
    printf("Min value: %d\n", arr[0]);
    printf("Max value: %d\n\n", arr[n - 1]);

    free(arr);

    return 0;
}
